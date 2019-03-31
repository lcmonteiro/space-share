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
#include "SKernel/SIOMessageConnector.h"
#include "SKernel/SIMessageConnector.h"
#include "SKernel/SOMessageConnector.h"
/**
 * Tools
 */
#include "SDefault.h"
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
    /**
     * interfaces
     */
    inline Super& Base() {
        return *this;
    }
    inline void Bind(const SAddress& uri) {
        Super::Bind(uri.File());
    }
    inline void Wait(const SAddress& uri) {
        Super::Bind(uri.File());
    }
    inline void Link(const SAddress& uri) {
        Super::Link(uri.File());
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
template <typename R, typename T> 
using SIMessageConnector = 
Layer::SIMessageConnector<
    T, Base::SIMessageConnector<R, SInputConnector>
>;
template<typename R, typename T>
class SILocConnectorT : public SIMessageConnector<R, T> {
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
    SILocConnectorT(Args &&...args) 
    : SIMessageConnector<R, T>(Properties{std::forward<Args>(args)...}) {} 
    /**
     * make
     */
    template<typename...Args>
    static IConnector Make(Args &&...args) {
        return std::make_shared<SILocConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Output LOC Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template <typename R, typename T> 
using SOMessageConnector = 
Layer::SOMessageConnector<
    T, Base::SOMessageConnector<R, SOutputConnector>
>;
template<typename R, typename T>
class SOLocConnectorT : public SOMessageConnector<R, T> {
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
    SOLocConnectorT(Args &&...args) 
    : SOMessageConnector<R, T>(Properties{std::forward<Args>(args)...}) {}
    /**
     * make
     */
    template<typename...Args>
    static OConnector Make(Args &&...args) {
        return std::make_shared<SOLocConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * IO LOC Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template <typename R, typename T> 
using SIOMessageConnector = 
Layer::SIMessageConnector<
    T, Layer::SOMessageConnector<
        T, Base::SIOMessageConnector<R, SInOutputConnector>
    >
>;
template<typename R, typename T>
class SIOLocConnectorT : public SIOMessageConnector<R, T> {
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
    SIOLocConnectorT(Args &&...args) 
    : SIOMessageConnector<R, T>(Properties{std::forward<Args>(args)...}) {}
    /**
     * make
     */
    template<typename...Args>
    static IOConnector Make(Args &&...args) {
        return std::make_shared<SIOLocConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Definition
 * ------------------------------------------------------------------------------------------------
 */
typedef SIOLocConnectorT<ResourceAdapterLoc, SDefault> IOLocConnector;
typedef SILocConnectorT<ResourceAdapterLoc, SDefault>  ILocConnector;
typedef SOLocConnectorT<ResourceAdapterLoc, SDefault>  OLocConnector;
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SFILEMESSAGECONNECTOR_H */

