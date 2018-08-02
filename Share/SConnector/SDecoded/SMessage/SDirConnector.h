/* 
 * Container:   SDirConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
 */
#ifndef SDIRSTREAMSOCKET_H
#define SDIRSTREAMSOCKET_H
/**
 */
#include "SKernel/SContainer.h"
#include "SKernel/SConnector.h"
/**
 * Base item streams
 */
#include "Sbase/SIDirConnector.h"
#include "Sbase/SODirConnector.h"
/**
 * Begin namespace Item
 */
namespace Item {
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
	static Item::IConnector Make(Args &&...args) {
		return make_shared<SIDirConnectorT>(forward<Args>(args)...);
	}
	/**
	 * constructor
	 */
	SIDirConnectorT(const string address, const string file) : T(address, file) {
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
	static Item::OConnector Make(Args &&...args) {
		return make_shared<SODirConnectorT>(forward<Args>(args)...);
	}
	/**
	 * constructor
	 */
	SODirConnectorT(
		const string address
	) : T(address) {
	}
};
/**
 * definitions
 */
typedef SIDirConnectorT<SIDirConnector> IDirConnector;
typedef SODirConnectorT<SODirConnector> ODirConnector;
/**
 * End namespace Item
 */
}
/**
 */
#endif /* SDIRSTREAMSOCKET_H */

