/* 
 * File:   SUdpMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 11:17 PM
 */
#ifndef SUDPMESSAGECONNECTOR_H
#define SUDPMESSAGECONNECTOR_H
/**
 * Space
 */
#include "SKernel/SContainer.h"
#include "SKernel/SConnector.h"
#include "SResource/SSocketResource.h"

/**
 * Share
 */
#include "SKernel/SIOMessageConnector.h"
#include "SKernel/SIMessageConnector.h"
#include "SKernel/SOMessageConnector.h"
/**
 * tools
 */
#include "STools/SDefault.h"
/**
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Stream
 */
namespace Message {
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Resource adapter
 * ---------------------------------------------------------------------------------------------------------------------
 */
class ResourceAdapterUdp : private SSocketResource {
public:
        using SSocketResource::SSocketResource;
        using SSocketResource::operator=;
        /**
         * interfaces
         */
        inline SSocketResource& Base() {
                return *this;
        }
        inline void Wait(const Address& uri) {
                SSocketResource::Wait(uri.Host(), uri.Port(), STREAM);
        }
        inline void Fill(Frame& buf) {
                SSocketResource::Fill(buf);
	}
        inline void Drain(const Frame& buf) {
                SSocketResource::Drain(buf);
        }
        inline bool Good() {
                SSocketResource::Good();
        }
        inline void Reset() {
                *this = SSocketResource();
        }
};    
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Input UDP Connector
 * ---------------------------------------------------------------------------------------------------------------------
 * template
 */
template<class R, class T>
class SIUdpConnectorT : public SIMessageConnector<R, T> {
public:
        using SIMessageConnector<R, T>::SIMessageConnector;
        /**
         */
        SIUdpConnectorT() = delete;
	/**
	 * make
	 */
	template<typename...Args>
	static IConnector Make(Args &&...args) {
		return make_shared<SIUdpConnectorT>(forward<Args>(args)...);
	}
};
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Output UDP Connector
 * ---------------------------------------------------------------------------------------------------------------------
 * template
 */
template<class R, class T>
class SOUdpConnectorT : public SOMessageConnector<R, T> {
public:
        using SOMessageConnector<R, T>::SOMessageConnector;
        /**
         */
        SOUdpConnectorT() = delete;
	/**
	 * make
	 */
	template<typename...Args>
	static OConnector Make(Args &&...args) {
		return make_shared<SOUdpConnectorT>(forward<Args>(args)...);
	}
};
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * IO UDP Connector
 * ---------------------------------------------------------------------------------------------------------------------
 * template
 */
template<class R, class T>
class SIOUdpConnectorT : public SIOMessageConnector<R, T> {
public:
        using SIOMessageConnector<R, T>::SIOMessageConnector;
        /**
         */
        SIOUdpConnectorT() = delete;
	/**
	 * make
	 */
	template<typename...Args>
	static IOConnector Make(Args &&...args) {
		return make_shared<SIOUdpConnectorT>(forward<Args>(args)...);
	}
};
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * definition
 * ---------------------------------------------------------------------------------------------------------------------
 */
typedef SIOUdpConnectorT<ResourceAdapterUdp, SDefault> IOUdpConnector;
typedef SIUdpConnectorT<ResourceAdapterUdp, SDefault>  IUdpConnector;
typedef SOUdpConnectorT<ResourceAdapterUdp, SDefault>  OUdpConnector;
/**
 * End namespace Stream
 */
}
/**
 * End namespace Decoded
 */
}
/**
 */
#endif /* SUDPMESSAGECONNECTOR_H */

