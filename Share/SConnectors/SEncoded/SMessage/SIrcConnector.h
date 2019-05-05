/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SIrcConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SIRCCONNECTORCODED_H
#define SIRCCONNECTORCODED_H
/**
 * space
 */
#include "SContainer.h"
#include "SConnector.h"
/**
 * connector
 */
#include "SKernel/SIIrcConnector.h"
#include "SKernel/SOIrcConnector.h"
#include "SKernel/SIOIrcConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
namespace Message {
/**
 * ----------------------------------------------------------------------------
 * Input IRC Connector
 * ----------------------------------------------------------------------------
 * template
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
 * ----------------------------------------------------------------------------
 * Output IRC Connector
 * ----------------------------------------------------------------------------
 * template
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
	SOIrcConnectorT(const string address) : T(address) {}
};
/**
 * ----------------------------------------------------------------------------
 * InOutput IRC Connector  
 * ----------------------------------------------------------------------------
 * template
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
 * ----------------------------------------------------------------------------
 * Definitions
 * ----------------------------------------------------------------------------
 */
typedef SIIrcConnectorT<SIIrcConnector>   IIrcConnector;
typedef SOIrcConnectorT<SOIrcConnector>   OIrcConnector;
typedef SIOIrcConnectorT<SIOIrcConnector> IOIrcConnector;
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SIRCCONNECTORCODED_H */

