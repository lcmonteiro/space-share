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
		'encode':{
			'delay':1000, 'redundancy':10, 'pass':'luis', 'verbose':2
		},
		'input':{
			'type':'file', 'uri':INPUT, 'pack-size':10, 'frame-size':4000, 'verbose':2
		},
		'output':[
			{'type':'file', 'uri':'/tmp/out1.coded', 'verbose':2},
			{'type':'file', 'uri':'/tmp/out2.coded', 'verbose':2}
		]
	},
	{
		'decode':{
			'delay':10000, 'pass':'luis', 'verbose':2
		},
		'input':[
			{'type':'file', 'uri':'/tmp/out1.coded', 'verbose':2},
			{'type':'file', 'uri':'/tmp/out2.coded', 'verbose':2}
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