/* 
 * Container:   SIrcConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SIRCSTREAMCODED_H
#define SIRCSTREAMCODED_H
/**
 */
#include "SKernel/SContainer.h"
#include "SKernel/SConnector.h"
/**
 * Base coded streams
 */
#include "Sbase/SIIrcConnector.h"
#include "Sbase/SOIrcConnector.h"
#include "Sbase/SIOIrcConnector.h"
/**
 * Begin namespace Code
 */
namespace Code {
/**
 * Input UDP Connector  template
 */
template<class T>
class SIIrcConnectorT : public T {
public:
	/**
	 * make
	 */
	template<typename...Args>
	static Code::IConnector Make(Args &&...args) {
		return make_shared<SIIrcConnectorT>(forward<Args>(args)...);
	}
	/**
	 * constructor
	 */
	SIIrcConnectorT(const string address) : T(address) {
	}
};
/**
 * Output UDP Connector  template
 */
template<class T>
class SOIrcConnectorT : public T {
public:
	/**
	 * make
	 */
	template<typename...Args>
	static Code::OConnector Make(Args &&...args) {
		return make_shared<SOIrcConnectorT>(forward<Args>(args)...);
	}
	/**
	 * constructor
	 */
	SOIrcConnectorT(const string address) : T(address) {
	}
};
/**
 * InOutput UDP Connector  template
 */
template<class T>
class SIOIrcConnectorT : public T {
public:
	/**
	 * make
	 */
	template<typename...Args>
	static Code::IOConnector Make(Args &&...args) {
		return make_shared<SIOIrcConnectorT>(forward<Args>(args)...);
	}
	/**
	 * constructor
	 */
	SIOIrcConnectorT(const string address) : T(address) {
	}
};
/**
 * definitions
 */
typedef SIIrcConnectorT<SIIrcConnector>   IIrcConnector;
typedef SOIrcConnectorT<SOIrcConnector>   OIrcConnector;
typedef SIOIrcConnectorT<SIOIrcConnector> IOIrcConnector;
/**
 * End namespace Code
 */
}
/**
 */
#endif /* SIRCSTREAMCODED_H */

