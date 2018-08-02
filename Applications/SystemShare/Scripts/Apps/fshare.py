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
	with open(source, 'w+') as f:
		try:
			# load
			tmp = load(f)
			# append
			tmp[tag] = path
			# save
			dump(tmp, f, indent=8)
		except:
			#save
			dump({tag:path}, f, indent=8)
		#
	#
#-----------------------------------------------------------------------------------------------------------------------
# main
#-----------------------------------------------------------------------------------------------------------------------
def main(params):
	#
	# default source file
	#
	source = getenv('HOME') + '/.fshare.json'
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
	# file name
	#
	fname = params.file if params.file else '/tmp/fshare-out'
	#
	# edit or view
	#
	if params.decode:
		#		
		process(decode(ipath, fname, password))
		#
		if getsize(fname):
			process(decode(ipath, fname, password))	
		#
		if params.clear:
			for f in ipath:
				remove(f);
			#
		#
	else:
		#		
		process(encode(fname, opath, password, params.redundancy))
		if min([getsize(f) for f in opath]) == 0:
			process(encode(fname, opath, password, params.redundancy))
		#
		write(params.tag, opath, source)
		#
		if params.clear:
			remove(fname);
		#
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
	params = parseinput('File Share', '1.0.0', [
		{'opt': ['--decode', '-d'], 'settings':{
			'help' : 'decode file',
			'action' : 'store_true'
		}},
		{'opt': ['--file', '-f'], 'settings':{
			'help' : 'file'
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
		{'opt': ['--clear', '-c'], 'settings':{
			'help' : 'clear files',
			'action' : 'store_true'
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