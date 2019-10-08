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
		'name':'--1', 'verbose':0,
		'loading':{
			'delay':30000, 'sleep':1000, 'timeout':5000, 'pack-size':1, 'lifetime':100, 'live':1, 'verbose':0
		},
		'input':{
			'type':'file', 'uri':INPUT, 'frame-size':1500, 'verbose':0
		},
		'output':{
			'type':'tcp', 'uri':'localhost:5001', 'verbose':0
		}
	}, {
		'name':'--2', 'verbose':0,
		'encode':{
			'delay':5900, 'redundancy':2, 'timeout':10000, 'lifetime':10, 'lives':3, 'verbose':0
		},
		'input':{
			'type':'tcp', 'uri':'localhost:5001', 'pack-size':10, 'frame-size':4000, 'verbose':0
		},
		'output':[
			{'type':'tcp', 'uri':'localhost:6001', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:6002', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:6003', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:6004', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:6005', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:6006', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:6007', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:6008', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:6009', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:6010', 'verbose':0}
		]
	}, {
		'name':'-11', 'verbose':0,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':30000, 'lifetime':10, 'live':3, 'verbose':0
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6001', 'pack-size':15, 'frame-size':300, 'verbose':0
		},
		'output':[
			{ 'uri':'@citadel.ringoflightning.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@mancubus.zandronum.com:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@solenoid.rizon.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@cronos.xevion.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@minime.fef.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@stardust.nj.us.leaf.chat-solutions.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.stardustfields.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.newit-lan.ru:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@husky.sierranet.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@sandwich.skyirc.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@adonis.powanet.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@space.blafasel.de:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.ninjaneering.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@germany.enterthegame.com:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.uk.mibbit.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.ssi.bg:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.blafasel.de:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@stopover.ky.us.starlink-irc.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.dopechat.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@overdrive.xertion.org:6667/stream', 'type':'irc', 'verbose':0 }
		]
	}, {
		'name':'-12', 'verbose':0,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':30000, 'lifetime':10, 'live':3, 'verbose':0
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6002', 'pack-size':15, 'frame-size':300, 'verbose':0
		},
		'output':[
			{ 'uri':'@hyperion.eagles-myirc.de:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@a.irc.somenet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@services.serenity-irc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@catastrophe.esper.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@chicago.il.us.chatnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@dirtbox.scenep2p.net:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@burstfire.uk.eu.gamesurge.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@tetris.allrednc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@defiant.geekshed.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@us.irc.ghostsirc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@kestrel.uk.afternet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@alpha.fr.eu.obsidianirc.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@rotterdam.nl.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@procrastinate.idlechat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@nc.d-t-net.de:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@atlantis.magicstar.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@mandalore.st-city.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.unibg.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@logitech.webcastsonline.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@clarent.nc.us.irchighway.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@dragonite.ca.dragonirc.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@monster.va.us.synirc.net:6667/stream', 'type':'irc', 'verbose':0 }
		]
	}, {
		'name':'-13', 'verbose':0,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':30000, 'lifetime':10, 'live':3, 'verbose':0
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6003', 'pack-size':15, 'frame-size':300, 'verbose':0
		},
		'output':[
			{ 'uri':'@neptune.betachat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.brasilirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.chateuropa.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.global-radio.ch:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@weedsmoka.ladysclub-irc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.ryukyu.ad.jp:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@b.irc.somenet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@shire.digitalirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@lynx.furnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.chaterz.nl:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@roubaix.fr.epiknet.org:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@irc.perm.ru:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@xdcc.scenep2p.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@aceraceae.subluminal.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.data.lt:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@metric.ie.eu.afterx.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.genscripts.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@jherer2.chillnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@andromede.europnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@services.penguinfriends.org:6667/stream', 'type':'irc', 'verbose':0 }
		]
	}, {
		'name':'-14', 'verbose':0,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':30000, 'lifetime':10, 'live':3, 'verbose':0
	},
		'input':{
			'type':'tcp', 'uri':'localhost:6004', 'pack-size':15, 'frame-size':300, 'verbose':0
		},
		'output':[
			{ 'uri':'@irc.brasport.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@shadow.qc.ca.nextirc.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.hashmark.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@axiom.bigfurs.com:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.redenorte.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@cosmicfire.mi.us.krono.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@london.uk.eu.starlink.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@gazduiretm.ny.us.nextirc.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.tomsk.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@mercury.il.us.dynastynet.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@chicago.il.us.starlink.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@aperture.esper.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@maple.on.ca.darkmyst.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@maki.luatic.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@stats.appliedirc.com:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.sylnt.us:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@ruby.exchat.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@denhaag.nl.eu.asylumnet.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@godzilla.jp.p2p-network.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.exolia.net:6667/stream', 'type':'irc', 'verbose':0 }
		]
	}, {
		'name':'-15', 'verbose':0,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':30000, 'lifetime':10, 'live':3, 'verbose':0
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6005', 'pack-size':15, 'frame-size':300, 'verbose':0
		},
		'output':[ 
			{ 'uri':'@irc.bluntchat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.odessa.ua:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@tampa.fl.us.roirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@mars.pa.us.dynastynet.net:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@irc.fewona.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.run.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@sigsegv.teranova.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@poischiche.fr.eu.netrusk.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@bigben.uk.p2p-network.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.goodfuck.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.metairc.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@paintball.tx.us.globalgamers.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@axa.id.as.auxnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@dome.ringoflightning.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@incognito.ca.us.austnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@nehalem.de.afternet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.icestarirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@online-dc3.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.nlnog.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@linux.globalirc.it:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.inet.tele.dk:6667/stream', 'type':'irc', 'verbose':0 }
		]
	}, {
		'name':'-16', 'verbose':0,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':30000, 'lifetime':10, 'live':3, 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6006', 'pack-size':15, 'frame-size':300, 'verbose':0
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
			{ 'uri':'@services.ptnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@vega.nj.us.mixxnet.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@stormlight.esper.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@nm.jawug.org.za:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@light.wa.us.swiftirc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.i-tna.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@hub.jawug.org.za:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@talis.powanet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.ben64.com:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@losangeles.ca.us.starlink.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@underworld.se.eu.dal.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@omega.uk.eu.synirc.net:6667/stream', 'type':'irc', 'verbose':0 }
		]
	}, {
		'name':'-17', 'verbose':0,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':30000, 'lifetime':10, 'live':3, 'verbose':0
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6007', 'pack-size':15, 'frame-size':300, 'verbose':0
		},
		'output':[
			{ 'uri':'@yuzuki.surrealchat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
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
		'name':'-18', 'verbose':0,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':30000, 'lifetime':10, 'live':3, 'verbose':0
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6008', 'pack-size':15, 'frame-size':300, 'verbose':0
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
		'name':'-19', 'verbose':0,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':30000, 'lifetime':10, 'live':3, 'verbose':0
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6009', 'pack-size':15, 'frame-size':300, 'verbose':0
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
			{ 'uri':'@senseless.xevion.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.x2x.cc:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@oslo.no.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@baltimore.md.us.exilenet.org:6667/stream', 'type':'irc', 'verbose':0 }
		]
	}, {
		'name':'-20', 'verbose':0,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':30000, 'lifetime':10, 'live':3, 'verbose':0
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6010', 'pack-size':15, 'frame-size':300, 'verbose':0
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
		'name':'101', 'verbose':0,
		'saving':{
			'delay':500, 'timeout':20000, 'lifetime':10, 'live':10, 'verbose':0
		},
		'input':{
			'type':'tcp', 'pack-size':10, 'frame-size':400, 'uri':'localhost:7001', 'verbose':0
		},
		'output':{
			'type':'file', 'uri':OUTPUT , 'verbose':0
		}
	}, {
		'name':'102', 'verbose':0,
		'decode':{
			'delay':1000, 'timeout':40000, 'lifetime':10, 'live':10, 'verbose':0
		},
		'input':[	
			{'type':'tcp', 'uri':'localhost:8001', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:8002', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:8003', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:8004', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:8005', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:8006', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:8007', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:8008', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:8009', 'verbose':0},
			{'type':'tcp', 'uri':'localhost:8010', 'verbose':0}
		],
		'output':{
			'type':'tcp', 'uri':'localhost:7001', 'verbose':0
		}
	}, {
		'name':'111', 'verbose':0,
		'decode':{
			'delay':1000, 'timeout':30000, 'lifetime':10, 'live':10, 'verbose':0
		},
		'input':[
			{ 'uri':'@citadel.ringoflightning.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@mancubus.zandronum.com:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@solenoid.rizon.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@cronos.xevion.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@minime.fef.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@stardust.nj.us.leaf.chat-solutions.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.stardustfields.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.newit-lan.ru:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@husky.sierranet.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@sandwich.skyirc.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@adonis.powanet.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@space.blafasel.de:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.ninjaneering.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@germany.enterthegame.com:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.uk.mibbit.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.ssi.bg:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.blafasel.de:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@stopover.ky.us.starlink-irc.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.dopechat.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@overdrive.xertion.org:6667/stream', 'type':'irc', 'verbose':0 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8001', 'verbose':0
		}
	}, {
		'name':'112', 'verbose':0,
		'decode':{
			'delay':1000, 'timeout':30000, 'lifetime':10, 'live':10, 'verbose':0
		},
		'input':[
			{ 'uri':'@hyperion.eagles-myirc.de:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@a.irc.somenet.org:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@services.serenity-irc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@catastrophe.esper.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@chicago.il.us.chatnet.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@dirtbox.scenep2p.net:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@burstfire.uk.eu.gamesurge.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@tetris.allrednc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@defiant.geekshed.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@us.irc.ghostsirc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@kestrel.uk.afternet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@alpha.fr.eu.obsidianirc.net:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@rotterdam.nl.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@procrastinate.idlechat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@nc.d-t-net.de:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@atlantis.magicstar.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@mandalore.st-city.net:6667/stream', 'type':'irc', 'verbose':0 },  
			{ 'uri':'@irc.unibg.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@logitech.webcastsonline.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@clarent.nc.us.irchighway.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@dragonite.ca.dragonirc.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@monster.va.us.synirc.net:6667/stream', 'type':'irc', 'verbose':0 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8002', 'verbose':0
		}
	}, {
		'name':'113', 'verbose':0,
		'decode':{
			'delay':1000, 'timeout':30000, 'lifetime':10, 'live':10, 'verbose':0
		},
		'input':[
			{ 'uri':'@neptune.betachat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.brasilirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.chateuropa.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.global-radio.ch:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@weedsmoka.ladysclub-irc.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.ryukyu.ad.jp:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@b.irc.somenet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@shire.digitalirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@lynx.furnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.chaterz.nl:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@roubaix.fr.epiknet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.perm.ru:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@xdcc.scenep2p.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@aceraceae.subluminal.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.data.lt:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@metric.ie.eu.afterx.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.genscripts.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@jherer2.chillnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@andromede.europnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@services.penguinfriends.org:6667/stream', 'type':'irc', 'verbose':0 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8003', 'verbose':0
		}
	}, {
		'name':'114', 'verbose':0,
		'decode':{
			'delay':1000, 'timeout':30000, 'lifetime':10, 'live':10, 'verbose':0
		},
		'input':[
			{ 'uri':'@irc.brasport.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@shadow.qc.ca.nextirc.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.hashmark.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@axiom.bigfurs.com:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.redenorte.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@cosmicfire.mi.us.krono.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@london.uk.eu.starlink.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@gazduiretm.ny.us.nextirc.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.tomsk.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@mercury.il.us.dynastynet.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@chicago.il.us.starlink.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@aperture.esper.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@maple.on.ca.darkmyst.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@maki.luatic.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@stats.appliedirc.com:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.sylnt.us:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@ruby.exchat.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@denhaag.nl.eu.asylumnet.org:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@godzilla.jp.p2p-network.net:6667/stream', 'type':'irc', 'verbose':0 },
			{ 'uri':'@irc.exolia.net:6667/stream', 'type':'irc', 'verbose':0 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8004', 'verbose':0
		}
	}, {
		'name':'115', 'verbose':0,
		'decode':{
			'delay':1000, 'timeout':30000, 'lifetime':10, 'live':10, 'verbose':0
		},
		'input':[
			{ 'uri':'@irc.bluntchat.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.odessa.ua:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@tampa.fl.us.roirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@mars.pa.us.dynastynet.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.fewona.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.run.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@sigsegv.teranova.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@poischiche.fr.eu.netrusk.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@bigben.uk.p2p-network.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.goodfuck.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.metairc.com:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@paintball.tx.us.globalgamers.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@axa.id.as.auxnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@dome.ringoflightning.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@incognito.ca.us.austnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@nehalem.de.afternet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.icestarirc.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@online-dc3.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.nlnog.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@linux.globalirc.it:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.inet.tele.dk:6667/stream', 'type':'irc', 'verbose':0 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8005', 'verbose':0
		}
	}, {
		'name':'116', 'verbose':5,
		'decode':{
			'delay':1000, 'timeout':30000, 'lifetime':10, 'live':10, 'verbose':0
		},
		'input':[
			{ 'uri':'@cricinfo.uk.eu.starlink.org:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@home.n00bstories.com:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@efnet.port80.se:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@moople.kbfail.net:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@nerim.fr.eu.evolu.net:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@irc.rizon.no:6667/stream', 'type':'irc', 'verbose':5 },  
			{ 'uri':'@fortitude.purplesurge.com:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@calohjin.mantrairc.net:6667/stream', 'type':'irc', 'verbose':5 },
			{ 'uri':'@thalassa.portalx.org:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@critical.relic.net:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@services.ptnet.org:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@vega.nj.us.mixxnet.net:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@stormlight.esper.net:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@nm.jawug.org.za:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@light.wa.us.swiftirc.net:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@irc.i-tna.org:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@hub.jawug.org.za:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@talis.powanet.org:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@irc.ben64.com:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@losangeles.ca.us.starlink.org:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@underworld.se.eu.dal.net:6667/stream', 'type':'irc', 'verbose':5 }, 
			{ 'uri':'@omega.uk.eu.synirc.net:6667/stream', 'type':'irc', 'verbose':5 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8006', 'verbose':0
		}
	}, {
		'name':'117', 'verbose':0,
		'decode':{
			'delay':1000, 'timeout':30000, 'lifetime':10, 'live':10, 'verbose':0
		},
		'input':[
			{ 'uri':'@yuzuki.surrealchat.net:6667/stream', 'type':'irc', 'verbose':0 },
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
			'type':'tcp', 'uri':'localhost:8007', 'verbose':0
		}
	}, {
		'name':'118', 'verbose':0,
		'decode':{
			'delay':1000, 'timeout':30000, 'lifetime':10, 'live':10, 'verbose':0
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
			'type':'tcp', 'uri':'localhost:8008', 'verbose':0
		}
	}, {
		'name':'119', 'verbose':0,
		'decode':{
			'delay':1000, 'timeout':30000, 'lifetime':10, 'live':10, 'verbose':0
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
			{ 'uri':'@senseless.xevion.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.x2x.cc:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@oslo.no.eu.neko-net.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@baltimore.md.us.exilenet.org:6667/stream', 'type':'irc', 'verbose':0 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8009', 'verbose':0
		}
	}, {
		'name':'120', 'verbose':0,
		'decode':{
			'delay':1000, 'timeout':30000, 'lifetime':10, 'live':10, 'verbose':0
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
			{ 'uri':'@brain.de.eu.phat-net.de:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@noodle.irc.ecnet.org:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@osgiliath.va.us.chatabout.net:6667/stream', 'type':'irc', 'verbose':0 }, 
			{ 'uri':'@irc.ewnix.net:6667/stream', 'type':'irc', 'verbose':0 }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8010', 'verbose':0
		}
	}
])
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
from sys_share_test import check
#
check(INPUT, OUTPUT)