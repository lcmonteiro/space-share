#!/usr/bin/env python2
#encoding: UTF-8
#
from subprocess import Popen
from os.path import dirname
from os.path import isabs
from json import load
from time import sleep
#
#-----------------------------------------------------------------------------------------------------------------------
# definitions
#-----------------------------------------------------------------------------------------------------------------------
CONFIG_FILE = "/home/monteiro/workspace/m2bee/C++/ShareSpace/Applications/SystemShare/sys_share.json"
#
SYSHARE_BIN = "/home/monteiro/workspace/m2bee/C++/ShareSpace/Applications/SystemShare/dist/Debug/GNU-Linux/systemshare"
#-----------------------------------------------------------------------------------------------------------------------
# parse code
#-----------------------------------------------------------------------------------------------------------------------
#
# get config
#
def get_config(fname=CONFIG_FILE):
	with open(fname) as fdata:
		return load(fdata)
	return None
#
# get path
#
def get_path(param):
	return param if isabs(param) else dirname(CONFIG_FILE) + '/' + param
#
# parameters
#
def get_param(param):
	if isinstance(param, list):
		return param
	if isinstance(param, dict):
		return [param]
	if isinstance(param, basestring):
		return get_config(get_path(param))
	return []
	#
#
def parse_params(param):
	out = []
	for g in ['name', 'type', 'verbose']:
		if g in param:
			out += ['--%s=%s'%(g, param[g])]
		#
	#
	for g in ['encode', 'decode', 'loading', 'saving', 'ypsilon', 'tpsilon', 'input', 'output']:
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
#
#-----------------------------------------------------------------------------------------------------------------------
# modules call
#-----------------------------------------------------------------------------------------------------------------------
#
# basic run
#
def run(bin, params):
	print ' '.join([bin] + params)
	return Popen([bin] + params)
#
# share
#
def call(params):
	return run(SYSHARE_BIN , params)
#-----------------------------------------------------------------------------------------------------------------------
# load system
#-----------------------------------------------------------------------------------------------------------------------
def load_system(conf):
	out = []
	for it in (conf if isinstance(conf, list) else [conf]):
		out += [call(parse_params(it))]
	#
	return out
#
#-----------------------------------------------------------------------------------------------------------------------
# process
#-----------------------------------------------------------------------------------------------------------------------
def process(config=[]):
	#
	for m in load_system(config):
		m.wait()
	#
#
#-----------------------------------------------------------------------------------------------------------------------
# main
#-----------------------------------------------------------------------------------------------------------------------
def main(cfile=CONFIG_FILE):
	#
	CONFIG_FILE = cfile;
	#
	process(get_config(CONFIG_FILE))
	#
#
if __name__ == "__main__":
	main()
#
