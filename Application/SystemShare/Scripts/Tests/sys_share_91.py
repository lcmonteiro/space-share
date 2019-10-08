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
		'name':'11', 'verbose':2,
		'ypsilon':{
			'delay':1000, 'lives':0, 'type':'tcp', 'uri':'localhost:5001', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:8002', 'pack-size':1, 'frame-size':1000, 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:6001', 'verbose':2
		}
	},
	{
		'name':'12', 'verbose':2,
		'encode':{
			'delay':1000, 'lives':0, 'redundancy':10, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6001', 'pack-size':20, 'frame-size':10, 'verbose':2
		},
		'output':[
			{'type':'tcp', 'uri':'localhost:7001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:7002', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:7003', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:7004', 'verbose':2}
		]
	},
	{
		'name':'13', 'verbose':2,
		'decode':{
			'delay':900, 'lives':0, 'verbose':2
		},
		'input':[
			{'type':'tcp', 'uri':'localhost:7001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:7002', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:7003', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:7004', 'verbose':2}
		],
		'output':{
			'type':'tcp', 'uri':'localhost:6002', 'verbose':2
		}
	},
	{
		'name':'21', 'verbose':2,
		'ypsilon':{
			'delay':1000, 'lives':0, 'type':'tcp', 'uri':'localhost:5002', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6002',  'pack-size':1, 'frame-size':1000, 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:8001', 'verbose':2
		}
	},
		{
		'name':'22', 'verbose':2,
		'encode':{
			'delay':1000, 'lives':0, 'redundancy':10, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:8001', 'pack-size':20, 'frame-size':10, 'verbose':2
		},
		'output':[
			{'type':'tcp', 'uri':'localhost:9001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:9002', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:9003', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:9004', 'verbose':2}
		]
	},
	{
		'name':'23', 'verbose':2,
		'decode':{
			'delay':900, 'lives':0, 'verbose':2
		},
		'input':[
			{'type':'tcp', 'uri':'localhost:9001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:9002', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:9003', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:9004', 'verbose':2}
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8002', 'verbose':2
		}
	}
])
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
from sys_share_test import check
#
check(INPUT, OUTPUT)