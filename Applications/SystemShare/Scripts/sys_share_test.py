#!/usr/bin/env python2
#encoding: UTF-8
#
#-----------------------------------------------------------------------------------------------------------------------
# check
#-----------------------------------------------------------------------------------------------------------------------
import os
import hashlib
#
def check(i, o):
	m = min([os.path.getsize(i), os.path.getsize(o)])
	assert m != 0
	assert m == os.path.getsize(i)
	i = hashlib.md5(open(i,'rb').read()[0:m]).hexdigest()
	o = hashlib.md5(open(o,'rb').read()[0:m]).hexdigest()
	assert i == o
#
def check_size(files):
	m = min([os.path.getsize(f) for f in files])
	assert m != 0
#