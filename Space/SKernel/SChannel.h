/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SChannel.h
 * Author: root
 *
 * Created on November 23, 2016, 11:43 AM
 */
#ifndef SCHANNEL_H
#define SCHANNEL_H
/**
 */
#include<iostream>
/**
 */
using namespace std;
/**
 */
typedef class SChannel {
public:
	SChannel()
	: __is(nullptr), __os(nullptr) {
	}
	SChannel(istream::__streambuf_type* ib, ostream::__streambuf_type* ob)
	: __is(ib), __os(ob) {
	}
	/**
	 * move operator
	 */
	inline SChannel& operator=(SChannel && c) {
		/**
		 * swap streams
		 */
		c.__is.rdbuf(__is.rdbuf(c.__is.rdbuf()));
		c.__os.rdbuf(__os.rdbuf(c.__os.rdbuf()));
		/**
		 */
		return *this;
	}
	/**
	 * streams operators
	 */
	inline operator ostream& () {
		return __os;
	}
	inline operator istream& () {
		return __is;
	}
	/**
	 * IO functions
	 */
	template <class V>
	inline ostream& operator<<(V v) {
		return __os << v;
	}
	template <class V>
	inline istream& operator>>(V& v) {
		return __is >> v;
	}
	/**
	 * utilities
	 */
	inline void Exceptions(ios::iostate ex){
		__is.exceptions(ex);
		__os.exceptions(ex);
	}
	
private:
	istream __is;
	ostream __os;
} Channel;

#endif /* SCHANNEL_H */

