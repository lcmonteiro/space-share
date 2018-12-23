/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SHash.h
 * Author: root
 *
 * Created on July 19, 2017, 6:23 PM
 */
#ifndef SHASH_H
#define SHASH_H
/**
 */
#include <cstdint>
#include <string>
/**
 */
using namespace std;
/**
 */
class SHash {
public:
	/**
	 * Digest convert string to number
	 * @param value - digest string
	 * @return number
	 */
	static uint64_t Digest(string value, uint64_t seed = 0xc70f6907UL);
};

#endif /* SHASH_H */

