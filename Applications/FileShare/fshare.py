#!/usr/bin/env python
#encoding: UTF-8
#-----------------------------------------------------------------------------------------------------------------------
# dependencies
#-----------------------------------------------------------------------------------------------------------------------
from argparse import ArgumentParser
from subprocess import Popen
#....................................... definitions ....................................
SHARE_BIN = 'fileshare'
#....................................... parse input ....................................
def parseinput(name, version, config):
	#
	# create parser
	#
	parser = ArgumentParser(description=name, version=version)
	#
	# add option
	#
	for p in config:
		parser.add_argument(*p['opt'], ** p['settings'])
	#
	#
	return parser.parse_args()
#....................................... seriaze params ..................................
def parse_params(param):
	out = []
	for g in ['encode', 'decode', 'input', 'output']:
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
def call_native(params):
	return Popen([SYSHARE_BIN] + params)
#-----------------------------------------------------------------------------------------------------------------------
# code functions
#-----------------------------------------------------------------------------------------------------------------------
from os.path import getsize
from math import ceil
#-----------------------------------------------------------------------------------------------------------------------
# tools
#-----------------------------------------------------------------------------------------------------------------------
from subprocess import call
from uuid	import uuid4
from getpass	import getpass
from os		import remove
from os		import getenv
from json	import load     as load_file
from json	import dump     as dump_file
from os         import remove   as delete_file
from os.path	import getmtime
#-----------------------------------------------------------------------------------------------------------------------
# Format
#-----------------------------------------------------------------------------------------------------------------------
#
#....................................... default ....................................
def default():
        return {
                'file':'.#', 'box': {}, 'size': 10, 'pass': False  
        }
#....................................... merge ......................................
def merge(param, base):
        if 'box' in param:
                for p in param['box']:
                        base['box'][p] = param[p]
                #
        #
        if 'file' in param:
                base['file'] = param['file'] 
        # 
        if 'size' in param:
                base['size'] = param['size'] 
        # 
        if 'pass' in param:
                base['pass'] = param['pass'] 
        # 
        return base

#-----------------------------------------------------------------------------------------------------------------------
# IO
#-----------------------------------------------------------------------------------------------------------------------
#
def save(param):
        with open(param['file'] + '.#', 'w+') as f:
                dump_file(param, f, indent=8)
        #
#
def load(path='.#'):
        try:
                with open(path + '.#') as f:
                        return load_file(f)
                #
        except:
                return {}
        #
#
def clear(path='.#'):
        delete_file(path + '.#')
#
#-----------------------------------------------------------------------------------------------------------------------
# options
#-----------------------------------------------------------------------------------------------------------------------
#
def create(param):
        # save information
        save(merge(param, default()))
#
def encode(param):
        #
        # merge param
        #
        param = merge(param, merge(load(param['file']), merge(load(), default())))
        #
        # encode
        #
        print params
        #
        # save information
        #
        save(param)
#
def decode(param):
        print load(param['file'])
#
def delete(param):
        print load(param['file'])
        delete(param['file'])
#
#-----------------------------------------------------------------------------------------------------------------------
# translate
#-----------------------------------------------------------------------------------------------------------------------
#
def normalize(param):
        result = {}
        #
        if param.file:
                result['file'] = param.file
        #
        if param.size:
                result['size'] = param.size
        #
        if param.box:
                result['box'] = dict([(i[0], i[1]) for i in param.box]) 
        #
        if param.clear:
                result['clear'] = param.clear
        #
        if param.keep:
                result['keep'] = param.keep
        #
        return result
#
#-----------------------------------------------------------------------------------------------------------------------
# main
#-----------------------------------------------------------------------------------------------------------------------
def main(param):
        print normalize(param)
        #
        # select command
        #
        return {
                'create': create, 
                'encode': encode,
                'decode': decode,
                "delete": delete
        }[param.cmd](normalize(param))
#	
#-----------------------------------------------------------------------------------------------------------------------
# entry point
#-----------------------------------------------------------------------------------------------------------------------
from sys import exit
#
if __name__ == '__main__':
	# -------------------- read args -----------------------------------------------
	params = parseinput('File Share', '1.0.0', [{
                        'opt': ['cmd'], 'settings': {
                        'help': 'commands',
                        'choices': ['create', 'encode', 'decode', 'destroy']
                }}, {
                        'opt': ['file'], 'settings': {
                        'help': 'file path',
                        'nargs':'?',
                        'metavar':'FILE'
                }}, {
                        'opt': ['-s', '--size'], 'settings': {
                        'help': 'file size',
                        'nargs':1,
                        'default': None
                }}, {
                        'opt': ['-b', '--box'], 'settings': {
                        'nargs':2,
                        'action':'append',
                        'metavar':('URI', 'SIZE'),
                        'help': 'box parameters (uri and size)'
                }}, {
                        'opt': ['-p', '--password'], 'settings': {
                        'help': 'request password',
                        'action': 'store_true'
                }}, {
                        'opt': ['-c', '--clear'], 'settings': {
                        'help': 'clear files',
                        'action': 'store_true'
                }}, {
                        'opt': ['-k', '--keep'], 'settings': {
                        'help': 'clear files',
                        'action': 'store_true'
                }}
        ])
	# --------------- main ---------------------------------------------------------
	try:
		res = main(params)
	except Exception as inst:
		print 'fshare:: error:', inst 
		exit(-1)
	#
	exit(res)
#-----------------------------------------------------------------------------------------------------------------------