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
		'name':'1', 'verbose':2,
		'loading':{
			'delay':1000, 'pack-size':10
		},
		'input':{
			'type':'file', 'uri':INPUT, 'frame-size':4000, 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:4001', 'verbose':2
		}
	},
	{
		'name':'2', 'verbose':2,
		'encode':{
			'delay':900, 'redundancy':10, 'lifetime':2, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:4001', 'pack-size':10, 'frame-size':4000, 'verbose':2
		},
		'output':[
			{'type':'tcp', 'uri':'localhost:5001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:5002', 'verbose':2}
		]
	},
	{
		'name':'3', 'verbose':2,
		'encode':{
			'delay':500, 'redundancy':10, 'lifetime':2, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:5001', 'pack-size':10, 'frame-size':400, 'verbose':2
		},
		'output':{
			'type':'file', 'uri':'/tmp/out1.coded', 'verbose':2
		}
	},
	{
		'name':'4', 'verbose':2,
		'encode':{
			'delay':500, 'redundancy':10, 'lifetime':2, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:5002', 'pack-size':10, 'frame-size':400, 'verbose':2
		},
		'output':{
			'type':'file', 'uri':'/tmp/out2.coded', 'verbose':2
		}
	},
	{
		'name':'5', 'verbose':2,
		'decode':{
			'delay':25000, 'lifetime':10
		},
		'input':{
			'type':'file', 'uri':'/tmp/out1.coded', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:6001', 'verbose':2
		}
	},
	{
		'name':'6', 'verbose':2,
		'decode':{
			'delay':25000, 'lifetime':10, 
		},
		'input':{
			'type':'file', 'uri':'/tmp/out2.coded', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:6002', 'verbose':2
		}
	},
	{
		'name':'7', 'verbose':2,
		'decode':{
			'delay':24500, 'lifetime':10
		},
		'input':[
			{'type':'tcp', 'uri':'localhost:6001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6002', 'verbose':2}
		],
		'output':{
			'type':'tcp', 'uri':'localhost:7001'
		}
	},
	{
		'name':'8', 'verbose':2,
		'saving':{
			'delay':23900, 'lifetime':10
		},
		'input':{
			'type':'tcp', 'pack-size':10, 'frame-size':4000, 'uri':'localhost:7001', 'verbose':2
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