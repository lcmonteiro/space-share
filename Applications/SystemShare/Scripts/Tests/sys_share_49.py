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
		'name':'2', 'verbose':5,
		'encode':{
			'delay':5900, 'redundancy':4, 'timeout':5000, 'lifetime':5, 'live':10, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:5001', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@services.lichtsnel.nl:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@strasbourg.nationchat.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@circe.sorcery.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@mundo.powerfriends.es:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.sailirc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@strawberry.xchannel.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.data.bg:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@ranma.ftee.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc2.chattersweb.nl:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@tauri.aureaworld.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@sonatadusk.ponychat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@fdn.geeknode.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@earth.sa-irc.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@celestin.fr.ircube.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@khisanth.otherworlders.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@online-dc2.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.eqemulator.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@wilhelm.freenode.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.danusya.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@senseless.xevion.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.x2x.cc:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@abyss.no.eu.darkmyst.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@oslo.no.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@baltimore.md.us.exilenet.org:6667/stream', 'type':'irc', 'verbose':2 }
		]
	},
	{
		'name':'3', 'verbose':5,
		'decode':{
			'delay':800, 'lifetime':10, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@services.lichtsnel.nl:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@strasbourg.nationchat.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@circe.sorcery.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@mundo.powerfriends.es:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@irc.sailirc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@strawberry.xchannel.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.data.bg:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@ranma.ftee.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc2.chattersweb.nl:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@tauri.aureaworld.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@sonatadusk.ponychat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@fdn.geeknode.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@earth.sa-irc.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@celestin.fr.ircube.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@khisanth.otherworlders.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@online-dc2.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@irc.eqemulator.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@wilhelm.freenode.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.danusya.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@senseless.xevion.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.x2x.cc:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@abyss.no.eu.darkmyst.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@oslo.no.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@baltimore.md.us.exilenet.org:6667/stream', 'type':'irc', 'verbose':2 }
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