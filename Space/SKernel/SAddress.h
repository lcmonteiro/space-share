/**
 * ------------------------------------------------------------------------------------------------
 * File:   SAddress.h
 * Author: Luis Monteiro
 *
 * Created on November 21, 2016, 12:10 PM
 * ------------------------------------------------------------------------------------------------
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
	 * Defaults
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
	 * Constructors
	 * ------------------------------------------------------------------------
	 * process constructor
	 * ----------------------------------------------------
	 */
	SAddress( 
		const std::string& addr);
	SAddress(
		const std::string& user, 
		const std::string& host, 
		const uint16_t     port, 
		const std::string& path);
	/**
	 * ----------------------------------------------------
	 * derivated constructor
	 * ----------------------------------------------------
	 */
	SAddress(const char* addr)
	: SAddress(std::string(addr)) {}
	/**
	 * ------------------------------------------------------------------------
	 * Accessors
	 * ------------------------------------------------------------------------
	 */
	inline const std::string& user()    const {
		return __name;
	}
	inline const std::string& file()    const {
		return __host;
	}
	inline const std::string& host()    const {
		return __host;
	}
	inline const uint16_t     port()    const {
		return __port;
	}
	inline const std::string& path()    const {
		return __path;
	}
	inline const std::string& channel() const {
		return __path;
	}
	/**
	 * ------------------------------------------------------------------------
	 * Friends
	 * ------------------------------------------------------------------------
	 */
  	friend SAddress operator+(const SAddress& lhs, const SAddress& rhs) {
		return SAddress(
		  	__merge(lhs.user(), "_", rhs.user()),
			__merge(lhs.host(), ".", rhs.host()),
		  	__merge(lhs.port(),      rhs.port()),
		  	__merge(lhs.path(), "/", rhs.path()));
	}
private:
	/**
	 * ------------------------------------------------------------------------
	 * Variables
	 * ------------------------------------------------------------------------
	 */
	std::string   __name;
	std::string   __host;
	uint16_t      __port;
	std::string   __path;
	/**
	 * ------------------------------------------------------------------------
	 * Utils
	 * ------------------------------------------------------------------------
	 */
	static inline std::string __merge(
		const std::string& s1, const std::string& sep, const std::string& s2) {
		if(s1.empty() || s2.empty()){
			return s1 + s2;
		}
		return s1 + sep + s2;
	}
	static inline uint16_t __merge(uint16_t v1, uint16_t v2) {
		return v1 + v2;
	}
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SADDRESS_H */
