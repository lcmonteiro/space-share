/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SFunction.h
 * Author: Luis Monteiro
 *
 * Created on January 20, 2017, 11:36 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SFUNCTION_H
#define SFUNCTION_H
/**
 * std
 */
#include <ctime>
#include <string>
#include <list>
/**
 * space
 */
#include "SLog.h"
#include "SEnergy.h"
#include "SRoadMonitor.h"
#include "SResourceMonitor.h"
/**
 * ------------------------------------------------------------------------------------
 * Exceptions 
 * ------------------------------------------------------------------------------------
 **/
typedef class SFunctionException : public std::logic_error {
public:
    using std::logic_error::logic_error;
    /**
     * constructor
     */
    SFunctionException(const std::string& msg): std::logic_error(msg) {
    }
} FunctionException;
/**
 * ----------------------------------------------------------------------------
 * Dead
 * ----------------------------------------------------------------------------
 */
typedef class SFunctionExceptionDead : public SFunctionException {
public:
    using SFunctionException::SFunctionException;
    /**
     * constructor
     */
    SFunctionExceptionDead(const std::string& s) : SFunctionException(s) {
    }
} FunctionExceptionDEAD;
/**
 * ------------------------------------------------------------------------------------
 * Function base 
 * ------------------------------------------------------------------------------------
 **/
