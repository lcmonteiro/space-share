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
#
i=0
#
while True:
	i+=1
	print 'iteration=', i
	#-----------------------------------------------------------------------------------------------------------------------
	# main
	#-----------------------------------------------------------------------------------------------------------------------
	from sys_share import process
	#
	process([
		{
			'name':'1', 'verbose':2,
			'encode':{
				'delay':1000, 'type':'stream', 'redundancy':2, 'verbose':2
			},
			'input':{
				'type':'file', 'uri':INPUT, 'pack-size':30, 'frame-size':400, 'verbose':2
			},
			'output':[
				{'type':'tcp', 'uri':'localhost:6001', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6002', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6003', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6004', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6005', 'verbose':2}
			]
		},
		{
			'name':'2', 'verbose':2,
			'decode':{
				'delay':800, 'type':'stream', 'verbose':2
			},
			'input':[
				{'type':'tcp', 'uri':'localhost:6001', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6002', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6003', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6004', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6005', 'verbose':2}
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
#