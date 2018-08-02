#!/usr/bin/env python
#encoding: UTF-8
#-----------------------------------------------------------------------------------------------------------------------
# proxy netshare
#-----------------------------------------------------------------------------------------------------------------------
from subprocess import Popen
from socket	import create_connection
from lockfile	import LockFile
from time	import sleep
from time 	import time
from threading	import Lock
#....................................... definitions ....................................
NETSHARE_BIN = '/home/monteiro/workspace/m2bee/C++/ShareSpace/Applications/NetShare/dist/Debug/GNU-Linux/netshare'
#.......................................... create proxy ...................................
def create_proxy(location, password):
	#
	for i in xrange(10):
		locker = LockFile('/tmp/lockproxy' + str(i))
		try:
			locker.acquire(1)
			#
			# open log file 
			#
			log = open('/tmp/netproxy' + str(i), 'w')
			#
			# create process
			#
			pro = Popen([
				NETSHARE_BIN, '-i', str(i), '-l', location, '-p', password
			], stdout=log, stderr=log)
			#
			#
			return {'process':pro, 'log' :log, 'locker':locker, 'port': (10000+(100*i))}
		except:
			pass
		#
	#
	raise RuntimeError('create proxy')
#
#.......................................... create connection ..............................
def create_link(proxy):
	#
	args = ('localhost', proxy['port'])
	for i in xrange(10):
		try:
			#
			# create socket
			#
			sock = create_connection(args)
			#
			#
			return {'sock':sock, 'args':args}
		except:
			sleep(1)
		#
	#
	raise RuntimeError('create link')
#
#-----------------------------------------------------------------------------------------------------------------------
# ui
#-----------------------------------------------------------------------------------------------------------------------
import curses
#............................................. global ...................................... 
LOCK   = Lock()
DATA   = []
OPUT   = None
IPUT   = None
SCRN   = None
#............................................. functions .................................... 
#
def print_output(msg, refresh=False):
	global OPUT
	#
	#OPUT.addstr(':'.join(x.encode('hex') for x in msg))
	#OPUT.addstr('\n')
	re = search('(.*)\x1F(.*)\x1F(.*)', msg)
	if re:
		OPUT.addstr("["+re.group(1)+"]", curses.A_BOLD)
		OPUT.addstr(re.group(2)+":")
		OPUT.addstr(re.group(3))
		OPUT.addstr('\n')
	#
	if refresh:
		OPUT.refresh()
	#	
#
def refresh_screen():
	global SCRN
	global OPUT
	global IPUT
	# screen
	with LOCK:
		SCRN.refresh()
		OPUT.refresh()
		IPUT.refresh()
		IPUT.addstr('> ')
	#
#
def draw_screen(name):
	global SCRN
	global OPUT
	global IPUT
	global DATA
	# screen
	maxy, maxx = SCRN.getmaxyx()
	with LOCK:
		#
		# delete windows
		#
		curses.endwin()
		SCRN.clear()
		SCRN.addstr(0, (maxx-len(name))/2, name, curses.A_BOLD)
		#
		# create output window
		#
		OPUT = curses.newwin(maxy-3, maxx, 2, 1)
		OPUT.scrollok(True)
		OPUT.leaveok(True)
		#
		# create imput window
		# 	
		IPUT = curses.newwin(1, maxx, maxy-1, 1)
		IPUT.scrollok(True)
		IPUT.keypad(1)
		#prompt.border('-', '-', '-', '-', '-', '-', ' ', ' ')
		#IPUT.timeout(10000)
		#prompt.leaveok(True)
		#
		# init output
		#
		for d in DATA:
			print_output(d)
		#
	#
	return (maxy, maxx)
#
def create_screen():
	global SCRN
	# screen
	SCRN = curses.initscr()
	SCRN.leaveok(True)
#
def delete_screen():
	curses.curs_set(1)
	curses.nocbreak()
	curses.echo()
	curses.endwin()
