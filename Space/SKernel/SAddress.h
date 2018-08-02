/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SAddress.h
 * Author: Luis Monteiro
 *
 * Created on November 21, 2016, 12:10 PM
 */
#ifndef SADDRESS_H
#define SADDRESS_H
/**
 */
#include <string>
/**
 */
using namespace std;
/**
 */
typedef class SAddress : public string {
public:
	/**
	 * constructor
	 */
	SAddress() = default;

	SAddress(SAddress&& addr) = default;
        
	SAddress(const SAddress& addr) = default;
	/**
	 * process constructor
	 */
	SAddress(
		const string addr, 
		const string user = "", 
		const string host = "", 
		const uint16_t port = 0, 
		const string path = ""
	);
	/**
	 * destructor
	 */
	virtual ~SAddress() = default;
	/**
	 * move operator
	 */
	SAddress& operator=(SAddress&& addr) = default;
        /**
         * copy operator 
         */
	SAddress& operator=(const SAddress& addr) = default;
	/**
	 * accessors
	 */
	inline const string& File() const {
		return __name;
	}
	inline const string& User() const {
		return __name;
	}
	inline const string& Host() const {
		return __host;
	}
	inline const uint16_t Port() const {
		return __port;
	}
	inline const string& Path() const {
		return __path;
	}
	inline const string& Channel() {
		return __path;
	}
private:
	/**
	 * attributes
	 */
	string __name;
	string __host;
	uint16_t __port;
	string __path;
} Address;

#endif /* SADDRESS_H */

