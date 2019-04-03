/**
 * File:   SAddress.h
 * Author: Luis Monteiro
 *
 * Created on November 21, 2016, 12:10 PM
 */
#ifndef SADDRESS_H
#define SADDRESS_H
/**
 * space
 */
#include "SText.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Address
 * ------------------------------------------------------------------------------------------------
 */
class SAddress : public SText {
public:
	/**
	 * ------------------------------------------------------------------------
	 * defaults
	 * ------------------------------------------------------------------------
	 */
	SAddress() 						= default;
	SAddress(SAddress&& addr) 		= default;
	SAddress(const SAddress& addr) 	= default;
	virtual ~SAddress() 			= default;
	/**
	 * operator
	 */
	SAddress& operator=(SAddress&& addr) 		= default;
	SAddress& operator=(const SAddress& addr) 	= default;
	/**
	 * ------------------------------------------------------------------------
	 * constructors
	 * ------------------------------------------------------------------------
	 * process constructor
	 */
	SAddress( 
		const std::string& addr
	);
	SAddress(
		const std::string& user, 
		const std::string& host, 
		const uint16_t     port, 
		const std::string& path
	);
	/**
	 * derivated constructor
	 */
	SAddress(const char* addr): SAddress(std::string(addr)){}
	/**
	 * ------------------------------------------------------------------------
	 * accessors
	 * ------------------------------------------------------------------------
	 */
	inline const std::string& User()    const {
		return __name;
	}
	inline const std::string& File()    const {
		return __host;
	}
	inline const std::string& Host()    const {
		return __host;
	}
	inline const uint16_t     Port()    const {
		return __port;
	}
	inline const std::string& Path()    const {
		return __path;
	}
	inline const std::string& Channel() const {
		return __path;
	}
	/**
	 * ------------------------------------------------------------------------
	 * friends
	 * ------------------------------------------------------------------------
	 */
  	friend SAddress operator+(const SAddress& lhs, const SAddress& rhs) {
		return SAddress(
		  	Merge(lhs.User(), "_", rhs.User()),
			Merge(lhs.Host(), ".", rhs.Host()),
		  	lhs.Port() + rhs.Port(),
		  	Merge(lhs.Path(), "/", rhs.Path())
		);
	}
private:
	/**
	 * ------------------------------------------------------------------------
	 * attributes
	 * ------------------------------------------------------------------------
	 */
	std::string   __name;
	std::string   __host;
	uint16_t      __port;
	std::string   __path;
	/**
	 * ------------------------------------------------------------------------
	 * utils
	 * ------------------------------------------------------------------------
	 */
	static std::string Merge(std::string s1, std::string sep, std::string s2) {
		if(s1.empty() || s2.empty()){
			return s1 + s2;
		}
		return s1 + sep + s2;
	}
};
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SADDRESS_H */
