#! /usr/bin/python

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

__author__ = "root"
__date__ = "$Dec 21, 2015 10:13:59 AM$"
#
import csv
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
#
def process_x_255():
	data = None
	with open('./data/decode-x-255', 'rb') as csvfile:
		data = [row for row in csv.reader(csvfile, delimiter=';', quotechar='|')]
	#
	data = [[float(v[0]), float(v[1]), float(v[2]), float(v[3])]  for v in data[1:]]
	#
	def func0(x, a, b, c, d):
		return c - (a * np.exp(-b * (x-d)))
	def func1(x, a, b, c, d):
		return (a * np.exp(-b * (x-d))) + c
	def func2(x, a, b, c):
		return (a / (x + b)) + c
	func = func2
	#
	x = [d[0] for d in data]
	y = [d[1] for d in data]
#	y = [(d[0] * d[1]) / 256  for d in data]
	#
	popt, pcov = curve_fit(func, x, y)
#	print [func(d, * popt) for d in x]
	print popt
#	Y = [func(x, *popt) for d in x]
	
#	plt.plot([func(d, * popt) for d in x])
	plt.plot([[(d[0] * d[1]) / 256, d[1], d[0] * func(d[0], * popt) / 256, func(d[0], * popt)] for d in data])
	plt.show()
#
def process_1_255():
	data = None
	with open('./data/decode-1-255', 'rb') as csvfile:
		data = [row for row in csv.reader(csvfile, delimiter=';', quotechar='|')]
	#
	data = [[float(v[0]), float(v[1]), float(v[2]), float(v[3])]  for v in data[1:]]
	#
	def func0(x, a, b, c, d):
		return c - (a * np.exp(-b * (x-d)))
	def func1(x, a, b, c, d):
		return (a * np.exp(-b * (x-d))) + c
	def func2(x, a, b, c):
		return (a / (x - b)) + c
	func = func2
	#
	x = [d[0] for d in data]
	y = [d[1] for d in data]
#	y = [(d[0] * d[1]) / 256  for d in data]
	#
	popt, pcov = curve_fit(func, x, y)
#	print [func(d, * popt) for d in x]
	popt = [3000, 35, 9]
#	Y = [func(x, *popt) for d in x]
	print popt
#	plt.plot([func(d, * popt) for d in x])
	plt.plot([[(d[0] * d[1]) / 256, d[1], d[0] * func(d[0], * popt) / 256, func(d[0], * popt)] for d in data])
	plt.show()
	
	
def process_6_255():
	data = None
	with open('./data/decode-6-255', 'rb') as csvfile:
		data = [row for row in csv.reader(csvfile, delimiter=';', quotechar='|')]
	#
	data = [[float(v[0]), float(v[1]), float(v[2]), float(v[3])]  for v in data[1:]]
	#
	def func0(x, a, b, c, d):
		return c - (a * np.exp(-b * (x-d)))
	def func1(x, a, b, c, d):
		return (a * np.exp(-b * (x-d))) + c
	def func2(x, a, b, c):
		return (a / (x + b)) + c
	func = func2
	#
	x = [d[0] for d in data]
	y = [d[1] for d in data]
#	y = [(d[0] * d[1]) / 256  for d in data]
	#
	popt, pcov = curve_fit(func, x, y)
#	print [func(d, * popt) for d in x]
	print popt
#	Y = [func(x, *popt) for d in x]
	
#	plt.plot([func(d, * popt) for d in x])
	plt.plot([[(d[0] * d[1]) / 256, d[1], d[0] * func(d[0], * popt) / 256, func(d[0], * popt)] for d in data])
	plt.show()	

def process_5_255():
	data = None
	with open('./data/decode-5-255', 'rb') as csvfile:
		data = [row for row in csv.reader(csvfile, delimiter=';', quotechar='|')]
	#
	data = [[float(v[0]), float(v[1]), float(v[2]), float(v[3])]  for v in data[1:]]
	#
	def func0(x, a, b, c, d):
		return c - (a * np.exp(-b * (x-d)))
	def func1(x, a, b, c, d):
		return (a * np.exp(-b * (x-d))) + c
	def func2(x, a, b, c):
		return (a / (x + b)) + c
	func = func2
	#
	x = [d[0] for d in data]
	y = [d[1] for d in data]