#
#-----------------------------------------------------------------------------------------------------------------------
# main
#-----------------------------------------------------------------------------------------------------------------------
from datetime	import datetime
from threading	import Thread
from os		import kill
from os		import devnull
from re		import search
#............................................. global ...................................... 

#............................................. format msg .................................. 
def fmt_message(txt, user):
	return "" + str(int(time()*1000)) + "\x1F" + user + "\x1F" + txt
#............................................. put msg .................................... 
def put_message(msg):
	global DATA
	global LOCK
	with LOCK:
		#
		# display
		#
		print_output(msg, True);
		#
		# save history
		#
		DATA.append(msg)
		#
	#
#............................................. send msg .................................... 
def send_message(msg, link):
	#
	#link['sock'].sendall(msg+"\u0000"*(20 - len(msg) % 20))
	link['sock'].sendall(msg+"\x00")
	#
	put_message(msg)
#............................................. receive msg ................................. 
def recv_message(link):
	try:
		carrier = ""
		while True:
			data = link['sock'].recv(0x1000)
			if data:
				#
				frames = (carrier + data).split("\0")
				#
				for m in frames[0:-1]:
					if m:
						put_message(m)
					#
				#
				carrier = frames[-1]
			else:
				put_message(fmt_message("disconnect","app"))
				#
				while True:
					try:
						link['sock'] = create_connection(link['args'])
						break
					except:
						sleep(1)
					#
				#
				put_message(fmt_message("connect","app"))
				#
			#	
		#
	except:
		pass
	#
#............................................. start ....................................... 
def main(params):
	global OPUT
	global IPUT
	global SCRN
	#
	#
	NAME = "mshare - security chat (%s@%s:%s)" % (params.user, params.location, params.password)
	#
	try:
		#
		# interlock
		#
		hist = []
		#
		# create UI
		#
		create_screen()
		#
		# creat proxy
		# 
		proxy = create_proxy(params.location, params.password);
		#
		# creat conection
		# 
		link = create_link(proxy)
		#
		# thread to reveive data
		#
		thread = Thread(target = recv_message, args = [link])
		thread.setDaemon(True)
		thread.start()
		#
		maxy, maxx = draw_screen(NAME)
		while True:
			refresh_screen()
			#
			# read data
			#
			txt=IPUT.getstr()
			if txt:
				#
				# send message
				#
				send_message(fmt_message(txt, params.user), link)
				#
			#
			if curses.is_term_resized(maxy, maxx):	
				#
				# redraw screen
				#
				maxy, maxx = draw_screen(NAME)
			#
		#
		
		#
	#
	# catch exceptions
	#
	except Exception as e:
		delete_screen()
		print 'mshare: error:', e 
	except:
		delete_screen()
	#
	# kill external proxy
	#
	proxy['process'].kill()
	#
	# realese lock
	#
	proxy['locker'].release()
	#
	return 0
#	
#-----------------------------------------------------------------------------------------------------------------------
# entry point
#-----------------------------------------------------------------------------------------------------------------------
from argparse	import ArgumentParser
from sys	import exit
#............................................ parse input .....................................
def parseinput(name, version, config):
	#
	# create parser
	#
	parser = ArgumentParser(description=name, version=version)
	#
	# add option
	#
	for p in config:
		parser.add_argument(*p['opt'], **p['settings'])
	#
	#
	return parser.parse_args()
#
if __name__ == '__main__':
	# read args
	params = parseinput('mshare', '1.0.0', [
		{'opt': ['--user', '-u'], 'settings':{
			'help' : 'user name',
			'default' : 'Unknown',
		}},
		{'opt': ['--location', '-l'], 'settings':{
			'help' : 'location',
			'default' : "",
		}},
		{'opt': ['--password', '-p'], 'settings':{
			'help' : 'password',
			'default' : "",
		}}
	])
	#
	# start point
	#
	exit(main(params))
#-----------------------------------------------------------------------------------------------------------------------
