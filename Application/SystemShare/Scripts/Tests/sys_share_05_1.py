#!/usr/bin/env python2
#encodin:UTF-8
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
from sys_share_test import check
from sys_share_test import check_size
#
i = 0
while True:
	i += 1
	print 'process', i
	#
	encode = {
		'name':'1', 'verbose':2,
		'encode':{
			'delay':10, 'redundancy':5, 'pass':'luis', 'verbose':2
		},
		'input':{
			'type':'file', 'uri':INPUT, 'pack-size':50, 'frame-size':1000, 'verbose':2
		},
		'output':[
			{'type':'file', 'uri':'/tmp/out1.coded', 'verbose':2},
			{'type':'file', 'uri':'/tmp/out2.coded', 'verbose':2}
		]
	}
	decode = {
		'name':'2', 'verbose':1,
		'decode':{
			'timeout':500, 'delay':2500, 'pass':'luis', 'verbose':2
		},
		'input':[
			{'type':'file', 'uri':'/tmp/out1.coded', 'verbose':2},
			{'type':'file', 'uri':'/tmp/out2.coded', 'verbose':2}
		],
		'output':{
			'type':'file', 'uri':OUTPUT, 'verbose':2
		}
	}
#	process([decode])
	process([encode, decode])
#	try:
#		check_size(['/tmp/out1.coded', '/tmp/out2.coded'])
#	except:
#		print 'except check size'
#		process([encode, decode])
	#
#	check(INPUT, OUTPUT)
	try:
		check(INPUT, OUTPUT)
	except:
		print 'except check'
		process([decode])
		#
		check(INPUT, OUTPUT)
	#
#