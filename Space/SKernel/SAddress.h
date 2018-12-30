/**
 * File:   SAddress.h
 * Author: Luis Monteiro
 *
 * Created on November 21, 2016, 12:10 PM
 */
#ifndef SADDRESS_H
#define SADDRESS_H
/**
 * std
 */
#include <string>
/**
 */
using namespace std;
/**
 */
class SAddress : public string {
public:
	/**
	 * defaut constructor
	 */
	SAddress() = default;

	SAddress(SAddress&& addr) = default;
        
	SAddress(const SAddress& addr) = default;
	/**
	 * process constructor
	 */
	SAddress( 
		const string& addr
	);
	SAddress(
		const string& user, 
		const string& host, 
		const uint16_t port, 
		const string& path
	);
	/**
	 * derivated constructor
	 */
	SAddress(const char* addr): SAddress(string(addr)){}
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
	/**
	 * friends
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
	 * attributes
	 */
	string   __name;
	string   __host;
	uint16_t __port;
	string   __path;
	/**
	 * utils
	 */
	static string Merge(string s1, string sep, string s2){
		if(s1.empty() || s2.empty()){
			return s1 + s2;
		}
		return s1 + sep + s2;
	}
};

#endif /* SADDRESS_H */
