#!/usr/bin/env python
#
# This program build and copy the essencial files from project directory to the new directory.
# The new directory will be compress in zip format
#
import os
import sys
import argparse
#
from time import gmtime
from time import strftime
from subprocess import call
#
#-----------------------------------------------------------------------------------------------------------------------
# definitions
#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
# split
#-----------------------------------------------------------------------------------------------------------------------
def split(doc, directions):
	#
	# extend 
	#
	extended = [dict(doc) for i in xrange(max([len(directions[d]) for d in directions]))]
	#
	for d in directions:
		for i in xrange(len(directions[d])):
			extended[i][d] = directions[d][i]
		#
	#
	return  extended
#-----------------------------------------------------------------------------------------------------------------------
# parse input
#-----------------------------------------------------------------------------------------------------------------------
def parseinput(name, config):
	#
	# create parser
	#
	parser = argparse.ArgumentParser(description=name)
	#
	# add option
	#
	for p in config:
		parser.add_argument(*p['opt'], **p['settings'])
	#
	#
	return parser.parse_args()
#		
if __name__ == "__main__":
	sys.exit(main(sys.argv[1:]))