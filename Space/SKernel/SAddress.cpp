/** 
 * File:   SAddress.cpp
 * Author: Luis Monteiro
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
	const string& addr
):string(addr) {
	smatch sm;
	if (!regex_match(*this, sm, std::regex(__ADDRESS_FMT__))) {
		throw logic_error("bad address format");
	}
	/**
	 * save parameter
	 */
	__name = Get(sm[1].str(), "");
	__host = Get(sm[2].str(), "");
	__port = Get(sm[3].str(), 0);
	__path = Get(sm[4].str(), "");
}
/**
 * 
 */
SAddress::SAddress(
	const string& user, 
	const string& host, 
	const uint16_t port, 
	const string& path
):string(), __name(user), __host(host), __port(port), __path(path) {
	ostringstream os;
	// save name
	if(!__name.empty()) { 
		os << __name; 
	}
	// save host
	if(!__host.empty()) { 
		if(os.tellp()) { os << "@"; }
		os << __host;	
	}
	// save port
	if(__port){
		if(os.tellp()) { os << ":";	}
		os << __port;
	} 
	// save path
	if(!__path.empty()){
		if(os.tellp()) { os << "/";	}
		os << __path;
	} 
	assign(os.str());
}