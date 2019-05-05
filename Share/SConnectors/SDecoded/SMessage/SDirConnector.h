/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SDirConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SDIRSTREAMSOCKET_H
#define SDIRSTREAMSOCKET_H
/**
 * space
 */
#include "SContainer.h"
#include "SConnector.h"
/**
 * share - connectors
 */
#include "SKernel/SIDirConnector.h"
#include "SKernel/SODirConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Item
 * ------------------------------------------------------------------------------------------------
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
	SIDirConnectorT(const std::string address, const std::string file) : T(address, file) {
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
 * ------------------------------------------------------------------------------------------------
 * End namespace Item
 * ------------------------------------------------------------------------------------------------
 */
}
/**
 */
#endif /* SDIRSTREAMSOCKET_H */

