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
		'name':'11', 'verbose':5,
		'ypsilon':{
			'lives':0, 'type':'tcp', 'uri':'localhost:5001', 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6002', 'pack-size':1, 'frame-size':1000, 'verbose':5
		},
		'output':{
			'type':'tcp', 'uri':'localhost:6001', 'verbose':5
		}
	},
	{
		'name':'21', 'verbose':5,
		'encode':{
			'lives':0, 'redundancy':10, 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6001', 'pack-size':20, 'frame-size':10, 'verbose':5
		},
		'output':[
			{'type':'tcp', 'uri':'localhost:7001', 'verbose':5}
		]
	},
	{
		'name':'31', 'verbose':5,
		'tpsilon':{
			'lives':0, 'type':'tcp', 'uri':'localhost:8001', 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:7001', 'verbose':5
		},
		'output':{
			'type':'tcp', 'uri':'localhost:9001', 'verbose':5
		}
	},
	{
		'name':'41', 'verbose':5,
		'decode':{
			'lives':0, 'verbose':5
		},
		'input':[
			{'type':'tcp', 'uri':'localhost:9001', 'verbose':5}
		],
		'output':{
			'type':'tcp', 'uri':'localhost:6002', 'verbose':5
		}
	},
	{
		'name':'51', 'verbose':5,
		'ypsilon':{
			'lives':0, 'type':'tcp', 'uri':'localhost:8001', 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:10001', 'verbose':5
		},
		'output':{
			'type':'tcp', 'uri':'localhost:10001', 'verbose':5
		}
	}
])
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
from sys_share_test import check
#
check(INPUT, OUTPUT)