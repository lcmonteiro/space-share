/**
 * ------------------------------------------------------------------------------------------------
 * File:   SFileMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 11:17 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SFILEMESSAGECONNECTORCODED_H
#define SFILEMESSAGECONNECTORCODED_H
/**
 * space
 */
#include "SContainer.h"
#include "SConnector.h"
#include "SFileResource.h"
/**
 * connector
 */
#include "SKernel/SIFileConnector.h"
#include "SKernel/SOFileConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
namespace Message {
/**
 * ----------------------------------------------------------------------------
 * Resource adapter
 * ----------------------------------------------------------------------------
 */
class ResourceAdapterFile : private SFileResource {
public:
    using Super = SFileResource;
    /**
     * default
     */
    using Super::Super;
    using Super::operator=;
    using Super::fill;
    using Super::drain;
    using Super::good;
    using Super::size;
    /**
     * interfaces
     */
    inline Super& base() {
        return *this;
    }
    inline void bind(const SAddress& uri) {
        *this = SIFileResource(uri);
    }
    inline void link(const SAddress& uri) {
        *this = SOFileResource(uri);
    }
    inline void reset() {
        *this = Super();
    }
};     
/**
 * ----------------------------------------------------------------------------
 * Input File Connector
 * ----------------------------------------------------------------------------
 * template
 */
template <typename R> 
using SIFileConnector = 
Layer::SIFileConnector<
    Base::SIFileConnector<R, SInputConnector>
>;
template<class R>
class SIFileConnectorT : public SIFileConnector<R> {
public:
    using SIFileConnector<R>::SIFileConnector;
    /**
     */
    SIFileConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static IConnector Make(Args &&...args) {
        return std::make_shared<SIFileConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ----------------------------------------------------------------------------
 * Output File Connector
 * ----------------------------------------------------------------------------
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
    using SOFileConnector<R>::SOFileConnector;
    /**
     */
    SOFileConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static OConnector Make(Args &&...args) {
        return std::make_shared<SOFileConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ----------------------------------------------------------------------------
 * Definition
 * ----------------------------------------------------------------------------
 */
typedef SIFileConnectorT<ResourceAdapterFile> IFileConnector;
typedef SOFileConnectorT<ResourceAdapterFile> OFileConnector;
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SFILEMESSAGECONNECTORCODED_H */