class SFunction: public SLog, public SEnergy<FunctionExceptionDEAD> {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SFunction(std::string id, size_t energy = UINT32_MAX, uint8_t verbose = 0)
    : SLog(verbose), SEnergy(energy), __id(id) {
        recover();
    }
    /**
     * ------------------------------------------------------------------------
     * Recover Function
     * ------------------------------------------------------------------------
     */
    virtual void recover() { SEnergy::restore(); }
protected:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     * function id
     */
    std::string __id;
    /**
     * ------------------------------------------------------------------------
     * Logging
     * ------------------------------------------------------------------------
     */
    inline void _debug  (const std::string& msg) { SLog::_debug  (__id, msg); }
    inline void _info   (const std::string& msg) { SLog::_info   (__id, msg); }
    inline void _warning(const std::string& msg) { SLog::_warning(__id, msg); }
    inline void _error  (const std::string& msg) { SLog::_error  (__id, msg); }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Spread template 
 * ------------------------------------------------------------------------------------------------
 **/
template<class K, class IN, class DOC, class OUT>
class SFunctionSpread : public SFunction {
public:
    /**
     * type definitions
     */
    using IRoad = SRoadMonitor<K, IN>;
    using ORoad = SRoad<K, OUT>;
    using Data  = DOC;
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     * base
     */
    using SFunction::SFunction;
    /**
     * default
     */ 
    SFunctionSpread(size_t energy = UINT32_MAX, uint8_t verbose = 0)
    : SFunction("Spread", energy, verbose) {}
    /**
     * ------------------------------------------------------------------------
     * Process 
     * ------------------------------------------------------------------------
     */
    void process(IRoad& in, ORoad& out) {
        try {
            /**
             * waiting, read and process container
             **/
            for (auto& it : in.wait()) {
                try {
                    _process_data(it->second->read(), out);
                } catch (ConnectorExceptionDEAD& ex) {
                    try {
                        for(auto& d: it->second->drain()) { 
                            _process_data(move(d), out);
                        }
                    } catch (...) {}
                    in.exception(it);
                } catch (ConnectorExceptionTIMEOUT& ex) {}
            }
        } catch (MonitorException& ex) {
            /**
             * drain and process container
             **/
            for (auto s : in) {
                try {
                    for(auto& d: s.second->drain()) { 
                        _process_data(std::move(d), out);
                    }
                } catch (...) {}
            }
            /**
             * send exception
             **/
            throw;
        }
        SEnergy::restore();
    }
    /**
     * ------------------------------------------------------------------------
     * Drain
     * ------------------------------------------------------------------------
     */
    void drain(IRoad& in, ORoad& out) {
        /**
         * drain
         */
        _drain_road(in, out);
        /**
         * process
         */
        _process_data(out);
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Drain Road 
     * ------------------------------------------------------------------------
     */
    inline void _drain_road(IRoad& in, ORoad& out) {
        for (auto it = in.begin(), end = in.end(); it != end;) {
            try {
                for (auto& d : it->second->drain()) { 
                    _process_data(std::move(d), out); 
                } ++it;
            } catch (IConnectorExceptionDEAD& ex) {
                in.exception(it);
            }
        }
    }
    /**
     * -------------------------------------------------------------------------
     * Process Data
     * -------------------------------------------------------------------------
     */
    virtual void _process_data(Data&& data, ORoad& out) {
        for (auto it = out.begin(), end = out.end(); it != end;) {
            try {
                it->second->write(data); ++it;
            } catch (ConnectorExceptionDEAD& ex) {
                out.exception(it);
            } catch (ConnectorExceptionTIMEOUT& ex) {
            }
        }
	}
    virtual void _process_data(ORoad& out) {
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Spliter template 
 *-------------------------------------------------------------------------------------------------
 **/
template<class K, class IO, class IN, class OUT>
class SFunctionSpliter : public SFunction {
public:
    /**
     * type definitions
     */
    using IORoad = SRoadMonitor<K, IO>;
    using IRoad  = SRoadMonitor<K, IN>;
    using ORoad  = SRoad<K, OUT>;
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     * base 
     */
    using SFunction::SFunction;
    /**
     * default
     */ 
    SFunctionSpliter(size_t energy = UINT32_MAX, uint8_t verbose = 0)
    : SFunction("Spliter", energy, verbose) {}
    /**
     * ------------------------------------------------------------------------
     * Process
     * ------------------------------------------------------------------------
     */
    inline void process(IORoad& io, IRoad& in, ORoad& out) {
        for (auto& i : SResourceMonitor<>(
            std::min(io.GetTimeout(), in.GetTimeout()), &io, &in
        ).wait()) {
            if (i == 0) {
                _process_road(io, out);
                continue;
            }
            if (i == 1) {
                _process_road(in, io);
                continue;
            }
        }
        SEnergy::restore();
    }
    inline void process(IORoad& io, ORoad& out) {
        _process_road(io, out);
        SEnergy::restore();
    }
    inline void process(IRoad& in, IORoad& io) {
        _process_road(in, io);
        SEnergy::restore();
    }
    /**
     * ------------------------------------------------------------------------
     * Drain
     * ------------------------------------------------------------------------
     */
    inline void drain(IORoad& io, IRoad& in, ORoad& out) {
        /**
         * drain roads
         */
        _drain_road(io, out);
        _drain_road(in, io);
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Process Road
     * ------------------------------------------------------------------------
     */
    template<class I, class O>
    void _process_road(I& in, O& out) {
        for (auto& it : in.wait()) {
            try {
                _process_data(it->second->read(), out);
            } catch (ConnectorExceptionDEAD& ex) {
                try {
                    for(auto& d: it->second->drain()) {
                        _process_data(std::move(d), out); 
                    }
                } catch (...) {}
                in.exception(it);
            } catch (ConnectorExceptionTIMEOUT& ex) {}
        }
    }
    /**
     * ------------------------------------------------------------------------
     * Drain Road 
     * ------------------------------------------------------------------------
     */
    template<class I, class O>
    void _drain_road(I& in, O& out) {
        for (auto it = in.begin(), end = in.end(); it != end;) {
            try {
                for (auto& d : it->second->drain()) { 
                    _process_data(std::move(d), out); 
                } ++it;
            } catch (IConnectorExceptionDEAD& ex) {
                in.exception(it);
            }
        }
    }
    /**
     * ------------------------------------------------------------------------
     * Process Data 
     * ------------------------------------------------------------------------
     */
    template<class D, class O>
    inline void _process_data(D&& data, O& out) {
        for (auto it = out.begin(), end = out.end(); it != end;) {
            try {
                it->second->write(data); ++it;
            } catch (ConnectorExceptionDEAD& ex) {
                out.exception(it);
            } catch (ConnectorExceptionTIMEOUT& ex) {
            }
        }
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 *-------------------------------------------------------------------------------------------------
 **/
#endif /* SFUNCTION_H */

