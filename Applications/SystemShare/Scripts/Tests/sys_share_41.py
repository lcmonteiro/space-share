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
			'delay':6000, 'sleep':1000, 'pack-size':8, 'lifetime':100, 'live':1, 'verbose':2
		},
		'input':{
			'type':'file', 'uri':INPUT, 'frame-size':300, 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:5001', 'verbose':2
		}
	},
	{
		'name':'2', 'verbose':2,
		'encode':{
			'delay':5900, 'redundancy':4, 'timeout':5000, 'lifetime':5, 'live':2, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:5001', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@citadel.ringoflightning.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@mancubus.zandronum.com:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@solenoid.rizon.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@cronos.xevion.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@minime.fef.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@stardust.nj.us.leaf.chat-solutions.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.stardustfields.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.newit-lan.ru:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@husky.sierranet.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@sandwich.skyirc.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@adonis.powanet.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@space.blafasel.de:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ninjaneering.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@germany.enterthegame.com:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.uk.mibbit.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ssi.bg:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.blafasel.de:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@stopover.ky.us.starlink-irc.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.dopechat.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@overdrive.xertion.org:6667/stream', 'type':'irc', 'verbose':2 }
		]
	},
	{
		'name':'3', 'verbose':2,
		'decode':{
			'delay':800, 'lifetime':10, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@citadel.ringoflightning.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@mancubus.zandronum.com:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@solenoid.rizon.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@cronos.xevion.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@minime.fef.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@stardust.nj.us.leaf.chat-solutions.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.stardustfields.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.newit-lan.ru:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@husky.sierranet.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@sandwich.skyirc.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@adonis.powanet.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@space.blafasel.de:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ninjaneering.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@germany.enterthegame.com:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.uk.mibbit.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ssi.bg:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.blafasel.de:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@stopover.ky.us.starlink-irc.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.dopechat.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@overdrive.xertion.org:6667/stream', 'type':'irc', 'verbose':2 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:7001', 'verbose':2
		}
	},
	{
		'name':'4', 'verbose':2,
		'saving':{
			'delay':700, 'lifetime':10, 'live':6, 'verbose':2
		},
		'input':{
			'type':'tcp', 'pack-size':10, 'frame-size':400, 'uri':'localhost:7001', 'verbose':2
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