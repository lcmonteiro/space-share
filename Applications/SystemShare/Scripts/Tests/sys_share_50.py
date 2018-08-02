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
			'delay':5900, 'redundancy':4, 'timeout':5000, 'lifetime':5, 'live':10, 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:5001', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@gaia.sorcery.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@hannibal.chaoz-irc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@outrun.foreverchat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.irule.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@nuclearfallout.wa.us.gamesurge.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@romania.netirc.eu:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@spaniels.slashnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@amistad.ma.us.starchat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@cantillon.be.eu.blitzed.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@ursa.nj.us.darkvoltage.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@pacifik.andromeda.fr:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.echo34.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@cheetah.anthrochat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.0f.se:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.ionic.at:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@cenedra.langochat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@moo.slashnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@tchat.andromeda.fr:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@gra-1.chat-irc.fr:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@crowley.anonnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.maxfraud.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@lion.sg.p2p-network.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@brain.de.eu.phat-net.de:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@noodle.irc.ecnet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@osgiliath.va.us.chatabout.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.ewnix.net:6667/stream', 'type':'irc', 'verbose':2 }
		]
	},
	{
		'name':'3', 'verbose':5,
		'decode':{
			'delay':800, 'timeout':5000, 'lifetime':10, 'live':10, 'verbose':5
		},
		'input':[
			{ 'uri':'@gaia.sorcery.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@hannibal.chaoz-irc.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@outrun.foreverchat.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ "uri":"@irc.irule.net:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@nuclearfallout.wa.us.gamesurge.net:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@romania.netirc.eu:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@spaniels.slashnet.org:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@amistad.ma.us.starchat.net:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@cantillon.be.eu.blitzed.org:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@ursa.nj.us.darkvoltage.net:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@pacifik.andromeda.fr:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@irc.echo34.com:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@cheetah.anthrochat.net:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@irc.0f.se:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@irc.ionic.at:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@cenedra.langochat.net:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@moo.slashnet.org:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@tchat.andromeda.fr:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@gra-1.chat-irc.fr:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@crowley.anonnet.org:6667/stream", "type":"irc", "verbose":2 },  
			{ "uri":"@irc.maxfraud.com:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@lion.sg.p2p-network.net:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@brain.de.eu.phat-net.de:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@noodle.irc.ecnet.org:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@osgiliath.va.us.chatabout.net:6667/stream", "type":"irc", "verbose":2 }, 
			{ "uri":"@irc.ewnix.net:6667/stream", "type":"irc", "verbose":2 }
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