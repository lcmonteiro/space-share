#!/usr/bin/env python
#encoding: UTF-8
#-----------------------------------------------------------------------------------------------------------------------
# sys_share
#-----------------------------------------------------------------------------------------------------------------------
from subprocess import Popen
#....................................... definitions ....................................
SYSHARE_BIN = 'systemshare'
#........................................ get_param .....................................
def get_param(param):
	if isinstance(param, list):
		return param
	if isinstance(param, dict):
		return [param]
	if isinstance(param, basestring):
		return get_config(get_path(param))
	return []
#....................................... parse_params ...................................
def parse_params(param):
	out = []
	for g in ['name', 'verbose']:
		if g in param:
			out += ['--%s=%s'%(g, param[g])]
		#
	#
	for g in ['encode', 'decode', 'loading', 'saving', 'input', 'output']:
		if g in param:
			for it in get_param(param[g]):
				out += ['-%s'%g[0].upper()]
				for k in it:
					out += ['--%s=%s'%(k, it[k])]
				#
			#
		#
	#
	return out
#.......................................... exe .........................................
def exe(params):
	return Popen([SYSHARE_BIN] + params) 
#....................................... load system ....................................
def load_system(conf):
	out = []
	for it in (conf if isinstance(conf, list) else [conf]):
		out += [exe(parse_params(it))]
	#
	return out
#......................................... process ......................................
def process(config=[]):
	#
	for m in load_system(config):
		m.wait()
	#
#-----------------------------------------------------------------------------------------------------------------------
#  sys_share_app
#-----------------------------------------------------------------------------------------------------------------------
from argparse import ArgumentParser
#.......................................... split .............................................
def split(doc, directions):
	#
	# extend 
	#
	extended = [dict(doc) for i in xrange(max([len(directions[d]) for d in directions]))]
	#
	for d in directions:
		for i in xrange(len(directions[d])):
			extended[i][d] = directions[d][i]
		#
	#
	return  extended
#............................................ parse input .....................................
def parseinput(name, version, config):
	#
	# create parser
	#
	parser = ArgumentParser(description=name, version=version)
	#
	# add option
	#
	for p in config:
		parser.add_argument(*p['opt'], **p['settings'])
	#
	#
	return parser.parse_args()
#-----------------------------------------------------------------------------------------------------------------------
# code functions
#-----------------------------------------------------------------------------------------------------------------------
from os.path import getsize
from math import ceil
#........................................ encode ..............................................
def encode(input, output, password, redundancy):
	#
	# find frame size
	#
	s = ceil(float(getsize(input)) / 50.0)
	while s > 8096:
		s = ceil(s / 2)
	#
	# redundancy
	#
	r = ((50.0 / len(output)) * float(redundancy))
	#
	return [{
		'name' : '2', 'verbose' : 0,
		'encode':{
			'timeout': 500, 'redundancy':int(r) + 5, 'pass':str(password)
		},
		'input':{
			'type':'file', 'uri':str(input), 'pack-size': 50, 'frame-size':int(s)
		},
		'output':split({'type':'file', 'uri':'', 'verbose' : 0}, {'uri':output})
	}]
#......................................... decode ...............................................
def decode(input, output, password):
	#
	# decode schema
	#
	return [{
		'name' : '1', 'verbose' : 0,
		'decode':{
			'timeout': 500, 'pass':str(password)
		},
		'output':{
			'type':'file', 'uri':str(output)
		},
		'input':split({'type':'file', 'uri':'', 'verbose' : 0}, {'uri':input})
	}]
#
#-----------------------------------------------------------------------------------------------------------------------
# tools
#-----------------------------------------------------------------------------------------------------------------------
from subprocess import call
from uuid	import uuid4
from getpass	import getpass
from os		import remove
from os		import getenv
from json	import load
from json	import dump
from os.path	import getmtime
#.............................................. keys .................................... 
def keys(source):
	try:
		with open(source) as f:
			tmp = load(f)
			return tmp.keys();
		#
	except:
		return []
	#
#.............................................. read .................................... 
def read(tag, source, path):
	try:
		with open(source) as f:
			tmp = load(f)
			return tmp[tag]
		#
	except:
		return path
	#
#............................................. write ..................................... 
def write(tag, path, source):
	try:
		tmp = None
		with open(source) as f:
			tmp = load(f)
			# append
			tmp[tag] = path
		#
		with open(source, 'w+') as f:
			# save
			dump(tmp, f, indent=8)
		#
	except:
		with open(source, 'w+') as f:
			#save
			dump({tag:path}, f, indent=8)
		#
	#
#............................................. edit ...................................... 
def edit(file):
	# geta last modification
	date = getmtime(file)
	# edit
	call(['nano', file])
	# verify
	return date != getmtime(file)
#............................................. edit ...................................... 
def view(file):
	call(['nano','-vx', file])
#-----------------------------------------------------------------------------------------------------------------------
# main
#-----------------------------------------------------------------------------------------------------------------------
def main(params):
	#
	# default source file
	#
	source = getenv('HOME') + '/.tshare.json'
	#
	# list files
	#
	if params.list:
		for i, f in enumerate(keys(source)):
			print i+1, f
		return 0
	#
	# tmp file name
	#
	tmp = '/tmp/' + str(uuid4())
	#
	# read password
	#
	password = getpass();
	#
	# read ipath by tag if existe
	#
	ipath = read(params.tag, source, params.paths)
	#
	# opath
	#
	opath = params.paths if params.paths else ipath
	#
	# edit or view
	#
	if params.edit:
		#		
		process(decode(ipath, tmp, password))
		#
		if edit(tmp):
			process(encode(tmp, opath, password, params.redundancy))
			#
			if min([getsize(f) for f in opath]) == 0:
				process(encode(tmp, opath, password, params.redundancy))
			#
			write(params.tag, opath, source)
		#
	else:
		#		
		process(decode(ipath, tmp, password))
		#
		view(tmp)
	#
	remove(tmp)
	return 0
#	
#-----------------------------------------------------------------------------------------------------------------------
# entry point
#-----------------------------------------------------------------------------------------------------------------------
from sys import exit
#
if __name__ == '__main__':
	# read args
	params = parseinput('Text Share', '1.0.0', [
		{'opt': ['--edit', '-e'], 'settings':{
			'help' : 'edit file',
			'action' : 'store_true'
		}},
		{'opt': ['--paths', '-p'], 'settings':{
			'help' : 'coded files',
			'nargs' : '+'
		}},
		{'opt': ['--tag', '-t'], 'settings':{
			'help' : 'tag or name',
			'default' : '',
		}},
		{'opt': ['--redundancy', '-r'], 'settings':{
			'help' : 'redundancy',
			'default' : 0,
		}},
		{'opt': ['--list', '-l'], 'settings':{
			'help' : 'list files',
			'action' : 'store_true'
		}}
	])
	#
	try:
		res = main(params)
	except:
		print 'tshare: error:', params 
		exit(-1)
	#
	exit(res)
#-----------------------------------------------------------------------------------------------------------------------