/* 
 * Container:   SLocConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLOCALCONNECTOR_H
#define SLOCALCONNECTOR_H
/**
 */
#include "SKernel/SContainer.h"
/**
 * Base Connectors
 */
#include "SKernel/SIMessageConnector.h"
/**
 * Begin namespace Message
 */
//namespace Message {
///**
// * Input LOCAL Connector break template
// */
//template<class S>
//class SILocConnectorT : public S {
//public:
//	/**
//	 * make
//	 */
//	template<typename...Args>
//	static Decoded::IConnector Make(Args &&...args) {
//		return make_shared<SILocConnectorT>(forward<Args>(args)...);
//	}
//	/**
//	 * constructor
//	 */
//	SILocConnectorT(
//		const string address,
//		const string local,
//		const size_t nframes,
//		const size_t sframes
//	) : S(address, local, nframes, sframes) {}
//};
///**
// * Output LOCAL Connector template
// */
//template<class S>
//class SOLocConnectorT : public S {
//public:
//	/**
//	 * make
//	 */
//	template<typename...Args>
//	static Decoded::OConnector Make(Args &&...args) {
//		return make_shared<SOLocConnectorT>(forward<Args>(args)...);
//	}
//	/**
//	 * constructor
//	 */
//	SOLocConnectorT(const string address, const string local) : S(address, local) {}
//};
///**
// * definitions	
// */
//typedef SILocConnectorT<SILocConnector> ILocConnector;
//typedef SOLocConnectorT<SOLocConnector> OLocConnector;
///**
// * End namespace Message
// */
//}
/**
 */
#endif /* SLOCALCONNECTOR_H */

