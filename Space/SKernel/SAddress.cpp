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
 * ----------------------------------------------------------------------------
 * utilities
 * ----------------------------------------------------------------------------
 */
static uint16_t Get(const std::string& data, const uint16_t def) {
	return data.empty() ? def : std::stoi(data);
}
static const std::string& Get(const std::string& data, const std::string& def) {
	return data.empty() ? def : data;
}
/**
 * ----------------------------------------------------------------------------
 * parse 
 * ----------------------------------------------------------------------------
 */
SAddress::SAddress(const std::string& addr)
: SText(addr), __name(), __host(), __port(), __path() {
	std::smatch sm;
	if (std::regex_match(*this, sm, std::regex(__ADDRESS_FMT__))) {
		/**
		 * save parameter
		 */
		__name = Get(sm[1].str(), "");
		__host = Get(sm[2].str(), "");
		__port = Get(sm[3].str(), 0);
		__path = Get(sm[4].str(), "");	
	} else {
		/**
		 * invalid address
		 */
		throw std::logic_error("bad address format");
	}
}
/**
 * ----------------------------------------------------------------------------
 * serialise 
 * ----------------------------------------------------------------------------
 */
SAddress::SAddress(
	const std::string& user, 
	const std::string& host, 
	const uint16_t port, 
	const std::string& path
): SText(), __name(user), __host(host), __port(port), __path(path) {
	std::ostringstream os;
	// save name ------------------------------------------
	if(!__name.empty()) { 
		os << __name; 
	}
	// save host ------------------------------------------
	if(!__host.empty()) { 
		if(os.tellp()) { os << "@"; }
		os << __host;	
	}
	// save port ------------------------------------------
	if(__port){
		if(os.tellp()) { os << ":";	}
		os << __port;
	} 
	// save path ------------------------------------------
	if(!__path.empty()){
		if(os.tellp()) { os << "/";	}
		os << __path;
	} 
	assign(os.str());
}