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
			{ 'uri':'@neptune.betachat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.brasilirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.chateuropa.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.global-radio.ch:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@weedsmoka.ladysclub-irc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.ryukyu.ad.jp:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@b.irc.somenet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@shire.digitalirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@lynx.furnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.chaterz.nl:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@roubaix.fr.epiknet.org:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@irc.perm.ru:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@xdcc.scenep2p.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@aceraceae.subluminal.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.data.lt:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@metric.ie.eu.afterx.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.genscripts.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@jherer2.chillnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@andromede.europnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@services.penguinfriends.org:6667/stream', 'type':'irc', 'verbose':2 }
		]
	},
	{
		'name':'3', 'verbose':2,
		'decode':{
			'delay':800, 'lifetime':10, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@neptune.betachat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.brasilirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.chateuropa.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.global-radio.ch:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@weedsmoka.ladysclub-irc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.ryukyu.ad.jp:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@b.irc.somenet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@shire.digitalirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@lynx.furnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.chaterz.nl:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@roubaix.fr.epiknet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.perm.ru:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@xdcc.scenep2p.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@aceraceae.subluminal.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.data.lt:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@metric.ie.eu.afterx.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.genscripts.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@jherer2.chillnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@andromede.europnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@services.penguinfriends.org:6667/stream', 'type':'irc', 'verbose':2 }
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