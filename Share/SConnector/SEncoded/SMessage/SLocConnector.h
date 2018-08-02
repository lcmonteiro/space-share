/** 
 * File:   SFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 2, 2016, 2:13 PM
 */
#ifndef SFILESTREAMCODED_H
#define SFILESTREAMCODED_H
/**
 */
#include "SKernel/SContainer.h"
#include "SKernel/SConnector.h"
/**
 * Base coded streams
 */
#include "Sbase/SIFileConnector.h"
#include "Sbase/SOFileConnector.h"
/**
 * Begin namespace Item
 */
namespace Code {
/**
 * Input FILE Connector coded template
 */
template<class T>
class SIFileConnectorT : public T {
public:
	/**
	 * make
	 */
	template<typename...Args>
	static Code::IConnector Make(Args &&...args) {
		return make_shared<SIFileConnectorT>(forward<Args>(args)...);
	}
	/**
	 * constructor
	 */
	SIFileConnectorT(const string address) : T(address) {
	}
};
/**
 * Output FILE Connector coded template
 */
template<class T>
class SOFileConnectorT : public T {
public:
	/**
	 * make
	 */
	template<typename...Args>
	static Code::OConnector Make(Args &&...args) {
		return make_shared<SOFileConnectorT>(forward<Args>(args)...);
	}
	/**
	 * constructor
	 */
	SOFileConnectorT(const string address) : T(address) {
	}
};
/**
 * definitions
 */
typedef SIFileConnectorT<SIFileConnector> IFileConnector;
typedef SOFileConnectorT<SOFileConnector> OFileConnector;
/**
 * End namespace Item
 */
}
/**
 */
#endif /* SFILESTREAMCODED_H */

