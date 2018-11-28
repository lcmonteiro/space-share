/* 
 * File:   STcpStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 11:17 PM
 */
#ifndef STCPSTREAMCONNECTOR_H
#define STCPSTREAMCONNECTOR_H
/**
 * Space Kernel
 */
#include "SContainer.h"
#include "SConnector.h"
/**
 * Share
 */
#include "SIStreamConnector.h"
#include "SOStreamConnector.h"
#include "SIOStreamConnector.h"
/**
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Stream
 */
namespace Stream {
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Resource adapter
 * ---------------------------------------------------------------------------------------------------------------------
 */
class ResourceAdapterTcp : private SSocketResource {
public:
    using SSocketResource::SSocketResource;
    using SSocketResource::operator=;
    /**
     * interfaces
     */
    inline SSocketResource& Base() {
        return *this;
    }
    inline void Wait(const SAddress& uri) {
        SSocketResource::Wait(uri.Host(), uri.Port(), STREAM);
    }
    inline void Fill(IFrame& buf) {
        SSocketResource::Fill(buf);
    }
    inline void Drain(const Frame& buf) {
        SSocketResource::Drain(buf);
    }
    inline bool Good() {
        return SSocketResource::Good();
    }
    inline void Reset() {
        *this = SSocketResource();
    }
};    
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Input TCP Connector
 * ---------------------------------------------------------------------------------------------------------------------
 * template
 */
template<class R>
class SITcpConnectorT : public SIOStreamConnector<R> {
public:
    using SIStreamConnector<R>::SIStreamConnector;
    /**
     */
    SITcpConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static IConnector Make(Args &&...args) {
        return make_shared<SITcpConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Output TCP Connector
 * ---------------------------------------------------------------------------------------------------------------------
 * template
 */
template<class R>
class SOTcpConnectorT : public SOStreamConnector<R> {
public:
    using SOStreamConnector<R>::SOStreamConnector;
    /**
     */
    SOTcpConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static OConnector Make(Args &&...args) {
        return make_shared<SOTcpConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * IO TCP Connector
 * ---------------------------------------------------------------------------------------------------------------------
 * template
 */
template<class R>
class SIOTcpConnectorT : public SIOStreamConnector<R> {
public:
    using SIOStreamConnector<R>::SIOStreamConnector;
    /**
     */
    SIOTcpConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static IOConnector Make(Args &&...args) {
        return make_shared<SIOTcpConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * definition
 * ---------------------------------------------------------------------------------------------------------------------
 */
typedef SIOTcpConnectorT<ResourceAdapterTcp> IOTcpConnector;
typedef SITcpConnectorT<ResourceAdapterTcp>  ITcpConnector;
typedef SOTcpConnectorT<ResourceAdapterTcp>  OTcpConnector;
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
#endif /* STCPSTREAMCONNECTOR_H */

