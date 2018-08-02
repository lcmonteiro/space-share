#!/usr/bin/env python2
#encoding:UTF-8
#
import sys
sys.path.append('..')
#-----------------------------------------------------------------------------------------------------------------------
# IO
#-----------------------------------------------------------------------------------------------------------------------
INPUT = ''
#
OUTPUT = ''
#-----------------------------------------------------------------------------------------------------------------------
# main
#-----------------------------------------------------------------------------------------------------------------------
from sys_share import process
#
process([
	{
		'name':'1', 'verbose':2,
		'encode':{
			'delay':1000, 'redundancy':10, 'verbose':2
		},
		'input':{
			'type':'udp', 'uri':INPUT, 'pack-size':10, 'frame-size':4000, 'verbose':2
		},
		'output':[
			{'type':'tcp', 'uri':'localhost:6001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6002', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6003', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6005', 'verbose':2}
		]
	},
	{
		'name':'2', 'verbose':2,
		'decode':{
			'delay':900, 'verbose':2
		},
		'input':[
			{'type':'tcp', 'uri':'localhost:6001', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6002', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6003', 'verbose':2},
			{'type':'tcp', 'uri':'localhost:6004', 'verbose':2}
		],
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