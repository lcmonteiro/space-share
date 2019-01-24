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
#include "SContainer.h"
#include "SResource.h"
#include "SAddress.h"
#include "SEnergy.h"
#include "SRoad.h"
#include "SLog.h"
#include "STask.h"
/**
 */
using namespace std;
/**
 * -----------------------------------------------------------------------------------------------
 * exceptions
 * -----------------------------------------------------------------------------------------------
 */
typedef class SConnectorExection : public system_error {
public:
    /**
     * constructor
     */
    SConnectorExection(string uri, error_code ec) 
    : system_error(ec), __uri(uri) {
    }
    SConnectorExection(string uri, error_code ec, const string& what) 
    : system_error(ec, what), __uri(uri) {
    }
    /**
     * destructor
     */
    virtual ~SConnectorExection() = default;
    /**
     */
    inline string operator()(void) const {
        return __uri;
    }
private:
    string __uri;
} ConnectorExection;
/**
 */
typedef class SConnectorExceptionTIMEOUT : public SConnectorExection {
public:
    using SConnectorExection::SConnectorExection;
    /**
     * constructor
     */
    SConnectorExceptionTIMEOUT(string s) 
    : SConnectorExection(s, make_error_code(errc::no_message)) {
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
    SConnectorExceptionDead(string s) 
    : SConnectorExection(s, make_error_code(errc::no_message)) {
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
 * stream base
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
    typedef string  Key;
    /**
     * constructor
     */
    SConnector() = default;

    SConnector(string uri, size_t energy = 1) : SLog(), SEnergy(energy), __uri(uri) {
    }
    /**
     * destructor
     */
    virtual ~SConnector() = default;
    /**
     * get uri 
     */
    inline string Uri() {
        return __uri;
    }
    /**
     * set energy
     */
    inline void SetEnergy(size_t energy) {
        SEnergy::Set(energy);    
    }
    /**
     * get energy
     */
    inline size_t GetEnergy() {
        return SEnergy::Get();
    }
    /**
     * is worker is inactive 
     */
    inline bool Inactive() {
        return !__waiter.joinable();
    }
    /**
     * repair connector
     */
    inline void Repair() {
        // decay energy resource ------ 
        SEnergy::Decay();
        // enable build ---------------
        __waiter = STask([this]() {
            try {
                _Open();
            } catch (exception& ){} catch (...) {
                throw;
            }
        });
    }
    /**
     * break connector
     **/
    inline void Break() {
        // cancel decay ---------------
        SEnergy::Cancel();
        // enable waiter --------------
        __waiter = STask([this]() {
            try {
                _Close();
            } catch (exception& ){} catch (...) {
                throw;
            }
        });
    }
    /**
     * check good
     */
    inline bool Good() {
        return !Empty() && _Good();
    }
    /**
     * wait to be good
     */
    SConnector& Wait(chrono::milliseconds timeout);
protected:
    /**
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
    list<pair<size_t, size_t>> Shape(size_t len, size_t split);
    /**
     * ----------------------------------------------------
     * logging
     * ----------------------------------------------------
     * debug
     */
    inline void __DEBUG(const string& msg) {
        SLog::__DEBUG(__uri, msg);
    }
    /**
     * information
     */
    inline void __INFO(const string& msg) {
        SLog::__INFO(__uri, msg);
    }
    /**
     * warning
     */
    inline void __WARNING(const string& msg) {
        SLog::__WARNING(__uri, msg);
    }
    /**
     * error
     */
    inline void __ERROR(const string& msg) {
        SLog::__ERROR(__uri, msg);
    }
    /**
     * critical error
     */
    inline void __CRITITAL(const string& msg) {
        SLog::__CRITITAL(__uri, msg);
    }
};
/**
 * definitions
 */
typedef shared_ptr<SConnector> Connector;
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
    inline Container Read() {
        try {
            return _Read();
        } catch (ResourceExceptionABORT& ex) {
            throw IConnectorExceptionDEAD(__uri);
        } catch (ResourceExceptionTIMEOUT& ex) {
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ContainerException& ex){
            ERROR(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        }
    }
    /**
     * read residual data 
     */
    inline list<Container> Drain() {
        try {
            return _Drain();
        } catch (ResourceExceptionABORT& ex) {
            throw IConnectorExceptionDEAD(__uri);
        } catch (ResourceExceptionTIMEOUT& ex) {
            throw IConnectorExceptionTIMEOUT(__uri);
        }
    }

protected:
    /**
     * ----------------------------------------------------
     * IO interfaces
     * ----------------------------------------------------
     * read
     */
    virtual Container _Read() = 0;
    /**
     * drain 
     **/
    virtual list<Container> _Drain() { return {_Read()}; }
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
    inline void Write(const Container& data){
        try {
            _Write(data);
        } catch (ResourceExceptionABORT& ex) {
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
    virtual void _Write(const Container& container) = 0;
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
    inline Container Read() {
        try {
            return _Read();
        } catch (ResourceExceptionABORT& ex) {
            throw IConnectorExceptionDEAD(__uri);
        } catch (ResourceExceptionTIMEOUT& ex) {
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ContainerException& ex){
            ERROR(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        }
    }
    /**
     * read residual data 
     */
    inline list<Container> Drain() {
        try {
            return _Drain();
        } catch (ResourceExceptionABORT& ex) {
            throw IConnectorExceptionDEAD(__uri);
        } catch (ResourceExceptionTIMEOUT& ex) {
            throw IConnectorExceptionTIMEOUT(__uri);
        }
    }
    /**
     * write data
     */
    inline void Write(const Container& data) {
        try {
            _Write(data);
        } catch (ResourceExceptionABORT& ex) {
            throw OConnectorExceptionDEAD(__uri);
        }
    }
protected:
    /**
     * ----------------------------------------------------
     * IO interfaces
     * ----------------------------------------------------
     * read
     */
    virtual Container _Read() = 0;
    /**
     * drain  
     */
    virtual list<Container> _Drain() { return {_Read()}; }
    /**
     * write 
     */
    virtual void _Write(const Container& container) = 0;
};
/**
 * definitions
 */
typedef shared_ptr<SInputConnector>    IConnector;
typedef shared_ptr<SOutputConnector>   OConnector;
typedef shared_ptr<SInOutputConnector> IOConnector;
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
        } catch (ResourceExceptionABORT& ex) {
            throw IConnectorExceptionDEAD(__uri);
        } catch (ResourceExceptionTIMEOUT& ex) {
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ContainerException& ex){
            ERROR(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        }
    }
    /**
     * read residual coded data 
     */
    inline list<Document> Drain() {
        try {
            return _Drain();
        } catch (ResourceExceptionABORT& ex) {
            throw IConnectorExceptionDEAD(__uri);
        } catch (ResourceExceptionTIMEOUT& ex) {
            throw IConnectorExceptionTIMEOUT(__uri);
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
     * read
     */
    virtual Document _Read() = 0;
    /**
     * drain
     */
    virtual list<Document> _Drain() { return {_Read()}; }
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
        } catch (ResourceExceptionABORT& ex) {
            throw IConnectorExceptionDEAD(__uri);
        } catch (ResourceExceptionTIMEOUT& ex) {
            throw IConnectorExceptionTIMEOUT(__uri);
        } catch (ContainerException& ex){
            ERROR(ex.what());
            throw IConnectorExceptionTIMEOUT(__uri);
        }
    }
    /**
     * read residual coded data 
     */
    inline list<Document> Drain() {
        try {
            return _Drain();
        } catch (ResourceExceptionABORT& ex) {
            throw IConnectorExceptionDEAD(__uri);
        } catch (ResourceExceptionTIMEOUT& ex) {
            throw IConnectorExceptionTIMEOUT(__uri);
        }
    }
    /**
     * write coded data
     */
    inline void Write(const Document& data){
        try {
            _Write(data);
        } catch (ResourceExceptionABORT& ex) {
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
     * read
     */
    virtual Document _Read() = 0;
    /**
     * drain 
     */
    virtual list<Document> _Drain() { return {_Read()}; }
    /**
     * write 
     */
    virtual void _Write(const Document& container) = 0;
};
/**
 * definitions
 */
typedef shared_ptr<SInputConnector>    IConnector;
typedef shared_ptr<SOutputConnector>   OConnector;
typedef shared_ptr<SInOutputConnector> IOConnector;
}
/**
 */
#endif /* SCONNECTOR_H */