#	y = [(d[0] * d[1]) / 256  for d in data]
	#
	popt, pcov = curve_fit(func, x, y)
#	print [func(d, * popt) for d in x]
	print popt
#	Y = [func(x, *popt) for d in x]
	
#	plt.plot([func(d, * popt) for d in x])
	plt.plot([[(d[0] * d[1]) / 256, d[1], d[0] * func(d[0], * popt) / 256, func(d[0], * popt)] for d in data])
	plt.show()
#
#
def process_3_255():
	data = None
	with open('./data/decode-3-255', 'rb') as csvfile:
		data = [row for row in csv.reader(csvfile, delimiter=';', quotechar='|')]
	#
	data = [[float(v[0]), float(v[1]), float(v[2]), float(v[3])]  for v in data[1:]]
	#
	def func0(x, a, b, c, d):
		return c - (a * np.exp(-b * (x-d)))
	def func1(x, a, b, c, d):
		return (a * np.exp(-b * (x-d))) + c
	def func2(x, a, b, c):
		return (a / (x + b)) + c
	func = func2
	#
	x = [d[0] for d in data]
	y = [d[1] for d in data]
#	y = [(d[0] * d[1]) / 256  for d in data]
	#
	popt, pcov = curve_fit(func, x, y)
#	print [func(d, * popt) for d in x]
	print popt
#	Y = [func(x, *popt) for d in x]
	
#	plt.plot([func(d, * popt) for d in x])
	plt.plot([[(d[0] * d[1]) / 256, d[1], d[0] * func(d[0], * popt) / 256, func(d[0], * popt)] for d in data])
	plt.show()
#
#
def process_10_255():
	data = None
	with open('./data/decode-10-255', 'rb') as csvfile:
		data = [row for row in csv.reader(csvfile, delimiter=';', quotechar='|')]
	#
	data = [[float(v[0]), float(v[1]), float(v[2]), float(v[3])]  for v in data[1:]]
	#
	def func0(x, a, b, c, d):
		return c - (a * np.exp(-b * (x-d)))
	def func1(x, a, b, c, d):
		return (a * np.exp(-b * (x-d))) + c
	def func2(x, a, b, c):
		return (a / (x + b)) + c
	func = func2
	#
	x = [d[0] for d in data]
	y = [d[1] for d in data]
#	y = [(d[0] * d[1]) / 256  for d in data]
	#
	popt, pcov = curve_fit(func, x, y)
#	print [func(d, * popt) for d in x]
	print popt
#	Y = [func(x, *popt) for d in x]
	
#	plt.plot([func(d, * popt) for d in x])
	plt.plot([[(d[0] * d[1]) / 256, d[1], d[0] * func(d[0], * popt) / 256, func(d[0], * popt)] for d in data])
	plt.show()

def process_255():
	data = None
	with open('./data/decode', 'rb') as csvfile:
		data = [row for row in csv.reader(csvfile, delimiter=';', quotechar='|')]
	#
	data = [[float(v[0]), float(v[1]), float(v[2]), float(v[3])]  for v in data[1:]]
	#
	def func0(x, a, b, c, d):
		return c - (a * np.exp(-b * (x-d)))
	def func1(x, a, b, c, d):
		return (a * np.exp(-b * (x-d))) + c
	def func2(x, a, b, c):
		return (a / (x + b)) + c
	func = func2
	#
	x = [d[0] for d in data]
	y = [d[1] for d in data]
#	y = [(d[0] * d[1]) / 256  for d in data]
	#
	popt, pcov = curve_fit(func, x, y)
#	print [func(d, * popt) for d in x]
	print popt
#	Y = [func(x, *popt) for d in x]
	
#	plt.plot([func(d, * popt) for d in x])
	plt.plot([
		[(d[0] * d[1]) / 256, d[1], 
		d[0] * func(d[0], * popt) / 256,
		func(d[0], * popt),
		6500 / d[0],
		3500 / d[0],
		6500 / ( d[0] + 20)
		] for d in data])
	plt.show()


#
#
def process_decode():
	data = None
	with open('./data/decode', 'rb') as csvfile:
		data = [row for row in csv.reader(csvfile, delimiter=';', quotechar='|')]
	#
	data = [[int(v[1]), int(v[2])]  for v in data[1:]]
	#
	print data

if __name__ == "__main__":
	process_255()