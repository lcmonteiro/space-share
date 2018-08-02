#!/usr/bin/env python2
#encoding:UTF-8
#
import sys
sys.path.append('..')
#-----------------------------------------------------------------------------------------------------------------------
# IO
#-----------------------------------------------------------------------------------------------------------------------
INPUT = '/home/monteiro/workspace/m2bee/C++/ShareSpace/Applications/SystemShare/Test/test.png'
#
OUTPUT = '/tmp/out'
#-----------------------------------------------------------------------------------------------------------------------
# main
#-----------------------------------------------------------------------------------------------------------------------
from sys_share import process
#
#-----------------------------------------------------------------------------------------------------------------------
# main
#-----------------------------------------------------------------------------------------------------------------------
process([
	{	
		'name':'1', 'verbose':2,
		'encode':{
			'delay':1000, 'lives':1, 'lifetime':10, 'redundancy':5, 'verbose':2
		},
		'input':{
			'type':'file', 'uri':INPUT, 'pack-size':10, 'frame-size':4000, 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:5001', 'verbose':2
		}
	},
	{
		'name':'2', 'verbose':2,
		'encode':{
			'delay':500, 'lives':1, 'lifetime':10, 'redundancy':5, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:5001', 'pack-size':10, 'frame-size':400, 'verbose':2
		},
		'output':{
			'type':'file', 'uri':'/tmp/out1.coded', 'verbose':2
		}
	},
	{
		'name':'3', 'verbose':2,
		'decode':{
			'delay':40000, 'lifetime':10
		},
		'input':{
			'type':'file', 'uri':'/tmp/out1.coded', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:6001', 'verbose':2
		}
	},
	{
		'name':'4', 'verbose':2,
		'decode':{
			'delay':39500, 'lifetime':10
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6001', 'verbose':2
		},
		'output':{
			'type':'file', 'uri':OUTPUT, 'verbose':2
		}
	}
])
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
from sys_share_test import check
#
check(INPUT, OUTPUT)