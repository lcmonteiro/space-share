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
			{ 'uri':'@sushi.penguinfriends.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.brasirc.com.br:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@comit.electrocode.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@tippett.ringoflightning.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.1chan.us:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.maddshark.com:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@terra.digitalirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@eu.chat4all.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@viper.il.me.irctoo.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc0.zhi.ch.swissirc.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@dreams.deepspace.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@aquarius.deepspace.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@valhalla.on.ca.chaoticnetworks.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@delphi.sierranet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@yggdrasil.iz-smart.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@good1.eu.relic.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@redechat.virtualife.com.br:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@euroserv.fr.quakenet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.italian-amici.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@hyperion.uk.eu.darenet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.trivialityzone.co.uk:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@tyran.ny.us.afterx.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@pugwash.scuttled.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.retardz.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@tube.paranode.net:6667/stream', 'type':'irc', 'verbose':2 }
		]
	},
	{
		'name':'3', 'verbose':2,
		'decode':{
			'delay':800, 'lifetime':10, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@sushi.penguinfriends.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.brasirc.com.br:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@comit.electrocode.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@tippett.ringoflightning.net:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@irc.1chan.us:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.maddshark.com:6667/stream', 'type':'irc', 'verbose':2 },  
			{ 'uri':'@terra.digitalirc.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@eu.chat4all.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@viper.il.me.irctoo.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc0.zhi.ch.swissirc.net:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@dreams.deepspace.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@aquarius.deepspace.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@valhalla.on.ca.chaoticnetworks.com:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@delphi.sierranet.org:6667/stream', 'type':'irc', 'verbose':2 },
			{ 'uri':'@yggdrasil.iz-smart.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@good1.eu.relic.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@redechat.virtualife.com.br:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@euroserv.fr.quakenet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.italian-amici.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@hyperion.uk.eu.darenet.org:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.trivialityzone.co.uk:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@tyran.ny.us.afterx.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@pugwash.scuttled.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.retardz.net:6667/stream', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@tube.paranode.net:6667/stream', 'type':'irc', 'verbose':2 }
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