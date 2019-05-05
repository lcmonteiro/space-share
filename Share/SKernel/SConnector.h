/**
 * ------------------------------------------------------------------------------------------------ 
 * Connector: Connector.h
 * Author: Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SCONNECTOR_H
#define SCONNECTOR_H
/**
 * std
 */
#include <random>
#include <list>
#include <ctime>
#include <memory>
#include <iomanip>
#include <iostream>
#include <system_error>
/**
 * space 
 */
#include "SDocument.h"
#include "SResource.h"
#include "SAddress.h"
#include "SEnergy.h"
#include "SRoad.h"
#include "SLog.h"
#include "STask.h"
/**
 * -----------------------------------------------------------------------------------------------
 * Exceptions
 * -----------------------------------------------------------------------------------------------
 */
typedef class SConnectorExection : public std::system_error {
public:
    /**
     * constructor
     */
    SConnectorExection(std::string uri, std::error_code ec) 
    : system_error(ec), __uri(uri) {
    }
    SConnectorExection(std::string uri, std::error_code ec, const std::string& what) 
    : system_error(ec, what), __uri(uri) {
    }
    /**
     * operator
     */
    inline std::string operator()(void) const {
        return __uri;
    }
private:
    std::string __uri;
} ConnectorExection;
/**
 * ----------------------------------------------------------------------------
 * Timeout
 * ----------------------------------------------------------------------------
 */
typedef class SConnectorExceptionTIMEOUT : public SConnectorExection {
public:
    using SConnectorExection::SConnectorExection;
    /**
     * constructor
     */
    SConnectorExceptionTIMEOUT(std::string s) 
    : SConnectorExection(s, std::make_error_code(std::errc::no_message)) {
    }
} ConnectorExceptionTIMEOUT;
typedef class SIConnectorExceptionTIMEOUT : public ConnectorExceptionTIMEOUT {
public:
    using ConnectorExceptionTIMEOUT::ConnectorExceptionTIMEOUT;
} IConnectorExceptionTIMEOUT;
typedef class SOConnectorExceptionTIMEOUT : public ConnectorExceptionTIMEOUT {
public:
    using ConnectorExceptionTIMEOUT::ConnectorExceptionTIMEOUT;
} OConnectorExceptionTIMEOUT;
/**
 * ----------------------------------------------------------------------------
 * Dead
 * ----------------------------------------------------------------------------
 */
typedef class SConnectorExceptionDead : public SConnectorExection {
public:
    using SConnectorExection::SConnectorExection;
    /**
     * constructor
     */
    SConnectorExceptionDead(std::string s) 
    : SConnectorExection(s, std::make_error_code(std::errc::no_message)) {
    }
} ConnectorExceptionDEAD;
typedef class SIConnectorExceptionDead : public ConnectorExceptionDEAD {
public:
    using ConnectorExceptionDEAD::ConnectorExceptionDEAD;
} IConnectorExceptionDEAD;
typedef class SOConnectorExceptionDead : public ConnectorExceptionDEAD {
public:
    using ConnectorExceptionDEAD::ConnectorExceptionDEAD;
} OConnectorExceptionDEAD;
/**
 * ------------------------------------------------------------------------------------------------
 * Connenctor Base
 * ------------------------------------------------------------------------------------------------
 **/
