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
			'delay':5900, 'redundancy':1, 'timeout':10000, 'lifetime':10, 'lives':3, 'verbose':2
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
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':3, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6001', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@citadel.ringoflightning.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@mancubus.zandronum.com:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@solenoid.rizon.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@cronos.xevion.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@minime.fef.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@stardust.nj.us.leaf.chat-solutions.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.stardustfields.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.newit-lan.ru:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@husky.sierranet.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@sandwich.skyirc.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@adonis.powanet.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@space.blafasel.de:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.ninjaneering.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@germany.enterthegame.com:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.uk.mibbit.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.ssi.bg:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.blafasel.de:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@stopover.ky.us.starlink-irc.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.dopechat.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@overdrive.xertion.org:6667/sssss', 'type':'irc', 'verbose':0  }
		]
	}, {
		'name':'-12', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':3, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6002', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@hyperion.eagles-myirc.de:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@a.irc.somenet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@nebula.uk.eu.darkmyst.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@services.serenity-irc.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@catastrophe.esper.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@chicago.il.us.chatnet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@dirtbox.scenep2p.net:6667/sssss', 'type':'irc', 'verbose':0  },  
			{ 'uri':'@burstfire.uk.eu.gamesurge.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@hivane.geeknode.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@tetris.allrednc.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@defiant.geekshed.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@us.irc.ghostsirc.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@kestrel.uk.afternet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@alpha.fr.eu.obsidianirc.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@arm.globalirc.it:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@rotterdam.nl.eu.neko-net.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@procrastinate.idlechat.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@nc.d-t-net.de:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@atlantis.magicstar.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@mandalore.st-city.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.unibg.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@logitech.webcastsonline.com:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@clarent.nc.us.irchighway.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@dragonite.ca.dragonirc.com:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@monster.va.us.synirc.net:6667/sssss', 'type':'irc', 'verbose':0  }
		]
	}, {
		'name':'-13', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':3, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6003', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@neptune.betachat.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.brasilirc.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.chateuropa.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.global-radio.ch:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@weedsmoka.ladysclub-irc.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.ryukyu.ad.jp:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@b.irc.somenet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@shire.digitalirc.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@lynx.furnet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.chaterz.nl:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@roubaix.fr.epiknet.org:6667/sssss', 'type':'irc', 'verbose':0  },  
			{ 'uri':'@irc.perm.ru:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@xdcc.scenep2p.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@aceraceae.subluminal.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.data.lt:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@metric.ie.eu.afterx.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.genscripts.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@jherer2.chillnet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@andromede.europnet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@services.penguinfriends.org:6667/sssss', 'type':'irc', 'verbose':0  }
		]
	}, {
		'name':'-14', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':3, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6004', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@irc.brasport.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@shadow.qc.ca.nextirc.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.hashmark.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@axiom.bigfurs.com:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.redenorte.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@cosmicfire.mi.us.krono.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@london.uk.eu.starlink.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@gazduiretm.ny.us.nextirc.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.tomsk.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@mercury.il.us.dynastynet.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@chicago.il.us.starlink.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@aperture.esper.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@maple.on.ca.darkmyst.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@maki.luatic.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@stats.appliedirc.com:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.sylnt.us:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@ruby.exchat.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@denhaag.nl.eu.asylumnet.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@godzilla.jp.p2p-network.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.exolia.net:6667/sssss', 'type':'irc', 'verbose':0  }
		]
	}, {
		'name':'-15', 'verbose':2,
		'encode':{
			'delay':5000, 'redundancy':4, 'timeout':10000, 'lifetime':15, 'live':3, 'verbose':2
		},
		'input':{
			'type':'tcp', 'uri':'localhost:6005', 'pack-size':15, 'frame-size':300, 'verbose':2
		},
		'output':[
			{ 'uri':'@rochester.mi.us.starlink-irc.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.bluntchat.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.odessa.ua:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@pegasus.il.us.darkmyst.org:6667/sssss', 'type':'irc', 'verbose':0  },  
			{ 'uri':'@tampa.fl.us.roirc.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@mars.pa.us.dynastynet.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@dallas.tx.us.irchaven.org:6667/sssss', 'type':'irc', 'verbose':0  },  
			{ 'uri':'@irc.fewona.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.run.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@sigsegv.teranova.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@poischiche.fr.eu.netrusk.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@bigben.uk.p2p-network.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.goodfuck.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@windy.us.p2p-network.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.metairc.com:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@paintball.tx.us.globalgamers.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@axa.id.as.auxnet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@dome.ringoflightning.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@incognito.ca.us.austnet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@nehalem.de.afternet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.icestarirc.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@online-dc3.fr.eu.evolu.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.nlnog.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@linux.globalirc.it:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.inet.tele.dk:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@rajaniemi.freenode.net:6667/sssss', 'type':'irc', 'verbose':0  }
		]
	},
	# --------------------------------------------------------------------------------------------------------------
	#						Decode
	# --------------------------------------------------------------------------------------------------------------
	{
		'name':'101', 'verbose':2,
		'saving':{
			'delay':500, 'timeout':20000, 'lifetime':10, 'live':10, 'verbose':2
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
			'delay':1000, 'timeout':40000, 'lifetime':10, 'live':10, 'verbose':2
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
			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@citadel.ringoflightning.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@mancubus.zandronum.com:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@solenoid.rizon.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@cronos.xevion.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@minime.fef.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@stardust.nj.us.leaf.chat-solutions.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.stardustfields.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.newit-lan.ru:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@husky.sierranet.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@sandwich.skyirc.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@adonis.powanet.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@space.blafasel.de:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.ninjaneering.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@germany.enterthegame.com:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.uk.mibbit.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.ssi.bg:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.blafasel.de:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@stopover.ky.us.starlink-irc.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.dopechat.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@overdrive.xertion.org:6667/sssss', 'type':'irc', 'verbose':0  }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8001', 'verbose':2
		}
	}, {
		'name':'112', 'verbose':2,
		'decode':{
			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@hyperion.eagles-myirc.de:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@a.irc.somenet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@nebula.uk.eu.darkmyst.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@services.serenity-irc.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@catastrophe.esper.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@chicago.il.us.chatnet.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@dirtbox.scenep2p.net:6667/sssss', 'type':'irc', 'verbose':0  },  
			{ 'uri':'@burstfire.uk.eu.gamesurge.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@hivane.geeknode.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@tetris.allrednc.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@defiant.geekshed.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@us.irc.ghostsirc.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@kestrel.uk.afternet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@alpha.fr.eu.obsidianirc.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@arm.globalirc.it:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@rotterdam.nl.eu.neko-net.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@procrastinate.idlechat.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@nc.d-t-net.de:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@atlantis.magicstar.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@mandalore.st-city.net:6667/sssss', 'type':'irc', 'verbose':0  },  
			{ 'uri':'@irc.unibg.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@logitech.webcastsonline.com:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@clarent.nc.us.irchighway.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@dragonite.ca.dragonirc.com:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@monster.va.us.synirc.net:6667/sssss', 'type':'irc', 'verbose':0  }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8002', 'verbose':2
		}
	}, {
		'name':'113', 'verbose':2,
		'decode':{
			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@neptune.betachat.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.brasilirc.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.chateuropa.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.global-radio.ch:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@weedsmoka.ladysclub-irc.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.ryukyu.ad.jp:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@b.irc.somenet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@shire.digitalirc.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@lynx.furnet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.chaterz.nl:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@roubaix.fr.epiknet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.perm.ru:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@xdcc.scenep2p.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@aceraceae.subluminal.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.data.lt:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@metric.ie.eu.afterx.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.genscripts.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@jherer2.chillnet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@andromede.europnet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@services.penguinfriends.org:6667/sssss', 'type':'irc', 'verbose':0  }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8003', 'verbose':2
		}
	}, {
		'name':'114', 'verbose':2,
		'decode':{
			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@irc.brasport.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@shadow.qc.ca.nextirc.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.hashmark.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@axiom.bigfurs.com:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.redenorte.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@cosmicfire.mi.us.krono.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@london.uk.eu.starlink.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@gazduiretm.ny.us.nextirc.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.tomsk.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@mercury.il.us.dynastynet.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@chicago.il.us.starlink.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@aperture.esper.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@maple.on.ca.darkmyst.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@maki.luatic.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@stats.appliedirc.com:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.sylnt.us:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@ruby.exchat.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@denhaag.nl.eu.asylumnet.org:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@godzilla.jp.p2p-network.net:6667/sssss', 'type':'irc', 'verbose':0  },
			{ 'uri':'@irc.exolia.net:6667/sssss', 'type':'irc', 'verbose':0  }
		],
		'output':{
			'type':'tcp', 'uri':'localhost:8004', 'verbose':2
		}
	}, {
		'name':'115', 'verbose':2,
		'decode':{
			'delay':1000, 'timeout':10000, 'lifetime':15, 'live':10, 'verbose':2
		},
		'input':[
			{ 'uri':'@rochester.mi.us.starlink-irc.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.bluntchat.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.odessa.ua:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@pegasus.il.us.darkmyst.org:6667/sssss', 'type':'irc', 'verbose':0  },  
			{ 'uri':'@tampa.fl.us.roirc.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@mars.pa.us.dynastynet.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@dallas.tx.us.irchaven.org:6667/sssss', 'type':'irc', 'verbose':0  },  
			{ 'uri':'@irc.fewona.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.run.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@sigsegv.teranova.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@poischiche.fr.eu.netrusk.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@bigben.uk.p2p-network.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.goodfuck.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@windy.us.p2p-network.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.metairc.com:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@paintball.tx.us.globalgamers.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@axa.id.as.auxnet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@dome.ringoflightning.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@incognito.ca.us.austnet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@nehalem.de.afternet.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.icestarirc.org:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@online-dc3.fr.eu.evolu.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.nlnog.net:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@linux.globalirc.it:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@irc.inet.tele.dk:6667/sssss', 'type':'irc', 'verbose':0  }, 
			{ 'uri':'@rajaniemi.freenode.net:6667/sssss', 'type':'irc', 'verbose':0  }
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