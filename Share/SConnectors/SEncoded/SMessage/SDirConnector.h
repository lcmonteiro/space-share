/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SDirConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SDIRSTREAMCODED_H
#define SDIRSTREAMCODED_H
/**
 * space
 */
#include "SContainer.h"
#include "SConnector.h"
/**
 * connector
 */
#include "SKernel//SIDirConnector.h"
#include "SKernel//SODirConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
namespace Message {
/**
 * ----------------------------------------------------------------------------
 * Input DIR Connector
 * ----------------------------------------------------------------------------
 * template
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
	SIDirConnectorT(const string address) : T(address) {}
};
/**
 * ----------------------------------------------------------------------------
 * Output DIR Connector
 * ----------------------------------------------------------------------------  
 * template
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
	) : T(address, files) {}
};
/**
 * ----------------------------------------------------------------------------
 * Definitions
 * ----------------------------------------------------------------------------
 */
typedef SIDirConnectorT<SIDirConnector> IDirConnector;
typedef SODirConnectorT<SODirConnector> ODirConnector;
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SDIRSTREAMCODED_H */

