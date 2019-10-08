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
			{ 'uri':'@cricinfo.uk.eu.starlink.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@home.n00bstories.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@efnet.port80.se:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@moople.kbfail.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@nerim.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.rizon.no:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@fortitude.purplesurge.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@calohjin.mantrairc.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@thalassa.portalx.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@critical.relic.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@verne.freenode.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@services.ptnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@vega.nj.us.mixxnet.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@stormlight.esper.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@nm.jawug.org.za:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@light.wa.us.swiftirc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.i-tna.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@hub.jawug.org.za:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@talis.powanet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.ben64.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@world.globalirc.it:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@anvil.nj.us.serenity-irc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@losangeles.ca.us.starlink.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@underworld.se.eu.dal.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@omega.uk.eu.synirc.net:6667/stream', 'type':'irc', 'verbose':2 }
		]
	},
	{
		'name':'3', 'verbose':2,
		'decode':{
			'delay':800, 'lifetime':10, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@cricinfo.uk.eu.starlink.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@home.n00bstories.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@efnet.port80.se:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@moople.kbfail.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@nerim.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.rizon.no:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@fortitude.purplesurge.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@calohjin.mantrairc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@thalassa.portalx.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@critical.relic.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@verne.freenode.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@services.ptnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@vega.nj.us.mixxnet.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@stormlight.esper.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@nm.jawug.org.za:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@light.wa.us.swiftirc.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.i-tna.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@hub.jawug.org.za:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@talis.powanet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.ben64.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@world.globalirc.it:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@anvil.nj.us.serenity-irc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@losangeles.ca.us.starlink.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@underworld.se.eu.dal.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@omega.uk.eu.synirc.net:6667/stream', 'type':'irc', 'verbose':2 }
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