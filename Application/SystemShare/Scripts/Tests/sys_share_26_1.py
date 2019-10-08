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
			'loading':{
				'delay':1000, 'pack-size':10, 'lives':1
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
				'delay':900, 'redundancy':5, 'lives':1, 'verbose':2
			},
			'input':{
				'type':'tcp', 'uri':'localhost:4001', 'pack-size':10, 'frame-size':4000, 'verbose':2
			},
			'output':[
				{'type':'tcp', 'uri':'localhost:5001', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:5002', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:5003', 'verbose':2}
			]
		},
		{
			'name':'3', 'verbose':2,
			'encode':{
				'delay':800, 'redundancy':5, 'lifetime':2, 'lives':1, 'verbose':2
			},
			'input':{
				'type':'tcp', 'uri':'localhost:5001', 'pack-size':10, 'frame-size':400, 'verbose':2
			},
			'output':[
				{'type':'tcp', 'uri':'localhost:6001', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6002', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6003', 'verbose':2}
			]
		},
		{
			'name':'4', 'verbose':2,
			'encode':{
				'delay':800, 'redundancy':5, 'lifetime':2, 'lives':1, 'verbose':2
			},
			'input':{
				'type':'tcp', 'uri':'localhost:5002', 'pack-size':10, 'frame-size':400, 'verbose':2
			},
			'output':[
				{'type':'tcp', 'uri':'localhost:6004', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6005', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6006', 'verbose':2}
			]
		},
		{
			'name':'5', 'verbose':2,
			'encode':{
				'delay':800, 'redundancy':5, 'lifetime':2, 'lives':1, 'verbose':2
			},
			'input':{
				'type':'tcp', 'uri':'localhost:5003', 'pack-size':10, 'frame-size':400, 'verbose':2
			},
			'output':[
				{'type':'tcp', 'uri':'localhost:6007', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6008', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6009', 'verbose':2}
			]
		},
		{
			'name':'6', 'verbose':2,
			'decode':{
				'delay':700, 'lifetime':3, 'verbose':2
			},
			'input':[
				{'type':'tcp', 'uri':'localhost:6001', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6002', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6003', 'verbose':2}
			],
			'output':{
				'type':'tcp', 'uri':'localhost:7001', 'verbose':2
			}
		},
		{
			'name':'7', 'verbose':2,
			'decode':{
				'delay':700, 'lifetime':3, 'verbose':2
			},
			'input':[
				{'type':'tcp', 'uri':'localhost:6004', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6005', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6006', 'verbose':2}
			],
			'output':{
				'type':'tcp', 'uri':'localhost:7002', 'verbose':2
			}
		},
		{
			'name':'8', 'verbose':2,
			'decode':{
				'delay':700, 'lifetime':3, 'verbose':2
			},
			'input':[
				{'type':'tcp', 'uri':'localhost:6007', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6008', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:6009', 'verbose':2}
			],
			'output':{
				'type':'tcp', 'uri':'localhost:7003', 'verbose':2
			}
		},
		{
			'name':'9', 'verbose':2,
			'decode':{
				'delay':600, 'lifetime':6, 'verbose':2
			},
			'input':[
				{'type':'tcp', 'uri':'localhost:7001', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:7002', 'verbose':2},
				{'type':'tcp', 'uri':'localhost:7003', 'verbose':2}
			],
			'output':{
				'type':'tcp', 'uri':'localhost:8001'
			}
		},
		{
			'name':'10', 'verbose':2,
			'saving':{
				'delay':500, 'lifetime':9, 'lives':1, 'verbose':2
			},
			'input':{
				'type':'tcp', 'pack-size':10, 'frame-size':4000, 'uri':'localhost:8001', 'verbose':2
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
#