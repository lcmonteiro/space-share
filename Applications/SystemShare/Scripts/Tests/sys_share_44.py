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
			{ 'uri':'@irc.brasport.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@shadow.qc.ca.nextirc.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.hashmark.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@axiom.bigfurs.com:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.redenorte.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@cosmicfire.mi.us.krono.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@london.uk.eu.starlink.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@gazduiretm.ny.us.nextirc.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.tomsk.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@mercury.il.us.dynastynet.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@chicago.il.us.starlink.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@aperture.esper.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@maple.on.ca.darkmyst.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@maki.luatic.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@stats.appliedirc.com:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.sylnt.us:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ruby.exchat.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@denhaag.nl.eu.asylumnet.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@godzilla.jp.p2p-network.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.exolia.net:6667/stream', 'type':'irc', 'verbose':2 }
		]
	},
	{
		'name':'3', 'verbose':2,
		'decode':{
			'delay':800, 'lifetime':10, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@irc.brasport.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@shadow.qc.ca.nextirc.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.hashmark.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@axiom.bigfurs.com:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.redenorte.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@cosmicfire.mi.us.krono.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@london.uk.eu.starlink.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@gazduiretm.ny.us.nextirc.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.tomsk.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@mercury.il.us.dynastynet.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@chicago.il.us.starlink.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@aperture.esper.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@maple.on.ca.darkmyst.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@maki.luatic.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@stats.appliedirc.com:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.sylnt.us:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ruby.exchat.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@denhaag.nl.eu.asylumnet.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@godzilla.jp.p2p-network.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.exolia.net:6667/stream', 'type':'irc', 'verbose':2 }
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