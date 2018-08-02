/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SFileConnector.h
 * Author: root
 *
 * Created on December 2, 2016, 2:13 PM
 */

#ifndef SFILESTREAMSOCKET_H
#define SFILESTREAMSOCKET_H
/**
 */
#include "SKernel/SContainer.h"
#include "SKernel/SConnector.h"
/**
 * Base item Connectors
 */
#include "Sbase/SIFileConnector.h"
#include "Sbase/SOFileConnector.h"
/**
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 * Input File Connector template
 */
template<class T>
class SIFileConnectorT : public T {
public:
	/**
	 * make
	 */
	template<typename...Args>
	static IConnector Make(Args &&...args) {
		return make_shared<SIFileConnectorT>(forward<Args>(args)...);
	}
public:
	/**
	 * constructor
	 */
	SIFileConnectorT() = default;

	SIFileConnectorT(
		const string address,
		const size_t sframes
	) : T(address, sframes) {
	}
	/**
	 * destructor
	 */
	virtual ~SIFileConnectorT() = default;
};
/**
 * Output File Connector template
 */
template<class T>
class SOFileConnectorT : public T {
public:
	/**
	 * make
	 */
	template<typename...Args>
	static OConnector Make(Args &&...args) {
		return make_shared<SOFileConnectorT>(forward<Args>(args)...);
	}
public:
	/**
	 * constructor
	 */
	SOFileConnectorT() = default;

	SOFileConnectorT(const string address) : T(address) {
	}
	/**
	 * destructor
	 */
	virtual ~SOFileConnectorT() = default;
};
/**
 * definitions
 */
typedef SIFileConnectorT<SIFileConnector> IFileConnector;
typedef SOFileConnectorT<SOFileConnector> OFileConnector;
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
/**
 */
#endif /* SFILESTREAMDATA_H */

