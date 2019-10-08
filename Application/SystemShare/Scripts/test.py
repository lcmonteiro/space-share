#!/usr/bin/env python2
#encoding: UTF-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
from math import log
if __name__ == "__main__":
	#
	hist0 = [100.0,1.0,100.0,1.0,1.0]
	hist1 = [10000.0,1.0,1.0,1.0,1.0]
	#
	px0 = [float(e)/sum(hist0) for e in hist0]
	px1 = [float(e)/sum(hist1) for e in hist1]
	#
	hx = [p0 * log(p1) for p0, p1 in zip(px0, px1)]
	#
	print -sum(hx)