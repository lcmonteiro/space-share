#!/usr/bin/env python2
#encoding:UTF-8
#
import sys
sys.path.append('..')
#-----------------------------------------------------------------------------------------------------------------------
# IO
#-----------------------------------------------------------------------------------------------------------------------
INPUT = '/home/monteiro/workspace/m2bee/C++/ShareSpace/Applications/SystemShare/Test/test.bmp'
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
			'type':'file', 'uri':INPUT, 'frame-size':4000, 'verbose':2
		},
		'output':{
			'type':'tcp', 'uri':'localhost:5001', 'verbose':5
		}
	}, {
		'name':'--2', 'verbose':2,
		'encode':{
			'delay':5900, 'type':'full', 'redundancy':3, 'timeout':10000, 'lifetime':10, 'lives':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:5001', 'pack-size':14, 'frame-size':4000, 'verbose':5
		},
		'output':[
			{'type':'tcp', 'uri':'localhost:6001', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6002', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6003', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6004', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6005', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6006', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6007', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6008', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6009', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6010', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6011', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6012', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6013', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6014', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6015', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6016', 'verbose':5},
			{'type':'tcp', 'uri':'localhost:6017', 'verbose':5}
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
			{ 'uri':'@cricinfo.uk.eu.starlink.org:6667/locateL', 'type':'irc', 'verbose':2 },
			{ 'uri':'@home.n00bstories.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@efnet.port80.se:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@moople.kbfail.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@nerim.fr.eu.evolu.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.rizon.no:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@stats.collectiveirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@calohjin.mantrairc.net:6667/locateL', 'type':'irc', 'verbose':2 },
			{ 'uri':'@thalassa.portalx.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@darkrai.unovarpgnet.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@verne.freenode.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@services.ptnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@vega.nj.us.mixxnet.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.fknbish.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@nm.jawug.org.za:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@light.wa.us.swiftirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.i-tna.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@hub.jawug.org.za:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@talis.powanet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ben64.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@world.globalirc.it:6667/locateL', 'type':'irc', 'verbose':2 },
			{ 'uri':'@anvil.nj.us.serenity-irc.net:6667/locateL', 'type':'irc', 'verbose':2 },
			{ 'uri':'@losangeles.ca.us.starlink.org:6667/locateL', 'type':'irc', 'verbose':2 },
			{ 'uri':'@underworld.se.eu.dal.net:6667/locate', 'type':'irc', 'verbose':2 }
		]
	}, {
		'name':'-12', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6002', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@yuzuki.surrealchat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ljubljana.si.eu.irchaven.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@port80a.se.quakenet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.mikrovisata.net:6667/locateM', 'type':'irc', 'verbose':2 },
			{ 'uri':'@london.globalirc.it:6667/locateM', 'type':'irc', 'verbose':2 },
			{ 'uri':'@leviathan.freedom2irc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@frankfurt.de.eu.neko-net.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@elder.scoutlink.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.europeirc.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@maple.nl.eu.gtanet.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@sinisalo.freenode.net:6667/locateM', 'type':'irc', 'verbose':2 },
			{ 'uri':'@cgiirc.langochat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@freedom.lostirc.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@cora.shadowfire.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@otter.anthrochat.net:6667/locateM', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.brirc.net:6667/locateM', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.sibptus.ru:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@embyr.tx.us.fyrechat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@420.us.p2p-network.net:6667/locateM', 'type':'irc', 'verbose':2 },
			{ 'uri':'@lithium.subluminal.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@sayuri.otaku-irc.fr:6667/locateM', 'type':'irc', 'verbose':2 },
			{ 'uri':'@netsplit.pirc.pl:6667/locate', 'type':'irc', 'verbose':2 }
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
			{ 'uri':'@sushi.penguinfriends.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.tom.ru:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@partyline.mefalcon.de:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@scootaloo.ponychat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.1chan.us:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.maddshark.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@gandi.geeknode.org:6667/locateN', 'type':'irc', 'verbose':2 },
			{ 'uri':'@eu.chat4all.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@viper.il.me.irctoo.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc0.zhi.ch.swissirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@dreams.deepspace.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@aquarius.deepspace.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@valhalla.on.ca.chaoticnetworks.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.chatcafe.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@yggdrasil.iz-smart.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@black.blackznet.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@underworld1.no.quakenet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@euroserv.fr.quakenet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.italian-amici.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@hyperion.uk.eu.darenet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.hagabard.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@coruscant.st-city.net:6667/locateN', 'type':'irc', 'verbose':2 },
			{ 'uri':'@pugwash.scuttled.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.retardz.net:6667/locateN', 'type':'irc', 'verbose':2 },
			{ 'uri':'@tube.paranode.net:6667/locate', 'type':'irc', 'verbose':2 }
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
			{ 'uri':'@irc.boredicons.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@strasbourg.nationchat.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@circe.sorcery.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@frost.fsinf.at:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.evolu7ion.fr:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@strawberry.xchannel.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@falkor.dejatoons.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@belay.foonetic.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc2.chattersweb.nl:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@tauri.aureaworld.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@shifty.realirc.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@fdn.geeknode.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@figarzilla.chateuropa.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@celestin.fr.ircube.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@khisanth.otherworlders.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@online-dc2.fr.eu.evolu.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.eqemulator.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@wilhelm.freenode.net:6667/locateO', 'type':'irc', 'verbose':2 },
			{ 'uri':'@underworld2.no.quakenet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc2.pilgerer.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@morgan.hackint.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@trendy.us.tawx.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@oslo.no.eu.neko-net.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@baltimore.md.us.exilenet.org:6667/locate', 'type':'irc', 'verbose':2 }
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
			{ 'uri':'@gaia.sorcery.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@hannibal.chaoz-irc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@envy.il.us.synirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@twilight.qc.ca.darenet.org:6667/locateP', 'type':'irc', 'verbose':2 },
			{ 'uri':'@nuclearfallout.wa.us.gamesurge.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@romania.netirc.eu:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@spaniels.slashnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@amistad.ma.us.starchat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@cantillon.be.eu.blitzed.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ursa.nj.us.darkvoltage.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@raspi.uplinkcorp.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.echo34.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@cheetah.anthrochat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.0f.se:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ionic.at:6667/locateP', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.reimuhakurei.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@moo.slashnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.pathos.irc-mania.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.barafranca.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@crowley.anonnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.maxfraud.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@lion.sg.p2p-network.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@brain.de.eu.phat-net.de:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.asylo.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@osgiliath.va.us.chatabout.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ewnix.net:6667/locate', 'type':'irc', 'verbose':2 }
		]
	}, {
		'name':'-16', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6006', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@pacific.cn.as.nextirc.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@mancubus.zandronum.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.christianchat.info:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@cronos.xevion.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@uk-hub-1.network.appliedirc.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@gavyn.forumcerdas.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.stardustfields.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.newit-lan.ru:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@eu1.relaxedirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@sandwich.skyirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@adonis.powanet.org:6667/locateQ', 'type':'irc', 'verbose':2 },
			{ 'uri':'@space.blafasel.de:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ircsource.irssi.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.phrenzy.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.uk.mibbit.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.eu.icq-chat.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.blafasel.de:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@zoidberg.us.utonet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ftl.na.dftba.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@saya.otaku-irc.fr:6667/locateQ', 'type':'irc', 'verbose':2 },
			{ 'uri':'@spectral.shadowcat.co.uk:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.degunino.net:6667/locate', 'type':'irc', 'verbose':2 }
		]
	}, {
		'name':'-17', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6007', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@hyperion.eagles-myirc.de:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@a.irc.somenet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@smugglers-bar.mefalcon.de:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@services.serenity-irc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@lion.anthrochat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@chicago.il.us.chatnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@magnet.rizon.net:6667/locateR', 'type':'irc', 'verbose':2 },
			{ 'uri':'@burstfire.uk.eu.gamesurge.net:6667/locateR', 'type':'irc', 'verbose':2 },
			{ 'uri':'@hivane.geeknode.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@tetris.allrednc.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@redhat.globalirc.it:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@us.irc.ghostsirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@kestrel.uk.afternet.org:6667/locateR', 'type':'irc', 'verbose':2 },
			{ 'uri':'@alpha.fr.eu.obsidianirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@arm.globalirc.it:6667/locateR', 'type':'irc', 'verbose':2 },
			{ 'uri':'@rotterdam.nl.eu.neko-net.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.frozen-irc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@nc.d-t-net.de:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@atlantis.magicstar.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@mandalore.st-city.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@omni.irc.omnimaga.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@atlanta.ga.us.starlink.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@clarent.nc.us.irchighway.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@etnies.ca.us.kampungchat.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ember.sorcery.net:6667/locate', 'type':'irc', 'verbose':2 }
		]
	}, {
		'name':'-18', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6008', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@neptune.betachat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.brasilirc.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.chateuropa.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@flux.serverpit.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@chat4.koach.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ryukyu.ad.jp:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@b.irc.somenet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irp.irc.omnimaga.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@lynx.furnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc2.hu:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@roubaix.fr.epiknet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.perm.ru:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.anarxi.st:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.meganet.ru:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.data.lt:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@metric.ie.eu.afterx.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.genscripts.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@jherer2.chillnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@raven.serenia.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@services.penguinfriends.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@tweek.de.inside-irc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.scenecritique.com:6667/locate', 'type':'irc', 'verbose':2 }
		]
	}, {
		'name':'-19', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6009', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@irc.brasport.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@shadow.qc.ca.nextirc.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.hashmark.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@axiom.bigfurs.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.redenorte.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@cosmicfire.mi.us.krono.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@london.uk.eu.starlink.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@gazduiretm.ny.us.nextirc.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.tomsk.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ashburn.va.us.undernet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@chicago.il.us.starlink.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@dungeon.axenet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@timtam.uk.eu.blitzed.org:6667/locateS', 'type':'irc', 'verbose':2 },
			{ 'uri':'@maki.luatic.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@stats.appliedirc.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.sylnt.us:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ruby.exchat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@denhaag.nl.eu.asylumnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@godzilla.jp.p2p-network.netS:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.exolia.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@budapest.hu.eu.undernet.org:6667/locate', 'type':'irc', 'verbose':2},
			{ 'uri':'@irc.infatech.net:6667/locate', 'type':'irc', 'verbose':2}
		]
	}, {
		'name':'-20', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6010', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@hyperion.ie.afternet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@uk.eu.fireirc.co:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.odessa.ua:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@yudum.unitedchat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@tampa.fl.us.roirc.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc2.pilgerer.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@figarzilla.chateuropa.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.fewona.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.run.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.eagle.y.se:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@poischiche.fr.eu.netrusk.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@bigben.uk.p2p-network.net:6667/locateT', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.goodfuck.org:6667/locateT', 'type':'irc', 'verbose':2 },
			{ 'uri':'@windy.us.p2p-network.net:6667/locateT', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.metairc.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@paintball.tx.us.globalgamers.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@axa.id.as.auxnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@river.serenia.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@schoko.blafasel.de:6667/locateT', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.mv.ru:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.icestarirc.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.dal.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.nlnog.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@linux.globalirc.it:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.inet.tele.dk:6667/locateT', 'type':'irc', 'verbose':2 },
			{ 'uri':'@rajaniemi.freenode.net:6667/locateT', 'type':'irc', 'verbose':2 }
		]
	}, {
		'name':'-21', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6011', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@etn.on.ca.mixxnet.net:6667/locateA', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ineffective.idlechat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@denthox.chaterz.nl:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@arizona.us.aceirc.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ircbar.hu.ircline.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@roubaix.fr.whatnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@luna.iz-smart.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.hes.de.euirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@sexy.zoite.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@italia.simosnap.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ca.us.fireirc.co:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@indoshells.forumcerdas.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ircsource.nl:6667/locateA', 'type':'irc', 'verbose':2 },
			{ 'uri':'@amsterdam.nl.eu.scarynet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ircd.underworld.no:6667/locateA', 'type':'irc', 'verbose':2 },
			{ 'uri':'@marisa.seraphimlabs.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc1.pilgerer.org:6667/locateA', 'type':'irc', 'verbose':2 },
			{ 'uri':'@karin.indirectirc.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@pie.ga.paradoxirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.gimp.ca:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@atropine.rc6.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.snyde.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@aesir.sorcery.net:6667/locateA', 'type':'irc', 'verbose':2 }
		]
	}, {
		'name':'-22', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6012', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@devnull.chatopia.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@moka.uk.chaoticnetworks.com:6667/locateB', 'type':'irc', 'verbose':2 },
			{ 'uri':'@port80b.se.quakenet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@icarius.tweakers.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@newyork.nationchat.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@hub.endeavour.rs2i.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@aetos.greekchat.eu:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@raspberry.bug.ch:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@stitch.chatspike.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.unworldly.nl:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ajhenderson.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@muffin.irc.omnimaga.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@wolf.furnet.org:6667/locateB', 'type':'irc', 'verbose':2 },
			{ 'uri':'@rappin.soundsnwaves.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.mgts.by:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ktu.lt:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@tampere.fi.b2irc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@delphini.ga.us.starchat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@alpha.appliedirc.com:6667/locateB', 'type':'irc', 'verbose':2 },
			{ 'uri':'@jeger.binhex.org:6667/locate', 'type':'irc', 'verbose':2 }
		]
	}, {
		'name':'-23', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6013', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@team-irc.w3.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@deep13.psigenix.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@venom.ny.us.darenet.org:6667/locateC', 'type':'irc', 'verbose':2 },
			{ 'uri':'@bacon.utassault.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@forum.nl.eu.globalgamers.net:6667/locateC', 'type':'irc', 'verbose':2 },
			{ 'uri':'@vervet.foonetic.net:6667/locateC', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.datahata.by:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@backup.knightirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@stagsleap.ca.us.blitzed.org:6667/locateC', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.radio-kanaan.de:6667/locateC', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.nandox.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@dalek.panicirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@server1.dream-irc.de:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@choopa.nj.us.dal.net:6667/locateC', 'type':'irc', 'verbose':2 },
			{ 'uri':'@drahelas.forestnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@alicorn.furnet.org:6667/locateC', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc0.qes.ch.swissirc.net:6667/locateC', 'type':'irc', 'verbose':2 },
			{ 'uri':'@frozen.coldfront.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@oslo.no.eu.irclink.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@trigun.dejatoons.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.choopa.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@dynamo.digitalirc.org:6667/locate', 'type':'irc', 'verbose':2 }
		]
	}, {
		'name':'-24', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6014', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@irc.chanfix.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.tsua.net:6667/locateD', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.gentoo.ca:6667/locateD', 'type':'irc', 'verbose':2 },
			{ 'uri':'@warlock.hub.sorcery.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@brussel.chaterz.be:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@services.chatabout.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@halcyon.il.us.dal.net:6667/locateD', 'type':'irc', 'verbose':2 },
			{ 'uri':'@real.irc.bassdrive.com:6667/locateD', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.tribalwar.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@librenet.europnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.delfi.ee:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@chat3.koach.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.zboub.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.wikkedwire.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.caffie.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@eden.evilnet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@mars.inframonde.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@sapphire.sinsira.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.mzima.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@mimir.irc.worldnet.net:6667/locate', 'type':'irc', 'verbose':2 }
		]
	}, {
		'name':'-25', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6015', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@levin.mozilla.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@aurora.irc.arloria.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@martel.seraphimlabs.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc2.yukieiri.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc2.juggler.jp:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@tiki.oceanius.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@stockholm.se.eu.nextirc.org:6667/locateE', 'type':'irc', 'verbose':2 },
			{ 'uri':'@atom.irdsi.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.unitedchat.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.zonebg.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@orwell.freenode.net:6667/locateE', 'type':'irc', 'verbose':2 },
			{ 'uri':'@area51.lostirc.org:6667/locateE', 'type':'irc', 'verbose':2 },
			{ 'uri':'@asgard.skyirc.net:6667/locateE', 'type':'irc', 'verbose':2 },
			{ 'uri':'@stats.pancake-pirates.org:6667/locateE', 'type':'irc', 'verbose':2 },
			{ 'uri':'@chalk.uuid.uk:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@fortaire.mantrairc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@zenith.cpt.za.atrum.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@ariel.chathispano.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@sinclair.irc.arloria.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@armisael.surrealchat.net:6667/locateE', 'type':'irc', 'verbose':2 }
		]
	}, {
		'name':'-26', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6016', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@irc.bol-chat.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@icarus.cpt.za.atrum.org:6667/locateF', 'type':'irc', 'verbose':2 },
			{ 'uri':'@discord.canternet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.us.ircnet.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@blair.xertion.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@7ter-himmel-irc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@chronos.psigenix.net:6667/locateF', 'type':'irc', 'verbose':2 },
			{ 'uri':'@seattle.wa.us.starlink.org:6667/locateF', 'type':'irc', 'verbose':2 },
			{ 'uri':'@chat.delfi.lt:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@mila.nc.us.chaoticnetworks.com:6667/locateF', 'type':'irc', 'verbose':2 },
			{ 'uri':'@bifrost.ca.us.dal.net:6667/locateF', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ss23.geek.nz:6667/locateF', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.seersirc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@laeta.zoite.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@master.spiderchat.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.homo.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ircshack.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.malkier.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@cosmos.snoonet.org:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@kiva3.lugs.ch:6667/locateF', 'type':'irc', 'verbose':2 }
		]
	}, {
		'name':'-27', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':5
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6017', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@islander.uk.eu.nextirc.org:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@polarity.6irc.net:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@icarus.nj.us.globalgamers.net:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.wup.nu:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@elysium.us.ix.undernet.org:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@dropbear.6irc.net:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@wirefull.geeknode.org:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@scale.fr.afternet.org:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@concrete.slashnet.org:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@osmium.uk.afternet.org:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@bofh.nl.smurfnet.ch:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@ganimedes.chathispano.com:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@irc.ukchatbox.org.uk:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@heraklion.ircnet.gr:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc2.xmission.com:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@bia.imaginarynet.uk:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.ircportal.net:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@montreal.qc.ca.nextirc.org:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@coyote.wa.us.starchat.net:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@irc.big-daddy.fr:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@silph.co:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@sundance.6irc.net:6667/locate', 'type':'irc', 'verbose':2 },
			{ 'uri':'@sapphire.exchat.net:6667/locate', 'type':'irc', 'verbose':2 }, 
			{ 'uri':'@asia.unitedchat.net:6667/locate', 'type':'irc', 'verbose':2 }
		]
	}#,
	# --------------------------------------------------------------------------------------------------------------
	#						Decode
	# --------------------------------------------------------------------------------------------------------------
