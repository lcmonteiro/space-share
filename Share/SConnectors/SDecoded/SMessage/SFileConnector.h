/**
 * ------------------------------------------------------------------------------------------------
 * File:   SFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 2, 2016, 2:13 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SFILEMESSAGECONNECTOR_H
#define SFILEMESSAGECONNECTOR_H
/**
 * Space
 */
#include "SContainer.h"
#include "SConnector.h"
#include "SFileResource.h"
/**
 * Kernel
 */
#include "SKernel/SIFileConnector.h"
#include "SKernel/SOFileConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Decoded {
namespace Message {
/**
 * ------------------------------------------------------------------------------------------------
 * Resource adapter
 * ------------------------------------------------------------------------------------------------
 */
class ResourceAdapterFile : private SFileResource {
public:
    using Super = SFileResource;
    /**
     * default
     */
    using Super::Super;
    using Super::operator=;
    using Super::Read;
    using Super::Drain;
    using Super::Good;
    using Super::size;
    /**
     * interfaces
     */
    inline Super& Base() {
        return *this;
    }
    inline void Bind(const SAddress& uri) {
        *this = SIFileResource(uri);
    }
    inline void Link(const SAddress& uri) {
        *this = SOFileResource(uri);
    }
    inline void Reset() {
        *this = Super();
    }
}; 
/**
 * ------------------------------------------------------------------------------------------------
 * Input LOC Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template <typename R> 
using SIFileConnector = 
Layer::SIFileConnector<
    Base::SIFileConnector<R, SInputConnector>
>;
template<typename R>
class SIFileConnectorT : public SIFileConnector<R> {
public:
    /**
     * properties
     */
    typedef struct {
        const SText  address; 
        const size_t nframes;
    } Properties;
    /**
     * constructor
     */
    template<typename...Args>
    SIFileConnectorT(Args &&...args) 
    : SIFileConnector<R>(Properties{std::forward<Args>(args)...}) {} 
    /**
     * make
     */
    template<typename...Args>
    static IConnector Make(Args &&...args) {
        return std::make_shared<SIFileConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Output LOC Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template <typename R> 
using SOFileConnector = 
Layer::SOFileConnector<
    Base::SOFileConnector<R, SOutputConnector>
>;
template<typename R>
class SOFileConnectorT : public SOFileConnector<R> {
public:
    /**
     * properties
     */
    typedef struct {
        const SText address; 
    } Properties;
    /**
     * constructor
     */
    template<typename...Args>
    SOFileConnectorT(Args &&...args) 
    : SOFileConnector<R>(Properties{std::forward<Args>(args)...}) {}
    /**
     * make
     */
    template<typename...Args>
    static OConnector Make(Args &&...args) {
        return std::make_shared<SOFileConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * IO LOC Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */

/**
 * ------------------------------------------------------------------------------------------------
 * Definition
 * ------------------------------------------------------------------------------------------------
 */
typedef SIFileConnectorT<ResourceAdapterFile>  IFileConnector;
typedef SOFileConnectorT<ResourceAdapterFile>  OFileConnector;
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 * 
 * 
 * 
 */
#endif /* SFILEMESSAGECONNECTOR_H */

