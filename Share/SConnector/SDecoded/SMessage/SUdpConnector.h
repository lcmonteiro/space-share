/* 
 * Container:   SUdpConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SUDPCONNECTOR_H
#define SUDPCONNECTOR_H
/**
 */
#include "SKernel/SContainer.h"
#include "SKernel/SConnector.h"
/**
 * Base connectors
 */
#include "SKernel/SIUdpConnector.h"
#include "SKernel/SOUdpConnector.h"
/**
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 * Input UDP Connector break template
 */
template<class S>
class SIUdpConnectorT : public S {
public:
	/**
	 * make
	 */
	template<typename...Args>
	static Decoded::IConnector Make(Args &&...args) {
		return make_shared<SIUdpConnectorT>(forward<Args>(args)...);
	}
	/**
	 * constructor
	 */
	SIUdpConnectorT(
		const string address,
		const string local,
		const size_t nframes
	) : S(address, local, nframes) {}
};
/**
 * Output UDP Connector template
 */
template<class S>
class SOUdpConnectorT : public S {
public:
	/**
	 * make
	 */
	template<typename...Args>
	static Decoded::OConnector Make(Args &&...args) {
		return make_shared<SOUdpConnectorT>(forward<Args>(args)...);
	}
	/**
	 * constructor
	 */
	SOUdpConnectorT(const string address, const string local) : S(address, local) {}
};
/**
 * definitions	
 */
typedef SIUdpConnectorT<SIUdpConnector> IUdpConnector;
typedef SOUdpConnectorT<SOUdpConnector> OUdpConnector;
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
#endif /* SUDPCONNECTOR_H */

