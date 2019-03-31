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
//#include "SKernel/SIOMessageConnector.h"
#include "SKernel/SIFileConnector.h"
//#include "SKernel/SOMessageConnector.h"
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
        //Super::Bind(uri.File());
    }
    inline void Wait(const SAddress& uri) {
        //Super::Bind(uri.File());
    }
    inline void Link(const SAddress& uri) {
        //Super::Link(uri.File());
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
        const size_t maxsmsg;
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

