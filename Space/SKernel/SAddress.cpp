/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SAddress.cpp
 * Author: root
 * 
 * Created on November 21, 2016, 12:10 PM
 */
#include <regex>
#if __GNUC__ < 5
#include <cstdlib>
int stoi(std::string s){
        return strtol(s.c_str(),0,10);
}
#endif
/**
 */
#include "SAddress.h"
/**
 * definitions
 */
#define __ADDRESS_FMT__	"([0-9a-zA-Z]*)(?:@|^)([0-9a-zA-Z.-]*):?([0-9]*)/?([0-9a-zA-Z/+._-]*)"
/**
 * utilities
 */
static uint16_t Get(string data, const uint16_t def) {
	return data.empty() ? def : stoi(data);
}
static string Get(string data, const string def) {
	return data.empty() ? def : move(data);
}
/**
 * parse 
 */
SAddress::SAddress(
	const string& addr, 
	const string& user, 
	const string& host, 
	const uint16_t port, 
	const string& path
):string(addr) {
	smatch sm;
	if (!regex_match(*this, sm, std::regex(__ADDRESS_FMT__))) {
		throw logic_error("bad address format");
	}
	/**
	 * save
	 */
	__name = Get(sm[1].str(), user);
	__host = Get(sm[2].str(), host);
	__port = Get(sm[3].str(), port);
	__path = Get(sm[4].str(), path);
}
