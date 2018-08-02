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
			'lives':0, 'type':'tcp', 'uri':'localhost:5001', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6002', 'pack-size':1, 'frame-size':1000, 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:6001', 'verbose':2
		}
	},
	{
		'name':'21', 'verbose':2,
		'encode':{
			'lives':0, 'redundancy':10, 'verbose':2
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
		'name':'31', 'verbose':2,
		'tpsilon':{
			'lives':0, 'type':'tcp', 'uri':'localhost:8001', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:7001', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:9001', 'verbose':2
		}
	},
	{
		'name':'32', 'verbose':2,
		'tpsilon':{
			'lives':0, 'type':'tcp', 'uri':'localhost:8002', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:7002', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:9002', 'verbose':2
		}
	},
	{
		'name':'33', 'verbose':2,
		'tpsilon':{
			'lives':0, 'type':'tcp', 'uri':'localhost:8003', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:7003', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:9003', 'verbose':2
		}
	},
	{
		'name':'34', 'verbose':2,
		'tpsilon':{
			'lives':0, 'type':'tcp', 'uri':'localhost:8004', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:7004', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:9004', 'verbose':2
		}
	},
	{
		'name':'41', 'verbose':2,
		'decode':{
			'lives':0, 'verbose':2
		},
		'input':[
			{'type':'tcp', 'uri':'localhost:9001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:9002', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:9003', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:9004', 'verbose':2}
		],
		'output':{
			'type':'tcp', 'uri':'localhost:6002', 'verbose':2
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
	},
	{
		'name':'52', 'verbose':5,
		'ypsilon':{
			'lives':0, 'type':'tcp', 'uri':'localhost:8002', 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:10002', 'verbose':5
		},
		'output':{
			'type':'tcp', 'uri':'localhost:10002', 'verbose':5
		}
	},
	{
		'name':'53', 'verbose':5,
		'ypsilon':{
			'lives':0, 'type':'tcp', 'uri':'localhost:8003', 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:10003', 'verbose':5
		},
		'output':{
			'type':'tcp', 'uri':'localhost:10003', 'verbose':5
		}
	},
	{
		'name':'54', 'verbose':5,
		'ypsilon':{
			'lives':0, 'type':'tcp', 'uri':'localhost:8004', 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:10004', 'verbose':5
		},
		'output':{
			'type':'tcp', 'uri':'localhost:10004', 'verbose':5
		}
	}
])
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
from sys_share_test import check
#
check(INPUT, OUTPUT)