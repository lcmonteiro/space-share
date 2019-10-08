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
	# --------------------------------------------------------------------------------------------------------------
	#						Encode
	# --------------------------------------------------------------------------------------------------------------
	{
		'name':'--1', 'verbose':2,
		'loading':{
			'delay':30000, 'sleep':1000, 'timeout':5000, 'pack-size':1, 'lifetime':100, 'live':1, 'verbose':2
		},
		'input':{
			'type':'file', 'uri':INPUT, 'frame-size':1500, 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:5001', 'verbose':5
		}
	}, {
		'name':'--2', 'verbose':2,
		'encode':{
			'delay':5900, 'redundancy':1, 'timeout':10000, 'lifetime':10, 'lives':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:5001', 'pack-size':5, 'frame-size':4000, 'verbose':5
		},
		'output':[
			{'type':'tcp', 'uri':'localhost:6001', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6002', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6003', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6004', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6005', 'verbose':5}
		]
	}, {
		'name':'-11', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6001', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@cricinfo.uk.eu.starlink.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@home.n00bstories.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@efnet.port80.se:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@moople.kbfail.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@nerim.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.rizon.no:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@fortitude.purplesurge.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@calohjin.mantrairc.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@thalassa.portalx.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@critical.relic.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@verne.freenode.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@services.ptnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@vega.nj.us.mixxnet.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@stormlight.esper.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@nm.jawug.org.za:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@light.wa.us.swiftirc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.i-tna.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@hub.jawug.org.za:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@talis.powanet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.ben64.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@world.globalirc.it:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@anvil.nj.us.serenity-irc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@losangeles.ca.us.starlink.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@underworld.se.eu.dal.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@omega.uk.eu.synirc.net:6667/stream', 'type':'irc', 'verbose':0 }
		]
	}, {
		'name':'-12', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6002', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@yuzuki.surrealchat.net:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@ljubljana.si.eu.irchaven.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@jedi.geeksandgamers.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.mikrovisata.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@london.globalirc.it:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@leviathan.freedom2irc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@frankfurt.de.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@nugget.digitalirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.europeirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@maple.nl.eu.gtanet.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@sinisalo.freenode.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@cgiirc.langochat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@freedom.lostirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@fantasya.europnet.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@triagia.drlnet.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@trinkhalle.bullet-irc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.sibptus.ru:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@embyr.tx.us.fyrechat.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@420.us.p2p-network.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@lithium.subluminal.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@sayuri.otaku-irc.fr:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@netsplit.pirc.pl:6667/stream', 'type':'irc', 'verbose':0 }
		]
	}, {
		'name':'-13', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6003', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@sushi.penguinfriends.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.brasirc.com.br:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@comit.electrocode.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@tippett.ringoflightning.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.1chan.us:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.maddshark.com:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@terra.digitalirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@eu.chat4all.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@viper.il.me.irctoo.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc0.zhi.ch.swissirc.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@dreams.deepspace.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@aquarius.deepspace.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@valhalla.on.ca.chaoticnetworks.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@delphi.sierranet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@yggdrasil.iz-smart.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@good1.eu.relic.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@redechat.virtualife.com.br:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@euroserv.fr.quakenet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.italian-amici.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@hyperion.uk.eu.darenet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.trivialityzone.co.uk:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@tyran.ny.us.afterx.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@pugwash.scuttled.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.retardz.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@tube.paranode.net:6667/stream', 'type':'irc', 'verbose':0 }
		]
	}, {
		'name':'-14', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6004', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@services.lichtsnel.nl:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@strasbourg.nationchat.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@circe.sorcery.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@mundo.powerfriends.es:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.sailirc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@strawberry.xchannel.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.data.bg:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@ranma.ftee.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc2.chattersweb.nl:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@tauri.aureaworld.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@sonatadusk.ponychat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@fdn.geeknode.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@earth.sa-irc.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@celestin.fr.ircube.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@khisanth.otherworlders.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@online-dc2.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.eqemulator.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@wilhelm.freenode.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.danusya.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@senseless.xevion.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.x2x.cc:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@abyss.no.eu.darkmyst.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@oslo.no.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@baltimore.md.us.exilenet.org:6667/stream', 'type':'irc', 'verbose':0 }
		]
	}, {
		'name':'-15', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6005', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@gaia.sorcery.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@hannibal.chaoz-irc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@outrun.foreverchat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.irule.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@nuclearfallout.wa.us.gamesurge.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@romania.netirc.eu:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@spaniels.slashnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@amistad.ma.us.starchat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@cantillon.be.eu.blitzed.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@ursa.nj.us.darkvoltage.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@pacifik.andromeda.fr:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.echo34.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@cheetah.anthrochat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.0f.se:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.ionic.at:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@cenedra.langochat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@moo.slashnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@tchat.andromeda.fr:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@gra-1.chat-irc.fr:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@crowley.anonnet.org:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@irc.maxfraud.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@lion.sg.p2p-network.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@brain.de.eu.phat-net.de:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@noodle.irc.ecnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@osgiliath.va.us.chatabout.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.ewnix.net:6667/stream', 'type':'irc', 'verbose':0 }
		]
	},
	# --------------------------------------------------------------------------------------------------------------
	#						Decode
	# --------------------------------------------------------------------------------------------------------------
	{
		'name':'101', 'verbose':2,
		'saving':{
			'delay':500, 'timeout':20000, 'lifetime':10, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'pack-size':10, 'frame-size':400, 'uri':'localhost:7001', 'verbose':2
		},
		'output':{
			'type':'file', 'uri':OUTPUT , 'verbose':2
		}
	}, {
		'name':'102', 'verbose':2,
		'decode':{
			'delay':1000, 'timeout':10000, 'lifetime':20, 'live':1, 'verbose':2
		},
		'input':[	
		{'type':'tcp', 'uri':'localhost:8001', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:8002', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:8003', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:8004', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:8005', 'verbose':5}
		],
		'output':{
			'type':'tcp', 'uri':'localhost:7001', 'verbose':5
		}
	}, {
		'name':'111', 'verbose':2,
		'decode':{
			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':[
			{ 'uri':'@cricinfo.uk.eu.starlink.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@home.n00bstories.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@efnet.port80.se:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@moople.kbfail.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@nerim.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.rizon.no:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@fortitude.purplesurge.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@calohjin.mantrairc.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@thalassa.portalx.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@critical.relic.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@verne.freenode.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@services.ptnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@vega.nj.us.mixxnet.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@stormlight.esper.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@nm.jawug.org.za:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@light.wa.us.swiftirc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.i-tna.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@hub.jawug.org.za:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@talis.powanet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.ben64.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@world.globalirc.it:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@anvil.nj.us.serenity-irc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@losangeles.ca.us.starlink.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@underworld.se.eu.dal.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@omega.uk.eu.synirc.net:6667/stream', 'type':'irc', 'verbose':0 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8001', 'verbose':2
		}
	}, {
		'name':'112', 'verbose':2,
		'decode':{
			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':[
			{ 'uri':'@yuzuki.surrealchat.net:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@ljubljana.si.eu.irchaven.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@jedi.geeksandgamers.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.mikrovisata.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@london.globalirc.it:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@leviathan.freedom2irc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@frankfurt.de.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@nugget.digitalirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.europeirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@maple.nl.eu.gtanet.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@sinisalo.freenode.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@cgiirc.langochat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@freedom.lostirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@fantasya.europnet.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@triagia.drlnet.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@trinkhalle.bullet-irc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.sibptus.ru:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@embyr.tx.us.fyrechat.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@420.us.p2p-network.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@lithium.subluminal.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@sayuri.otaku-irc.fr:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@netsplit.pirc.pl:6667/stream', 'type':'irc', 'verbose':0 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8002', 'verbose':2
		}
	}, {
		'name':'113', 'verbose':2,
		'decode':{
			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':[
			{ 'uri':'@sushi.penguinfriends.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.brasirc.com.br:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@comit.electrocode.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@tippett.ringoflightning.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.1chan.us:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.maddshark.com:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@terra.digitalirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@eu.chat4all.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@viper.il.me.irctoo.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc0.zhi.ch.swissirc.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@dreams.deepspace.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@aquarius.deepspace.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@valhalla.on.ca.chaoticnetworks.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@delphi.sierranet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@yggdrasil.iz-smart.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@good1.eu.relic.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@redechat.virtualife.com.br:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@euroserv.fr.quakenet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.italian-amici.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@hyperion.uk.eu.darenet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.trivialityzone.co.uk:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@tyran.ny.us.afterx.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@pugwash.scuttled.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.retardz.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@tube.paranode.net:6667/stream', 'type':'irc', 'verbose':0 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8003', 'verbose':2
		}
	}, {
		'name':'114', 'verbose':2,
		'decode':{
			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':[
			{ 'uri':'@services.lichtsnel.nl:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@strasbourg.nationchat.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@circe.sorcery.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@mundo.powerfriends.es:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.sailirc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@strawberry.xchannel.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.data.bg:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@ranma.ftee.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc2.chattersweb.nl:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@tauri.aureaworld.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@sonatadusk.ponychat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@fdn.geeknode.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@earth.sa-irc.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@celestin.fr.ircube.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@khisanth.otherworlders.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@online-dc2.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.eqemulator.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@wilhelm.freenode.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.danusya.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@senseless.xevion.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.x2x.cc:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@abyss.no.eu.darkmyst.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@oslo.no.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@baltimore.md.us.exilenet.org:6667/stream', 'type':'irc', 'verbose':0 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8004', 'verbose':2
		}
	}, {
		'name':'115', 'verbose':2,
		'decode':{
			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':[
			{ 'uri':'@gaia.sorcery.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@hannibal.chaoz-irc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@outrun.foreverchat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.irule.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@nuclearfallout.wa.us.gamesurge.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@romania.netirc.eu:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@spaniels.slashnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@amistad.ma.us.starchat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@cantillon.be.eu.blitzed.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@ursa.nj.us.darkvoltage.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@pacifik.andromeda.fr:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.echo34.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@cheetah.anthrochat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.0f.se:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.ionic.at:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@cenedra.langochat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@moo.slashnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@tchat.andromeda.fr:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@gra-1.chat-irc.fr:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@crowley.anonnet.org:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@irc.maxfraud.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@lion.sg.p2p-network.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@brain.de.eu.phat-net.de:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@noodle.irc.ecnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@osgiliath.va.us.chatabout.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.ewnix.net:6667/stream', 'type':'irc', 'verbose':0 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8005', 'verbose':2
		}
	}
])
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
from sys_share_test import check
#
check(INPUT, OUTPUT)