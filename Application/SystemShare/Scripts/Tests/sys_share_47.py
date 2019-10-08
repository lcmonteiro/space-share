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
			{ 'uri':'@yuzuki.surrealchat.net:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@ljubljana.si.eu.irchaven.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@jedi.geeksandgamers.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.mikrovisata.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@london.globalirc.it:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@leviathan.freedom2irc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@frankfurt.de.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@nugget.digitalirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.europeirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@maple.nl.eu.gtanet.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@sinisalo.freenode.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@cgiirc.langochat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@freedom.lostirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@fantasya.europnet.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@triagia.drlnet.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@trinkhalle.bullet-irc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.sibptus.ru:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@embyr.tx.us.fyrechat.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@420.us.p2p-network.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@lithium.subluminal.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@sayuri.otaku-irc.fr:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@netsplit.pirc.pl:6667/stream', 'type':'irc', 'verbose':2 }
		]
	},
	{
		'name':'3', 'verbose':2,
		'decode':{
			'delay':800, 'lifetime':10, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@yuzuki.surrealchat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@ljubljana.si.eu.irchaven.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@jedi.geeksandgamers.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.mikrovisata.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@london.globalirc.it:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@leviathan.freedom2irc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@frankfurt.de.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@nugget.digitalirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.europeirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@maple.nl.eu.gtanet.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@sinisalo.freenode.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@cgiirc.langochat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@freedom.lostirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@fantasya.europnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@triagia.drlnet.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@trinkhalle.bullet-irc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.sibptus.ru:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@embyr.tx.us.fyrechat.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@420.us.p2p-network.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@lithium.subluminal.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@sayuri.otaku-irc.fr:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@netsplit.pirc.pl:6667/stream', 'type':'irc', 'verbose':2 }
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