class SConnector: public SLog, protected SEnergy<ConnectorExceptionDEAD> {
    /**
     * type definitions
     */
    using Task = STask;
public:
    using Key  = std::string;
    /**
     * ------------------------------------------------------------------------
     * Defaults
     * ------------------------------------------------------------------------
     */
    SConnector()          = default;
    virtual ~SConnector() = default;
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SConnector(std::string uri, size_t energy = 1) 
    : SLog(), SEnergy(energy), __uri(uri) { }
    /**
     * ------------------------------------------------------------------------
     * Interface
     * ------------------------------------------------------------------------
     * Get URI 
     * ----------------------------------------------------
     */
    inline const SAddress& uri() const {
        return __uri;
    }
    /**
     * ----------------------------------------------------
     * Set Energy
     * ----------------------------------------------------
     */
    inline void energy(size_t energy) {
        SEnergy::set(energy);    
    }
    /**
     * ----------------------------------------------------
     * Get Energy
     * ----------------------------------------------------
     */
    inline size_t energy() {
        return SEnergy::get();
    }
    /**
     * ----------------------------------------------------
     * Is worker is inactive 
     * ----------------------------------------------------
     */
    inline bool inactive() {
        return !__waiter.joinable();
    }
    /**
     * ----------------------------------------------------
     * Build Connector
     * ----------------------------------------------------
     */
    inline void build() {
        /**
         * decay energy resource
         */ 
        SEnergy::decay();
        /**
         * enable build
         */
        __waiter = STask([this]() {
            try {
                _open();
            } catch (std::exception& ){} catch (...) {
                throw;
            }
        });
    }
    /**
     * ----------------------------------------------------
     * Detroy Connector
     * ----------------------------------------------------
     **/
    inline void destroy() {
        /**
         * cancel decay
         */
         SEnergy::cancel();
        /**
         * enable waiter
         */
        __waiter = STask([this]() {
            try {
                _close();
            } catch (std::exception& ){} catch (...) {
                throw;
            }
        });
    }
    /**
     * ----------------------------------------------------
     * Check Status
     * ----------------------------------------------------
     */
    inline bool good() {
        return !empty() && _good();
    }
    /**
     * ----------------------------------------------------
     * Wait (timeout) to be good
     * ----------------------------------------------------
     */
    SConnector& wait(std::chrono::milliseconds timeout);
protected:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     **
     * stream identifier
     */
    SAddress __uri;
    /**
     * worker
     */
    Task __waiter;
    /**
     * energy
     */
    size_t __energy;
    /**
     * ------------------------------------------------------------------------
     * Interfaces
     * ------------------------------------------------------------------------
     * close
     **/
    virtual void _close() = 0;
    /**
     * open
     */
    virtual void _open() = 0;
    /**
     * good
     */
    virtual bool _good() = 0;
    /**
     * ------------------------------------------------------------------------
     * utilities
     * ------------------------------------------------------------------------
     * reshape 
     */
    std::list<std::pair<size_t, size_t>> _shape(size_t len, size_t split);
    /**
     * ------------------------------------------------------------------------
     * Logging
     * ------------------------------------------------------------------------
     */
    inline void _debug  (const std::string& msg) { SLog::_debug  (__uri, msg); }
    inline void _info   (const std::string& msg) { SLog::_info   (__uri, msg); }
    inline void _warning(const std::string& msg) { SLog::_warning(__uri, msg); }
    inline void _error  (const std::string& msg) { SLog::_error  (__uri, msg); }
};
/**
 * ----------------------------------------------------------------------------
 * Definitions
 * ----------------------------------------------------------------------------
 */
typedef std::shared_ptr<SConnector> Connector;
/**
 * ------------------------------------------------------------------------------------------------
 * IO decoded stream  
 * ------------------------------------------------------------------------------------------------
 **/
