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
		'ypsilon':{
			'delay':1000, 'lives':0, 'type':'tcp', 'uri':'localhost:5001', 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6001', 'pack-size':1, 'frame-size':1000, 'verbose':5
		},
		'output':{
			'type':'tcp', 'uri':'localhost:6002', 'verbose':5
		}
	},
	{
		'name':'2', 'verbose':5,
		'ypsilon':{
			'delay':1000, 'lives':0, 'type':'tcp', 'uri':'localhost:5002', 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6002', 'pack-size':1, 'frame-size':1000, 'verbose':5
		},
		'output':{
			'type':'tcp', 'uri':'localhost:6001', 'verbose':5
		}
	}
])
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
from sys_share_test import check
#
check(INPUT, OUTPUT)