#!/usr/bin/env python2
#encoding:UTF-8
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
process([
	{
		'name':'1', 'verbose':5,
		'loading':{
			'delay':1000, 'lives':1, 'sleep':500, 'pack-size':2, 'verbose':5
		},
		'input':{
			'type':'file', 'uri':INPUT, 'frame-size':400, 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:5001', 'verbose':2
		}
	},
	{
		'name':'2', 'verbose':5,
		'encode':{
			'delay':900, 'redundancy':10, 'lives':1, 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:5001', 'pack-size':10, 'frame-size':400, 'verbose':5
		},
		'output':[
			{'type':'tcp', 'uri':'localhost:6001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6002', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6003', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6004', 'verbose':2}
		]
	},
	{
		'name':'3', 'verbose':5,
		'decode':{
			'delay':800, 'lives':1, 'lifetime':10, 'verbose':5
		},
		'input':[
			{'type':'tcp', 'uri':'localhost:6001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6002', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6003', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6004', 'verbose':2}
		],
		'output':{
			'type':'tcp', 'uri':'localhost:7001'
		}
	},
	{
		'name':'4', 'verbose':5,
		'saving':{
			'delay':700, 'lives':1, 'lifetime':30, 'verbose':5
		},
		'input':{
			'type':'tcp', 'pack-size':10, 'frame-size':400, 'uri':'localhost:7001', 'verbose':2
		},
		'output':{
			'type':'file', 'uri':OUTPUT , 'verbose':2
		}
	}
])
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
from sys_share_test import check
#
check(INPUT, OUTPUT)