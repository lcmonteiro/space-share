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
                'name': '11', 'verbose':2,
		'encode':{
			'delay':1000, 'redundancy':5, 'verbose':2
		},
		'input':{
			'type':'file', 'uri':INPUT, 'pack-size':10, 'frame-size':4000, 'verbose':2
		},
		'output':[
			{'type':'tcp', 'uri':'localhost:5001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:5002', 'verbose':2}
		]
	},
	{
                'name': '12','verbose':2,
		'encode':{
			'delay':500, 'redundancy':5, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:5001', 'pack-size':10, 'frame-size':400, 'verbose':2
		},
		'output':{
			'type':'file', 'uri':'/tmp/out1.coded', 'verbose':2
		}
	},
	{
                'name': '13','verbose':2,
		'encode':{
			'delay':500, 'redundancy':5, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:5002', 'pack-size':10, 'frame-size':400, 'verbose':2
		},
		'output':{
			'type':'file', 'uri':'/tmp/out2.coded', 'verbose':2
		}
	},
	{
                'name': '21', 'verbose':2,
		'decode':{
			'delay':75000, 'lifetime':10, 'verbose':5
		},
		'input':{
			'type':'file', 'uri':'/tmp/out1.coded', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:6001', 'verbose':2
		}
	},
	{
                'name': '22', 'verbose':2,
		'decode':{
			'delay':75000, 'lifetime':10, 'verbose':5
		},
		'input':{
			'type':'file', 'uri':'/tmp/out2.coded', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:6002', 'verbose':2
		}
	},
	{
                'name': '23', 'verbose':2,
		'decode':{
			'delay':74500, 'lifetime':10, 'verbose':5
		},
		'input':[
			{'type':'tcp', 'uri':'localhost:6001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6002', 'verbose':2}
		],
		'output':{
			'type':'file', 'uri':OUTPUT
		}
	}
])
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
from sys_share_test import check
#
check(INPUT, OUTPUT)