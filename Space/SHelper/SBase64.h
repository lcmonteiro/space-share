/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SBase64.h
 * Author: Luis Monteiro
 *
 * Created on November 15, 2016, 11:23 AM
 */
#ifndef SBASE64_H
#define SBASE64_H
/**
 */
#include <string>
/**
 */
#include "SContainer.h"
/**
 */
using namespace std;
/**
 */
namespace SBase64 {
	/**
	 * Encode
	 * @param data
	 * @return 
	 */
	string Encode(Frame::const_iterator begin, Frame::const_iterator end);
	/**
	 * Decode
	 * @param data
	 * @return 
	 */
	Frame Decode(string::const_iterator begin, string::const_iterator end);
	/**
	 * Utilities
	 */
	inline string Encode(const Frame& data) {
		return Encode(data.begin(), data.end());
	}
	inline Frame Decode(const string& data) {
		return Decode(data.begin(), data.end());
	}
};

#endif /* SBASE64_H */

