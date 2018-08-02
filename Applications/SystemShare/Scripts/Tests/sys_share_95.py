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
		'name':'111', 'verbose':2,
		'ypsilon':{
			'lives':0, 'type':'tcp', 'uri':'localhost:5001', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6002', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:6001', 'verbose':2
		}
	},
	{
		'name':'121', 'verbose':2,
		'encode':{
			'lives':0, 'redundancy':4, 'verbose':2
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
		'name':'131', 'verbose':2,
		'decode':{
			'lives':0, 'verbose':2
		},
		'input':[
			{'type':'tcp', 'uri':'localhost:8001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:8002', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:8003', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:8004', 'verbose':2}
		],
		'output':{
			'type':'tcp', 'uri':'localhost:6002', 'verbose':2
		}
	},
	{
		'name':'141', 'verbose':2,
		'tpsilon':{
			'lives':0, 'type':'irc', 'uri':'@husky.sierranet.org:6667/stream', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:7001', 'verbose':2
		},
		'output':{	
			'type':'tcp', 'uri':'localhost:8001', 'verbose':2
		}
	},
	{
		'name':'142', 'verbose':2,
		'tpsilon':{
			'lives':0, 'type':'irc', 'uri':'@space.blafasel.de:6667/stream', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:7002', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:8002', 'verbose':2
		}
	},
	{
		'name':'143', 'verbose':2,
		'tpsilon':{
			'lives':0, 'type':'irc', 'uri':'@neptune.betachat.net:6667/stream', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:7003', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:8003', 'verbose':2
		}
	},
	{
		'name':'144', 'verbose':2,
		'tpsilon':{
			'lives':0, 'type':'irc', 'uri':'@overdrive.xertion.org:6667/stream', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:7004', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:8004', 'verbose':2
		}
	},
	
	
	{
		'name':'211', 'verbose':2,
		'ypsilon':{
			'delay':5000, 'lives':0, 'type':'tcp', 'uri':'localhost:5002', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:9002', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:9001', 'verbose':2
		}
	},
	{
		'name':'221', 'verbose':2,
		'encode':{
			'delay':5000, 'lives':0, 'redundancy':4, 'verbose':2
		},
		'input':{
			'delay':5000, 'type':'tcp', 'uri':'localhost:9001', 'pack-size':20, 'frame-size':10, 'verbose':2
		},
		'output':[
			{'type':'tcp', 'uri':'localhost:10001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:10002', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:10003', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:10004', 'verbose':2}
		]
	},
	{
		'name':'231', 'verbose':2,
		'decode':{
			'delay':5000, 'lives':0, 'verbose':2
		},
		'input':[
			{'type':'tcp', 'uri':'localhost:11001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:11002', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:11003', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:11004', 'verbose':2}
		],
		'output':{
			'type':'tcp', 'uri':'localhost:9002', 'verbose':2
		}
	},
	{
		'name':'241', 'verbose':2,
		'tpsilon':{
			'delay':5000, 'lives':0, 'type':'irc', 'uri':'@husky.sierranet.org:6667/stream', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:10001', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:11001', 'verbose':2
		}
	},
	{
		'name':'242', 'verbose':2,
		'tpsilon':{
			'delay':5000, 'lives':0, 'type':'irc', 'uri':'@space.blafasel.de:6667/stream', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:10002', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:11002', 'verbose':2
		}
	},
	{
		'name':'243', 'verbose':2,
		'tpsilon':{
			'delay':5000, 'lives':0, 'type':'irc', 'uri':'@neptune.betachat.net:6667/stream', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:10003', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:11003', 'verbose':2
		}
	},
	{
		'name':'244', 'verbose':2,
		'tpsilon':{
			'delay':5000, 'lives':0, 'type':'irc', 'uri':'@overdrive.xertion.org:6667/stream', 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:10004', 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:11004', 'verbose':2
		}
	}
])
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
from sys_share_test import check
#
check(INPUT, OUTPUT)