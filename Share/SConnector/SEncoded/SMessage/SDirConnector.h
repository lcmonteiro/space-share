/* 
 * File:   SDirConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
 */
#ifndef SDIRSTREAMCODED_H
#define SDIRSTREAMCODED_H
/**
 */
#include "SKernel/SContainer.h"
#include "SKernel/SConnector.h"
/**
 * Base coded streams
 */
#include "Sbase/SIDirConnector.h"
#include "Sbase/SODirConnector.h"
/**
 * Begin namespace Code
 */
namespace Code {
/**
 * Input UDP Connector  template
 */
template<class T>
class SIDirConnectorT : public T {
public:
	/**
	 * make
	 */
	template<typename...Args>
	static Code::IConnector Make(Args &&...args) {
		return make_shared<SIDirConnectorT>(forward<Args>(args)...);
	}
	/**
	 * constructor
	 */
	SIDirConnectorT(const string address) : T(address) {
	}
};
/**
 * Output UDP Connector  template
 */
template<class T>
class SODirConnectorT : public T {
public:
	/**
	 * make
	 */
	template<typename...Args>
	static Code::OConnector Make(Args &&...args) {
		return make_shared<SODirConnectorT>(forward<Args>(args)...);
	}
	/**
	 * constructor
	 */
	SODirConnectorT(
		const string address, 
		const size_t files
	) : T(address, files) {
	}
};
/**
 * definitions
 */
typedef SIDirConnectorT<SIDirConnector> IDirConnector;
typedef SODirConnectorT<SODirConnector> ODirConnector;
/**
 * End namespace Code
 */
}
#endif /* SDIRSTREAMCODED_H */

