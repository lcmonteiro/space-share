/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SBase64.cpp
 * Author: Luis Monteiro
 * 
 * Created on November 15, 2016, 11:23 AM
 */
#include "SBase64.h"
/**
 * Encode
 * @param begin
 * @param end
 * @return 
 */
string SBase64::Encode(Frame::const_iterator begin, Frame::const_iterator end) {
	/**
	 * basis
	 */
	static const char basis[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	/**
	 * output
	 */
	string out;
	/**
	 * reserve size
	 */
	out.reserve(((distance(begin, end) + 2) / 3 * 4) + 1);
	/**
	 * process
	 */
	auto it = begin, it1 = begin + 1, it2 = begin + 2;
	for (; it2 < end; it += 3, it1 += 3, it2 += 3) {
		out.push_back(basis[(*it >> 2) & 0x3F]);
		out.push_back(basis[((*it & 0x3) << 4) | ((int) (*it1 & 0xF0) >> 4)]);
		out.push_back(basis[((*it1 & 0xF) << 2) | ((int) (*it2 & 0xC0) >> 6)]);
		out.push_back(basis[*it2 & 0x3F]);
	}
	if (it < end) {
		out.push_back(basis[(*it >> 2) & 0x3F]);
		if (it1 < end) {
			out.push_back(basis[((*it & 0x3) << 4) | ((int) (*it1 & 0xF0) >> 4)]);
			out.push_back(basis[((*it1 & 0xF) << 2)]);
		} else {
			out.push_back(basis[((*it & 0x3) << 4)]);
		}
	}
	return out;
}
/**
 * Decode
 * @param begin
 * @param end
 * @return 
 */
Frame SBase64::Decode(string::const_iterator begin, string::const_iterator end) {
	/**
	 * ASCII table 
	 */
	static const unsigned char map[256] = {
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
		64, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
		64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
	};
	/**
	 * output
	 */
	Frame out;
	/**
	 * reserve size
	 */
	out.reserve(((distance(begin, end) + 3) / 4) * 3);
	/**
	 * process
	 */
	auto it0 = begin, it1 = begin + 1, it2 = begin + 2, it3 = begin + 3;
	for (; it3 < end; it0 += 4, it1 += 4, it2 += 4, it3 += 4) {
		out.push_back((uint8_t) (map[int(*it0)] << 2 | map[int(*it1)] >> 4));
		out.push_back((uint8_t) (map[int(*it1)] << 4 | map[int(*it2)] >> 2));
		out.push_back((uint8_t) (map[int(*it2)] << 6 | map[int(*it3)]));
	}
	if (it1 < end) {
		out.push_back((uint8_t) (map[int(*it0)] << 2 | map[int(*it1)] >> 4));
	}
	if (it2 < end) {
		out.push_back((uint8_t) (map[int(*it1)] << 4 | map[int(*it2)] >> 2));
	}
	if (it3 < end) {
		out.push_back((uint8_t) (map[int(*it2)] << 6 | map[int(*it3)]));
	}
	return out;
}