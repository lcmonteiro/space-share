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
			{ 'uri':'@rochester.mi.us.starlink-irc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.bluntchat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.odessa.ua:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@pegasus.il.us.darkmyst.org:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@tampa.fl.us.roirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@mars.pa.us.dynastynet.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@dallas.tx.us.irchaven.org:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@irc.fewona.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.run.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@sigsegv.teranova.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@poischiche.fr.eu.netrusk.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@bigben.uk.p2p-network.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.goodfuck.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@windy.us.p2p-network.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.metairc.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@paintball.tx.us.globalgamers.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@axa.id.as.auxnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@dome.ringoflightning.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@incognito.ca.us.austnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@nehalem.de.afternet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.icestarirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@online-dc3.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.nlnog.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@linux.globalirc.it:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.inet.tele.dk:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@rajaniemi.freenode.net:6667/stream', 'type':'irc', 'verbose':2 }
		]
	},
	{
		'name':'3', 'verbose':2,
		'decode':{
			'delay':800, 'lifetime':10, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@rochester.mi.us.starlink-irc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.bluntchat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.odessa.ua:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@pegasus.il.us.darkmyst.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@tampa.fl.us.roirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@mars.pa.us.dynastynet.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@dallas.tx.us.irchaven.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.fewona.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.run.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@sigsegv.teranova.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@poischiche.fr.eu.netrusk.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@bigben.uk.p2p-network.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.goodfuck.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@windy.us.p2p-network.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.metairc.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@paintball.tx.us.globalgamers.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@axa.id.as.auxnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@dome.ringoflightning.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@incognito.ca.us.austnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@nehalem.de.afternet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.icestarirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@online-dc3.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.nlnog.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@linux.globalirc.it:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.inet.tele.dk:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@rajaniemi.freenode.net:6667/stream', 'type':'irc', 'verbose':2 }
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