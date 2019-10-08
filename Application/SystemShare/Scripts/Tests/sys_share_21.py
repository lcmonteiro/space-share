#!/usr/bin/env python2
#encoding:UTF-8
#
import sys
sys.path.append('..')
#-----------------------------------------------------------------------------------------------------------------------
# IO
#-----------------------------------------------------------------------------------------------------------------------
INPUT = '/home/monteiro/workspace/m2bee/C++/ShareSpace/Applications/SystemShare/Test/test.png'
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
			'type':'file', 'uri':'/tmp/out.data', 'verbose':2
		}
	},
	{
		'name':'2', 'verbose':2,
		'saving':{
			'delay':15000
		},
		'input':{
			'type':'file', 'pack-size':10, 'frame-size':4000, 'uri':'/tmp/out.data', 'verbose':2
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