#	{
#		'name':'101', 'verbose':2,
#		'saving':{
#			'delay':500, 'timeout':20000, 'lifetime':10, 'live':1, 'verbose':2
#		},
#		'input':{
#			'type':'tcp', 'pack-size':10, 'frame-size':400, 'uri':'localhost:7001', 'verbose':2
#		},
#		'output':{
#			'type':'file', 'uri':OUTPUT , 'verbose':2
#		}
#	}, {
#		'name':'102', 'verbose':2,
#		'decode':{
#			'delay':1000, 'type':'full', 'timeout':10000, 'lifetime':20, 'live':1, 'verbose':2
#		},
#		'input':[
#			{'type':'tcp', 'uri':'localhost:8001', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8002', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8003', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8004', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8005', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8006', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8007', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8008', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8009', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8010', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8011', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8012', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8013', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8014', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8015', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8016', 'verbose':5},
#			{'type':'tcp', 'uri':'localhost:8017', 'verbose':5}
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:7001', 'verbose':5
#		}
#	}, {
#		'name':'111', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@cricinfo.uk.eu.starlink.org:6667/locateL', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@home.n00bstories.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@efnet.port80.se:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@moople.kbfail.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@nerim.fr.eu.evolu.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.rizon.no:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@stats.collectiveirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@calohjin.mantrairc.net:6667/locateL', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@thalassa.portalx.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@darkrai.unovarpgnet.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@verne.freenode.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@services.ptnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@vega.nj.us.mixxnet.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.fknbish.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@nm.jawug.org.za:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@light.wa.us.swiftirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.i-tna.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@hub.jawug.org.za:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@talis.powanet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.ben64.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@world.globalirc.it:6667/locateL', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@anvil.nj.us.serenity-irc.net:6667/locateL', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@losangeles.ca.us.starlink.org:6667/locateL', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@underworld.se.eu.dal.net:6667/locate', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8001', 'verbose':2
#		}
#	}, {
#		'name':'112', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@yuzuki.surrealchat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ljubljana.si.eu.irchaven.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@port80a.se.quakenet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.mikrovisata.net:6667/locateM', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@london.globalirc.it:6667/locateM', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@leviathan.freedom2irc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@frankfurt.de.eu.neko-net.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@elder.scoutlink.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.europeirc.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@maple.nl.eu.gtanet.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@sinisalo.freenode.net:6667/locateM', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@cgiirc.langochat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@freedom.lostirc.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@cora.shadowfire.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@otter.anthrochat.net:6667/locateM', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.brirc.net:6667/locateM', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.sibptus.ru:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@embyr.tx.us.fyrechat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@420.us.p2p-network.net:6667/locateM', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@lithium.subluminal.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@sayuri.otaku-irc.fr:6667/locateM', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@netsplit.pirc.pl:6667/locate', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8002', 'verbose':2
#		}
#	}, {
#		'name':'113', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@sushi.penguinfriends.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.tom.ru:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@partyline.mefalcon.de:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@scootaloo.ponychat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.1chan.us:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.maddshark.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@gandi.geeknode.org:6667/locateN', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@eu.chat4all.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@viper.il.me.irctoo.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc0.zhi.ch.swissirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@dreams.deepspace.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@aquarius.deepspace.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@valhalla.on.ca.chaoticnetworks.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.chatcafe.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@yggdrasil.iz-smart.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@black.blackznet.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@underworld1.no.quakenet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@euroserv.fr.quakenet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.italian-amici.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@hyperion.uk.eu.darenet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.hagabard.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@coruscant.st-city.net:6667/locateN', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@pugwash.scuttled.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.retardz.net:6667/locateN', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@tube.paranode.net:6667/locate', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8003', 'verbose':2
#		}
#	}, {
#		'name':'114', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@irc.boredicons.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@strasbourg.nationchat.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@circe.sorcery.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@frost.fsinf.at:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.evolu7ion.fr:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@strawberry.xchannel.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@falkor.dejatoons.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@belay.foonetic.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc2.chattersweb.nl:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@tauri.aureaworld.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@shifty.realirc.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@fdn.geeknode.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@figarzilla.chateuropa.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@celestin.fr.ircube.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@khisanth.otherworlders.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@online-dc2.fr.eu.evolu.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.eqemulator.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@wilhelm.freenode.net:6667/locateO', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@underworld2.no.quakenet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc2.pilgerer.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@morgan.hackint.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@trendy.us.tawx.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@oslo.no.eu.neko-net.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@baltimore.md.us.exilenet.org:6667/locate', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8004', 'verbose':2
#		}
#	}, {
#		'name':'115', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@gaia.sorcery.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@hannibal.chaoz-irc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@envy.il.us.synirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@twilight.qc.ca.darenet.org:6667/locateP', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@nuclearfallout.wa.us.gamesurge.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@romania.netirc.eu:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@spaniels.slashnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@amistad.ma.us.starchat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@cantillon.be.eu.blitzed.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ursa.nj.us.darkvoltage.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@raspi.uplinkcorp.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.echo34.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@cheetah.anthrochat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.0f.se:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.ionic.at:6667/locateP', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.reimuhakurei.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@moo.slashnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.pathos.irc-mania.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.barafranca.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@crowley.anonnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.maxfraud.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@lion.sg.p2p-network.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@brain.de.eu.phat-net.de:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.asylo.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@osgiliath.va.us.chatabout.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.ewnix.net:6667/locate', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8005', 'verbose':2
#		}
#	}, {
#		'name':'116', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@pacific.cn.as.nextirc.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@mancubus.zandronum.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.christianchat.info:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@cronos.xevion.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@uk-hub-1.network.appliedirc.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@gavyn.forumcerdas.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.stardustfields.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.newit-lan.ru:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@eu1.relaxedirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@sandwich.skyirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@adonis.powanet.org:6667/locateQ', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@space.blafasel.de:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ircsource.irssi.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.phrenzy.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.uk.mibbit.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.eu.icq-chat.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.blafasel.de:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@zoidberg.us.utonet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ftl.na.dftba.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@saya.otaku-irc.fr:6667/locateQ', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@spectral.shadowcat.co.uk:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.degunino.net:6667/locate', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8006', 'verbose':2
#		}
#	}, {
#		'name':'117', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@hyperion.eagles-myirc.de:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@a.irc.somenet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@smugglers-bar.mefalcon.de:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@services.serenity-irc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@lion.anthrochat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@chicago.il.us.chatnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@magnet.rizon.net:6667/locateR', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@burstfire.uk.eu.gamesurge.net:6667/locateR', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@hivane.geeknode.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@tetris.allrednc.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@redhat.globalirc.it:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@us.irc.ghostsirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@kestrel.uk.afternet.org:6667/locateR', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@alpha.fr.eu.obsidianirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@arm.globalirc.it:6667/locateR', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@rotterdam.nl.eu.neko-net.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.frozen-irc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@nc.d-t-net.de:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@atlantis.magicstar.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@mandalore.st-city.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@omni.irc.omnimaga.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@atlanta.ga.us.starlink.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@clarent.nc.us.irchighway.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@etnies.ca.us.kampungchat.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ember.sorcery.net:6667/locate', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8007', 'verbose':2
#		}
#	}, {
#		'name':'118', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@neptune.betachat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.brasilirc.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.chateuropa.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@flux.serverpit.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@chat4.koach.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.ryukyu.ad.jp:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@b.irc.somenet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irp.irc.omnimaga.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@lynx.furnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc2.hu:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@roubaix.fr.epiknet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.perm.ru:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.anarxi.st:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.meganet.ru:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.data.lt:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@metric.ie.eu.afterx.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.genscripts.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@jherer2.chillnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@raven.serenia.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@services.penguinfriends.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@tweek.de.inside-irc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.scenecritique.com:6667/locate', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8008', 'verbose':2
#		}
#	}, {
#		'name':'119', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@irc.brasport.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@shadow.qc.ca.nextirc.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.hashmark.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@axiom.bigfurs.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.redenorte.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@cosmicfire.mi.us.krono.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@london.uk.eu.starlink.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@gazduiretm.ny.us.nextirc.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.tomsk.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ashburn.va.us.undernet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@chicago.il.us.starlink.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@dungeon.axenet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@timtam.uk.eu.blitzed.org:6667/locateS', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@maki.luatic.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@stats.appliedirc.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.sylnt.us:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ruby.exchat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@denhaag.nl.eu.asylumnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@godzilla.jp.p2p-network.netS:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.exolia.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@budapest.hu.eu.undernet.org:6667/locate', 'type':'irc', 'verbose':0},
#			{ 'uri':'@irc.infatech.net:6667/locate', 'type':'irc', 'verbose':0}
#	],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8009', 'verbose':2
#		}
#	}, {
#		'name':'120', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@hyperion.ie.afternet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@uk.eu.fireirc.co:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.odessa.ua:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@yudum.unitedchat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@tampa.fl.us.roirc.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc2.pilgerer.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@figarzilla.chateuropa.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.fewona.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.run.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.eagle.y.se:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@poischiche.fr.eu.netrusk.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@bigben.uk.p2p-network.net:6667/locateT', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.goodfuck.org:6667/locateT', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@windy.us.p2p-network.net:6667/locateT', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.metairc.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@paintball.tx.us.globalgamers.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@axa.id.as.auxnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@river.serenia.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@schoko.blafasel.de:6667/locateT', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.mv.ru:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.icestarirc.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.dal.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.nlnog.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@linux.globalirc.it:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.inet.tele.dk:6667/locateT', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@rajaniemi.freenode.net:6667/locateT', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8010', 'verbose':2
#		}
#	}, {
#		'name':'121', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@etn.on.ca.mixxnet.net:6667/locateA', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ineffective.idlechat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@denthox.chaterz.nl:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@arizona.us.aceirc.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ircbar.hu.ircline.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@roubaix.fr.whatnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@luna.iz-smart.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.hes.de.euirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@sexy.zoite.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@italia.simosnap.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ca.us.fireirc.co:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@indoshells.forumcerdas.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ircsource.nl:6667/locateA', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@amsterdam.nl.eu.scarynet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ircd.underworld.no:6667/locateA', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@marisa.seraphimlabs.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc1.pilgerer.org:6667/locateA', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@karin.indirectirc.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@pie.ga.paradoxirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.gimp.ca:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@atropine.rc6.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.snyde.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@aesir.sorcery.net:6667/locateA', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8011', 'verbose':2
#		}
#	}, {
#		'name':'122', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@devnull.chatopia.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@moka.uk.chaoticnetworks.com:6667/locateB', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@port80b.se.quakenet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@icarius.tweakers.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@newyork.nationchat.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@hub.endeavour.rs2i.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@aetos.greekchat.eu:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@raspberry.bug.ch:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@stitch.chatspike.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.unworldly.nl:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.ajhenderson.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@muffin.irc.omnimaga.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@wolf.furnet.org:6667/locateB', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@rappin.soundsnwaves.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.mgts.by:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.ktu.lt:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@tampere.fi.b2irc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@delphini.ga.us.starchat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@alpha.appliedirc.com:6667/locateB', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@jeger.binhex.org:6667/locate', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8012', 'verbose':2
#		}
#	}, {
#		'name':'123', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@team-irc.w3.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@deep13.psigenix.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@venom.ny.us.darenet.org:6667/locateC', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@bacon.utassault.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@forum.nl.eu.globalgamers.net:6667/locateC', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@vervet.foonetic.net:6667/locateC', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.datahata.by:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@backup.knightirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@stagsleap.ca.us.blitzed.org:6667/locateC', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.radio-kanaan.de:6667/locateC', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.nandox.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@dalek.panicirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@server1.dream-irc.de:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@choopa.nj.us.dal.net:6667/locateC', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@drahelas.forestnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@alicorn.furnet.org:6667/locateC', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc0.qes.ch.swissirc.net:6667/locateC', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@frozen.coldfront.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@oslo.no.eu.irclink.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@trigun.dejatoons.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.choopa.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@dynamo.digitalirc.org:6667/locate', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8013', 'verbose':2
#		}
#	}, {
#		'name':'124', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@irc.chanfix.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.tsua.net:6667/locateD', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.gentoo.ca:6667/locateD', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@warlock.hub.sorcery.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@brussel.chaterz.be:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@services.chatabout.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@halcyon.il.us.dal.net:6667/locateD', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@real.irc.bassdrive.com:6667/locateD', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.tribalwar.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@librenet.europnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.delfi.ee:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@chat3.koach.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.zboub.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.wikkedwire.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.caffie.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@eden.evilnet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@mars.inframonde.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@sapphire.sinsira.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.mzima.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@mimir.irc.worldnet.net:6667/locate', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8014', 'verbose':2
#		}
#	}, {
#		'name':'125', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@levin.mozilla.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@aurora.irc.arloria.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@martel.seraphimlabs.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc2.yukieiri.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc2.juggler.jp:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@tiki.oceanius.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@stockholm.se.eu.nextirc.org:6667/locateE', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@atom.irdsi.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.unitedchat.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.zonebg.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@orwell.freenode.net:6667/locateE', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@area51.lostirc.org:6667/locateE', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@asgard.skyirc.net:6667/locateE', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@stats.pancake-pirates.org:6667/locateE', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@chalk.uuid.uk:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@fortaire.mantrairc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@zenith.cpt.za.atrum.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@ariel.chathispano.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@sinclair.irc.arloria.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@armisael.surrealchat.net:6667/locateE', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8015', 'verbose':2
#		}
#	}, {
#		'name':'126', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@irc.bol-chat.com:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@icarus.cpt.za.atrum.org:6667/locateF', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@discord.canternet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.us.ircnet.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@blair.xertion.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@7ter-himmel-irc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@chronos.psigenix.net:6667/locateF', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@seattle.wa.us.starlink.org:6667/locateF', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@chat.delfi.lt:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@mila.nc.us.chaoticnetworks.com:6667/locateF', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@bifrost.ca.us.dal.net:6667/locateF', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.ss23.geek.nz:6667/locateF', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.seersirc.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@laeta.zoite.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@master.spiderchat.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.homo.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.ircshack.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@irc.malkier.net:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@cosmos.snoonet.org:6667/locate', 'type':'irc', 'verbose':0 },
#			{ 'uri':'@kiva3.lugs.ch:6667/locateF', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8016', 'verbose':2
#		}
#	}, {
#		'name':'127', 'verbose':2,
#		'decode':{
#			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':1, 'verbose':2
#		},
#		'input':[
#			{ 'uri':'@islander.uk.eu.nextirc.org:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@polarity.6irc.net:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@icarus.nj.us.globalgamers.net:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@irc.wup.nu:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@elysium.us.ix.undernet.org:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@dropbear.6irc.net:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@wirefull.geeknode.org:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@scale.fr.afternet.org:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@concrete.slashnet.org:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@osmium.uk.afternet.org:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@bofh.nl.smurfnet.ch:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@ganimedes.chathispano.com:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@irc.ukchatbox.org.uk:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@heraklion.ircnet.gr:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@irc2.xmission.com:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@bia.imaginarynet.uk:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@irc.ircportal.net:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@montreal.qc.ca.nextirc.org:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@coyote.wa.us.starchat.net:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@irc.big-daddy.fr:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@silph.co:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@sundance.6irc.net:6667/locate', 'type':'irc', 'verbose':0 },  
#			{ 'uri':'@sapphire.exchat.net:6667/locate', 'type':'irc', 'verbose':0 }, 
#			{ 'uri':'@asia.unitedchat.net:6667/locate', 'type':'irc', 'verbose':0 }
#		],
#		'output':{
#			'type':'tcp', 'uri':'localhost:8017', 'verbose':2
#		}
#	}
])
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
from sys_share_test import check
#
check(INPUT, OUTPUT)