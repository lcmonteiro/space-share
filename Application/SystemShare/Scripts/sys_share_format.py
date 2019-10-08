#!/usr/bin/env python2
#encoding: UTF-8
#
#-----------------------------------------------------------------------------------------------------------------------
# definitions
#-----------------------------------------------------------------------------------------------------------------------
CONFIG = {
	'socket':{
		'share':{
			'share':{
				'sync':{
				}
			}	
		}
	}
}
#-----------------------------------------------------------------------------------------------------------------------
# TEMPLATE
#-----------------------------------------------------------------------------------------------------------------------
TEMPLATE = {
	'socket':{
		'store':{'delay':'','sleep':''},
		'load':{'delay':'','sleep':''},
		'input':{'type':'','resource':'','frame-size':''},
		'output':{'type':'','resource':''}
	},
	'share':{
		'decode':{'quantity':0},
		'encode':{'quantity':0},
		'input':{'type':'','resource':'','frame-size':'','container-size':''},
		'output':{'type':'','resource':''}},
	'sync':{
		'get':{'delay':''},
		'put':{'delay':''},
		'input':{'type':'tcp','resource':'localhost:6001'},
		'output':''
	}
}
#-----------------------------------------------------------------------------------------------------------------------
# CODE
#-----------------------------------------------------------------------------------------------------------------------
def create_socket(template, config, out):
	out['socket'] += [template['socket']];
	pass
#
def create_share(template, config, out):
	out['share'] += [template['share']];
	pass
#
def create_sync(template, config, out):
	out['sync'] += [template['sync']];
	pass
#
def create(template, config):
	out = {
		'socket':[], 'share':[], 'sync':[]
	}
	for e in config:
		{'socket': create_socket, 'share': create_share, 'sync': create_sync}[e](template, config[e], out)
	#
	return out
#
#
#
def store(data, fname, split=' '):
        with open(fname, 'w') as text_file:
                text_file.write(split.join(data))
#
#
data = create(TEMPLATE, CONFIG)

#data = template()
#
#data = add_outirc(data, INPUT_CFG["wide"])
##
#data = add_extensions(data, '-o irc -r zezito@', ':6667/canalzito --local luizito@')
##
#store(data, '/tmp/out')
#
print data