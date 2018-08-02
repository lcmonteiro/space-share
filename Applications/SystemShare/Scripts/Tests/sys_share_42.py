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
			{ 'uri':'@hyperion.eagles-myirc.de:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@a.irc.somenet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@nebula.uk.eu.darkmyst.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@services.serenity-irc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@catastrophe.esper.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@chicago.il.us.chatnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@dirtbox.scenep2p.net:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@burstfire.uk.eu.gamesurge.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@hivane.geeknode.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@tetris.allrednc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@defiant.geekshed.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@us.irc.ghostsirc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@kestrel.uk.afternet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@alpha.fr.eu.obsidianirc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@arm.globalirc.it:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@rotterdam.nl.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@procrastinate.idlechat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@nc.d-t-net.de:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@atlantis.magicstar.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@mandalore.st-city.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.unibg.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@logitech.webcastsonline.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@clarent.nc.us.irchighway.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@dragonite.ca.dragonirc.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@monster.va.us.synirc.net:6667/stream', 'type':'irc', 'verbose':2 }
		]
	},
	{
		'name':'3', 'verbose':2,
		'decode':{
			'delay':800, 'lifetime':10, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@hyperion.eagles-myirc.de:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@a.irc.somenet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@nebula.uk.eu.darkmyst.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@services.serenity-irc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@catastrophe.esper.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@chicago.il.us.chatnet.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@dirtbox.scenep2p.net:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@burstfire.uk.eu.gamesurge.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@hivane.geeknode.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@tetris.allrednc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@defiant.geekshed.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@us.irc.ghostsirc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@kestrel.uk.afternet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@alpha.fr.eu.obsidianirc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@arm.globalirc.it:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@rotterdam.nl.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@procrastinate.idlechat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@nc.d-t-net.de:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@atlantis.magicstar.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@mandalore.st-city.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.unibg.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@logitech.webcastsonline.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@clarent.nc.us.irchighway.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@dragonite.ca.dragonirc.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@monster.va.us.synirc.net:6667/stream', 'type':'irc', 'verbose':2 }
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