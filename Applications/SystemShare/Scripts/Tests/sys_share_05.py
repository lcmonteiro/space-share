#!/usr/bin/env python2
#encodin:UTF-8
#
import sys
sys.path.append('..')
#-----------------------------------------------------------------------------------------------------------------------
# IO
#-----------------------------------------------------------------------------------------------------------------------
INPUT = '/home/monteiro/workspace/m2bee/C++/ShareSpace/Applications/SystemShare/Test/test.bmp'
#
OUTPUT = '/tmp/out'
#-----------------------------------------------------------------------------------------------------------------------
# main
#-----------------------------------------------------------------------------------------------------------------------
from sys_share import process
#
encode = {
	'name':'1', 'verbose':2,
	'encode':{
		'delay':10, 'redundancy':5, 'pass':'luis', 'verbose':2
	},
	'input':{
		'type':'file', 'uri':INPUT, 'pack-size':50, 'frame-size':1000, 'verbose':2
	},
	'output':[
		{'type':'file', 'uri':'/tmp/out1.coded', 'verbose':2},
		{'type':'file', 'uri':'/tmp/out2.coded', 'verbose':2}
	]
}
decode = {
	'name':'2', 'verbose':1,
	'decode':{
		'timeout':500, 'delay':4500, 'pass':'luis', 'verbose':2
	},
	'input':[
		{'type':'file', 'uri':'/tmp/out1.coded', 'verbose':2},
		{'type':'file', 'uri':'/tmp/out2.coded', 'verbose':2}
	],
	'output':{
		'type':'file', 'uri':OUTPUT, 'verbose':2
	}
}
process([encode, decode])
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
from sys_share_test import check
#
check(INPUT, OUTPUT)