/* 
 * Connector: Connector.h
 * Author: Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
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
 * exceptions
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
     * destructor
     */
    virtual ~SConnectorExection() = default;
    /**
     */
    inline std::string operator()(void) const {
        return __uri;
    }
private:
    std::string __uri;
} ConnectorExection;
/**
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
 * connenctor base
 * ------------------------------------------------------------------------------------------------
 **/
class SConnector: public SLog, protected SEnergy<ConnectorExceptionDEAD> {
    /**
     * type definitions
     */
    typedef STask Task;
public:
    /**
     * connector default
     */
    typedef std::string  Key;
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     */
    SConnector()          = default;
    virtual ~SConnector() = default;
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    SConnector(std::string uri, size_t energy = 1) 
    : SLog(), SEnergy(energy), __uri(uri) {
    }
    /**
     * ------------------------------------------------------------------------
     * interface
     * ------------------------------------------------------------------------
     * get uri 
     * ----------------------------------------------------
     */
    inline const SAddress& GetURI() const {
        return __uri;
    }
    /**
     * ----------------------------------------------------
     * set energy
     * ----------------------------------------------------
     */
    inline void SetEnergy(size_t energy) {
        SEnergy::Set(energy);    
    }
    /**
     * ----------------------------------------------------
     * get energy
     * ----------------------------------------------------
     */
    inline size_t GetEnergy() {
        return SEnergy::Get();
    }
    /**
     * ----------------------------------------------------
     * is worker is inactive 
     * ----------------------------------------------------
     */
    inline bool Inactive() {
        return !__waiter.joinable();
    }
    /**
     * ----------------------------------------------------
     * repair connector
     * ----------------------------------------------------
     */
    inline void Repair() {
        // decay energy resource ------ 
        SEnergy::Decay();
        // enable build ---------------
        __waiter = STask([this]() {
            try {
                _Open();
            } catch (std::exception& ){} catch (...) {
                throw;
            }
        });
    }
    /**
     * ----------------------------------------------------
     * break connector
     * ----------------------------------------------------
     **/
    inline void Break() {
        // cancel decay ---------------
        SEnergy::Cancel();
        // enable waiter --------------
        __waiter = STask([this]() {
            try {
                _Close();
            } catch (std::exception& ){} catch (...) {
                throw;
            }
        });
    }
    /**
     * ----------------------------------------------------
     * check status
     * ----------------------------------------------------
     */
    inline bool Good() {
        return !empty() && _Good();
    }
    /**
     * ----------------------------------------------------
     * wait (timeout) to be good
     * ----------------------------------------------------
     */
    SConnector& Wait(std::chrono::milliseconds timeout);
protected:
    /**
     * ----------------------------------------------------
     * variables
     * ----------------------------------------------------
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
     * ----------------------------------------------------
     * interfaces
     * ----------------------------------------------------
     * close
     **/
    virtual void _Close() = 0;
    /**
     * open
     */
    virtual void _Open() = 0;
    /**
     * good
     */
    virtual bool _Good() = 0;
    /**
     * ----------------------------------------------------
     * utilities
     * ----------------------------------------------------
     * reshape 
     */
    std::list<std::pair<size_t, size_t>> Shape(size_t len, size_t split);
    /**
     * ------------------------------------------------------------------------
     * logging
     * ------------------------------------------------------------------------
     * debug
     * ----------------------------------------------------
     */
    inline void __DEBUG(const std::string& msg) {
        SLog::__DEBUG(__uri, msg);
    }
    /**
     * ----------------------------------------------------
     * information
     * ----------------------------------------------------
     */
    inline void __INFO(const std::string& msg) {
        SLog::__INFO(__uri, msg);
    }
    /**
     * ----------------------------------------------------
     * warning
     * ----------------------------------------------------
     */
    inline void __WARNING(const std::string& msg) {
        SLog::__WARNING(__uri, msg);
    }
    /**
     * ----------------------------------------------------
     * error
     * ----------------------------------------------------
     */
    inline void __ERROR(const std::string& msg) {
        SLog::__ERROR(__uri, msg);
    }
    /**
     * ----------------------------------------------------
     * critical error
     * ----------------------------------------------------
     */
    inline void __CRITICAL(const std::string& msg) {
        SLog::__CRITICAL(__uri, msg);
    }
};
/**
 * ----------------------------------------------------------------------------
 * definitions
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
     * constructor
     */
    SInputConnector() = default;
    /**
     * destructor
     */
    virtual ~SInputConnector() = default;
    /**
     */
    virtual Resource& GetResource() = 0;
    /**
     * read data
     */
    inline Document Read() {
        try {
            return _Read();
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
     * read residual data 
     */
    inline std::list<Document> Drain() {
        try {
            return _Drain();
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
    virtual Document _Read() = 0;
    /**
     * drain 
     **/
    virtual std::list<Document> _Drain() { return {}; }
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
     * constructor
     */
    SOutputConnector() = default;
    /**
     * destructor
     */
    virtual ~SOutputConnector() = default;
    /**
     * write data
     */
    inline void Write(const Document& data){
        try {
            _Write(data);
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
    virtual void _Write(const Document& container) = 0;
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
     * constructor
     */
    SInOutputConnector() = default;
    /**
     * destructor
     */
    virtual ~SInOutputConnector() = default;
    /**
     * get resource
     */
    virtual Resource& GetResource() = 0;
    /**
     * read data
     */
    inline Document Read() {
        try {
            return _Read();
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
     * read residual data 
     */
    inline std::list<Document> Drain() {
        try {
            return _Drain();
        } catch (ResourceExceptionTIMEOUT& ex) {
            INFO(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw IConnectorExceptionDEAD(__uri);
        }
    }
    /**
     * write data
     */
    inline void Write(const Document& data) {
        try {
            _Write(data);
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
    virtual Document _Read() = 0;
    /**
     * drain  
     */
    virtual std::list<Document> _Drain() { return {}; }
    /**
     * write 
     */
    virtual void _Write(const Document& container) = 0;
};
/**
 * ----------------------------------------------------------------------------
 * definitions
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
     * constructor
     */
    SInputConnector() = default;
    /**
     * destructor
     */
    virtual ~SInputConnector() = default;
    /**
     * get resource
     */
    virtual Resource& GetResource() = 0;
    /**
     * read coded data
     */
    inline Document Read() {
        try {
            return _Read();
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
     * read residual coded data 
     */
    inline std::list<Document> Drain() {
        try {
            return _Drain();
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
    virtual Document _Read() = 0;
    /**
     * drain
     */
    virtual std::list<Document> _Drain() { return {}; }
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
     * constructor
     */
    SOutputConnector() = default;
    /**
     * destructor
     */
    virtual ~SOutputConnector() = default;
    /**
     * write coded data
     */
    inline void Write(const Document& data){
        try {
            _Write(data);
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
    virtual void _Write(const Document& container) = 0;
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
     * constructor
     */
    SInOutputConnector() = default;
    /**
     * destructor
     */
    virtual ~SInOutputConnector() = default;    
    /**
     */
    virtual Resource& GetResource() = 0;
    /**
     * read coded data
     */
    inline Document Read(){
        try {
            return _Read();
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
     * read residual coded data 
     */
    inline std::list<Document> Drain() {
        try {
            return _Drain();
        } catch (ResourceExceptionTIMEOUT& ex) {
            INFO(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw IConnectorExceptionDEAD(__uri);
        }
    }
    /**
     * write coded data
     */
    inline void Write(const Document& data){
        try {
            _Write(data);
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
            throw OConnectorExceptionDEAD(__uri);
        }
    }
protected:
    /**
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
    virtual Document _Read() = 0;
    /**
     * drain 
     */
    virtual std::list<Document> _Drain() { return {}; }
    /**
     * write 
     */
    virtual void _Write(const Document& container) = 0;
};
/**
 * ----------------------------------------------------------------------------
 * definitions
 * ----------------------------------------------------------------------------
 */
typedef std::shared_ptr<SInputConnector>    IConnector;
typedef std::shared_ptr<SOutputConnector>   OConnector;
typedef std::shared_ptr<SInOutputConnector> IOConnector;
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SCONNECTOR_H */

