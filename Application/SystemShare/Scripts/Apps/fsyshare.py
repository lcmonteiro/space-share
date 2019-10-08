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
	return [
		{
			'name' : 'loading', 'verbose' : 0,
			'loading':{
				'timeout': 500, 'delay': 100, 'pack-size':1, 'sleep':1
			},
			'input':{
				'type':'file', 'uri':str(input), 'frame-size':10000, 'verbose': 0
			},
			'output':{
				'type':'tcp', 'uri':'localhost:5001', 'verbose' : 0
			}
		}, {
			'name' : 'encode', 'verbose' : 0,
			'encode':{
				'timeout': 500, 'delay': 10, 'redundancy':5, 'pass':str(password)
			},
			'input':{
				'type':'tcp', 'uri':'localhost:5001', 'pack-size': 50, 'frame-size':int(s)
			},
			'output':split({'type':'file', 'uri':'', 'verbose' : 0}, {'uri':output})
		}
	]
#........................................ process encode ........................................
def process_encode(input, output, password, redundancy):
	#
	process(encode(input, output, password, redundancy))
	#
	if min([getsize(f) for f in output]) == 0:
		process(encode(input, output, password, redundancy))
	#
#......................................... decode ...............................................
def decode(input, output, password):
	#
	# decode schema
	#
	return [
		{
			'name' : 'decode', 'verbose' : 0,
			'decode':{
				'timeout': 500, 'delay': 100, 'pass':str(password)
			},
			'output':{
				'type':'tcp', 'uri':'localhost:6001'
			},
			'input':split({'type':'file', 'uri':'', 'verbose' : 0}, {'uri':input})
		},
		{
			'name' : 'saving', 'verbose' : 0,
			'saving':{
				'timeout': 600, 'delay': 10,  'sleep':1
			},
			'input':{
				'type':'tcp', 'pack-size':1, 'frame-size':10000, 'uri':'localhost:6001', 'verbose' : 0
			},
			'output':{
				'type':'file', 'uri':str(output) , 'verbose': 0
			}
		}
	]
#........................................ process decode ........................................	
def process_decode(input, output, password):
	process(decode(input, output, password))
	#
	if getsize(output):
		process(decode(input, output, password))
	#
#-----------------------------------------------------------------------------------------------------------------------
# tools
#-----------------------------------------------------------------------------------------------------------------------
from subprocess import call
from uuid	import uuid4
from getpass	import getpass
from os		import makedirs
from os		import listdir
from os		import remove
from os		import getenv
from os		import devnull
from json	import load
from json	import dump
from os.path	import getmtime
from os.path	import exists
#.............................................. show .................................... 
def show(tag, source):
	try:
		with open(source) as f:
			tmp = load(f)
			if tag:
				for i, f in enumerate(set([f for d in tmp[tag] for f in listdir(d)])):
					print i+1, f
				#
			else:
				for i, f in enumerate(tmp.keys()):
					print i+1, f
				#
		#
	except:
		return "NOT FOUND"
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
	if not path:
		return
	#
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
#............................................. files ..................................... 
def files(name, paths):
	return [p + '/' + name for p in paths]
#............................................. paths ..................................... 
def paths(paths):
	for p in paths: 
		if not exists(p):
			makedirs(p)
		#
	#
	return paths
#............................................. redundancy ..................................... 
def redundancy(value, file, files):
	if value:
		return value
	return len(files)+(-(len(files) * getsize(file))//sum([getsize(f) for f in iin]))
#............................................. open ...................................... 
def openwith(file):
	FNULL = open(devnull, 'rw')
	#
	date = 0
	# geta last modification
	try:
		date = getmtime(file)
	except:
		pass
	# edit
	call(['mimeopen', file], stderr=FNULL)
	# verify
	try:
		return date != getmtime(file)
	except:
		pass
	return False
#-----------------------------------------------------------------------------------------------------------------------
# main
#-----------------------------------------------------------------------------------------------------------------------
def main(params):
	#
	# list files
	#
	if params.list:
		show(params.tag, params.source)
		return 0
	# 
	# read password
	#
	password = getpass();
	#
	# read ipath by tag if existe
	#
	ipath = read(params.tag, params.source, params.paths)
	#
	# opath
	#
	opath = params.paths if params.paths else ipath
	#
	# create, insert, remove, open 
	#
	if params.create:#-----------------------------------------------------------------------
		# tmp file
		tmp = '/tmp/' + str(uuid4()) + "." + params.create
		# open 
		if openwith(tmp):
			# encode
			process_encode(
				tmp, 
				files(params.name, paths(opath)),
				password, 
				params.redundancy
			)
		# save
		write(params.tag, params.paths, params.source)
		# remove
		remove(tmp)
		# quit
		return 0
	if params.insert:#-----------------------------------------------------------------------
		# encode
		process_encode(
			params.insert, 
			files(params.name, paths(opath)), 
			password, params.redundancy
		)
		# save
		write(params.tag, params.paths, params.source)
		# remove
		remove(params.insert);
		# quit
		return 0
	if params.delete:#-----------------------------------------------------------------------
		# delete
		for f in files(params.export, ipath):
			remove(f);
		# quit
		return 0
	if params.export:#-----------------------------------------------------------------------
		# decode
		process_decode(files(params.name, ipath), params.export, password)
		# quit
		return 0
	if params.name:#-------------------------------------------------------------------------
		# tmp file name
		tmp = '/tmp/' + str(uuid4())
		# decode
		process_decode(files(params.name, ipath), tmp, password)
		# open 
		if openwith(tmp):
			# encode
			process_encode(
				tmp, 
				files(params.name, paths(opath)), 
				password, 
				redundancy(params.redundancy, files(params.name, ipath), out)
			)
		# save
		write(params.tag, params.paths, params.source)
		# remove
		remove(tmp)
		# quit
		return 0
	#
	return 0
#	
#-----------------------------------------------------------------------------------------------------------------------
# entry point
#-----------------------------------------------------------------------------------------------------------------------
from sys import exit
#
if __name__ == '__main__':
	# read args
	params = parseinput('System Share', '1.0.0', [
		{'opt': ['--source', '-s'], 'settings':{
			'help' : 'tag',
			'default' : getenv('HOME') + '/.fsyshare.json',
		}},
		{'opt': ['--tag', '-t'], 'settings':{
			'help' : 'tag',
			'default' : 'r ',
		}},
		{'opt': ['--name', '-n'], 'settings':{
			'help' : 'name'
		}},
		{'opt': ['--paths', '-p'], 'settings':{
			'help' : 'coded files',
			'nargs' : '+'
		}},
		{'opt': ['--redundancy', '-r'], 'settings':{
			'help' : 'redundancy',
			'default' : 0,
		}},
		{'opt': ['--list', '-l'], 'settings':{
			'help' : 'list files',
			'action' : 'store_true'
		}},
		{'opt': ['--create', '-c'], 'settings':{
			'help' : 'create file',
			'default' : ''
		}},
		{'opt': ['--insert', '-i'], 'settings':{
			'help' : 'import file',
			'default' : ''
		}},
		{'opt': ['--export', '-e'], 'settings':{
			'help' : 'export file',
			'default' : ''
		}},
		{'opt': ['--delete', '-d'], 'settings':{
			'help' : 'export file',
			'default' : ''
		}}
	])
	#
	try:
		res = main(params)
	except:
		print 'fshare: error:', params 
		exit(-1)
	#
	exit(res)
#-----------------------------------------------------------------------------------------------------------------------