namespace Decoded {
/**
 * ----------------------------------------------------------------------------
 * InputConnector
 * ----------------------------------------------------------------------------
 */
class SInputConnector : public SConnector {
public:
    using SConnector::SConnector;
    /**
     * ----------------------------------------------------
     * Constructor
     * ----------------------------------------------------
     */
    SInputConnector() = default;
    /**
     * ----------------------------------------------------
     * Get Resource
     * ----------------------------------------------------
     */
    virtual Resource& resource() = 0;
    /**
     * ----------------------------------------------------
     * Read Data
     * ----------------------------------------------------
     */
    inline Document read() {
        try {
            return _read();
        } catch (ResourceExceptionTIMEOUT& ex) {
            INFO(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw IConnectorExceptionDEAD(__uri);
        }  catch (ContainerException& ex){
            ERROR(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        }
    }
    /**
     * ----------------------------------------------------
     * Read Residual Data 
     * ----------------------------------------------------
     */
    inline std::list<Document> drain() {
        try {
            return _drain();
        } catch (ResourceExceptionTIMEOUT& ex) {
            INFO(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw IConnectorExceptionDEAD(__uri);
        }
    }
protected:
    /**
     * ----------------------------------------------------
     * IO interfaces
     * ----------------------------------------------------
     **
     * read
     */
    virtual Document _read() = 0;
    /**
     * drain 
     */
    virtual std::list<Document> _drain() { 
        return {}; 
    }
};
/**
 * ----------------------------------------------------------------------------
 * OutputConnector
 * ----------------------------------------------------------------------------
 */
class SOutputConnector: public SConnector {
public:
    using SConnector::SConnector;
    /**
     * ----------------------------------------------------
     * Constructor
     * ----------------------------------------------------
     */
    SOutputConnector() = default;
    /**
     * ----------------------------------------------------
     * Write Data
     * ----------------------------------------------------
     */
    inline void write(const Document& data){
        try {
            _write(data);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw OConnectorExceptionDEAD(__uri);
        }
    }
protected:
    /**
     * ----------------------------------------------------
     * IO interfaces
     * ----------------------------------------------------
     * write
     **/
    virtual void _write(const Document& container) = 0;
};
/**
 * ----------------------------------------------------------------------------
 * InOutputConnector
 * ----------------------------------------------------------------------------
 */
class SInOutputConnector : public SConnector {
public:
    using SConnector::SConnector;
    /**
     * ----------------------------------------------------
     * Constructor
     * ----------------------------------------------------
     */
    SInOutputConnector() = default;
    /**
     * ----------------------------------------------------
     * Get Resource
     * ----------------------------------------------------
     */
    virtual Resource& resource() = 0;
    /**
     * ----------------------------------------------------
     * Read Data
     * ----------------------------------------------------
     */
    inline Document read() {
        try {
            return _read();
        } catch (ResourceExceptionTIMEOUT& ex) {
            INFO(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw IConnectorExceptionDEAD(__uri);
        }  catch (ContainerException& ex){
            ERROR(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        }
    }
    /**
     * ----------------------------------------------------
     * Read Residual Data 
     * ----------------------------------------------------
     */
    inline std::list<Document> drain() {
        try {
            return _drain();
        } catch (ResourceExceptionTIMEOUT& ex) {
            INFO(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw IConnectorExceptionDEAD(__uri);
        }
    }
    /**
     * ----------------------------------------------------
     * Write Data
     * ----------------------------------------------------
     */
    inline void write(const Document& data) {
        try {
            _write(data);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw OConnectorExceptionDEAD(__uri);
        }
    }
protected:
    /**
     * ----------------------------------------------------
     * IO interfaces
     * ----------------------------------------------------
     **
     * read
     */
    virtual Document _read() = 0;
    /**
     * drain  
     */
    virtual std::list<Document> _drain() {
        return {}; 
    }
    /**
     * write 
     */
    virtual void _write(const Document& container) = 0;
};
/**
 * ----------------------------------------------------------------------------
 * Definitions
 * ----------------------------------------------------------------------------
 */
typedef std::shared_ptr<SInputConnector>    IConnector;
typedef std::shared_ptr<SOutputConnector>   OConnector;
typedef std::shared_ptr<SInOutputConnector> IOConnector;
}
/**
 * ------------------------------------------------------------------------------------------------
 * IO encoded stream  
 * ------------------------------------------------------------------------------------------------
 **/
namespace Encoded {
/**
 * ----------------------------------------------------------------------------
 * InputConnector
 * ----------------------------------------------------------------------------
 */
class SInputConnector : public SConnector {
public:
    using SConnector::SConnector;
    /**
     * ----------------------------------------------------
     * Constructor
     * ----------------------------------------------------
     */
    SInputConnector() = default;
    /**
     * ----------------------------------------------------
     * Get Resource
     * ----------------------------------------------------
     */
    virtual Resource& resource() = 0;
    /**
     * ----------------------------------------------------
     * Read Coded Data
     * ----------------------------------------------------
     */
    inline Document read() {
        try {
            return _read();
        } catch (ResourceExceptionTIMEOUT& ex) {
            INFO(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw IConnectorExceptionDEAD(__uri);
        } catch (ContainerException& ex){
            ERROR(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        }
    }
    /**
     * ----------------------------------------------------
     * Read Residual Coded Data 
     * ----------------------------------------------------
     */
    inline std::list<Document> drain() {
        try {
            return _drain();
        } catch (ResourceExceptionTIMEOUT& ex) {
            INFO(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw IConnectorExceptionDEAD(__uri);
        }
    }
protected:
    /**
     * ----------------------------------------------------
     * Variables
     * ----------------------------------------------------
     * machine state
     */
    size_t __state;
    /**
     * ----------------------------------------------------
     * IO interfaces
     * ----------------------------------------------------
     **
     * read
     */
    virtual Document _read() = 0;
    /**
     * drain
     */
    virtual std::list<Document> _drain() { 
        return {}; 
    }
};
/**
 * ----------------------------------------------------------------------------
 * OutputConnector
 * ----------------------------------------------------------------------------
 */
class SOutputConnector : public SConnector {
public:
    using SConnector::SConnector;
    /**
     * ----------------------------------------------------
     * Constructor
     * ----------------------------------------------------
     */
    SOutputConnector() = default;
    /**
     * ----------------------------------------------------
     * Write Coded Data
     * ----------------------------------------------------
     */
    inline void write(const Document& data){
        try {
            _write(data);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw OConnectorExceptionDEAD(__uri);
        }
    }
protected:
    /**
     * ----------------------------------------------------
     * IO interfaces
     * ----------------------------------------------------
     * write
     **/
    virtual void _write(const Document& container) = 0;
};
/**
 * ----------------------------------------------------------------------------
 * InOutputConnector
 * ----------------------------------------------------------------------------
 */
class SInOutputConnector: public SConnector {
public:
    using SConnector::SConnector;
    /**
     * ----------------------------------------------------
     * Constructor
     * ----------------------------------------------------
     */
    SInOutputConnector() = default;
    /**
     * ----------------------------------------------------
     * Get Resource
     * ----------------------------------------------------
     */
    virtual Resource& resource() = 0;
    /**
     * ----------------------------------------------------
     * Read Coded Data
     * ----------------------------------------------------
     */
    inline Document read(){
        try {
            return _read();
        } catch (ResourceExceptionTIMEOUT& ex) {
            INFO(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw IConnectorExceptionDEAD(__uri);
        } catch (ContainerException& ex){
            ERROR(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        }
    }
    /**
     * ----------------------------------------------------
     * Read Residual Coded Data 
     * ----------------------------------------------------
     */
    inline std::list<Document> drain() {
        try {
            return _drain();
        } catch (ResourceExceptionTIMEOUT& ex) {
            INFO(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw IConnectorExceptionDEAD(__uri);
        }
    }
    /**
     * ----------------------------------------------------
     * Write Coded Data
     * ----------------------------------------------------
     */
    inline void write(const Document& data){
        try {
            _write(data);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw OConnectorExceptionDEAD(__uri);
        }
    }
protected:
    /**
     * ----------------------------------------------------
     * Variables
     * ----------------------------------------------------
     * machine state
     */
    size_t __state;
    /**
     * ----------------------------------------------------
     * IO interfaces
     * ----------------------------------------------------
     **
     * read
     */
    virtual Document _read() = 0;
    /**
     * drain 
     */
    virtual std::list<Document> _drain() {
         return {}; 
    }
    /**
     * write 
     */
    virtual void _write(const Document& container) = 0;
};
/**
 * ----------------------------------------------------------------------------
 * Definitions
 * ----------------------------------------------------------------------------
 */
typedef std::shared_ptr<SInputConnector>    IConnector;
typedef std::shared_ptr<SOutputConnector>   OConnector;
typedef std::shared_ptr<SInOutputConnector> IOConnector;
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SCONNECTOR_H */

