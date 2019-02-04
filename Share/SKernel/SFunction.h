/* 
 * File:   SFunction.h
 * Author: Luis Monteiro
 *
 * Created on January 20, 2017, 11:36 AM
 */
#ifndef SFUNCTION_H
#define SFUNCTION_H
/**
 * C++
 */
#include <ctime>
#include <string>
#include <list>
/**
 * Space Kernel
 */
#include "SLog.h"
#include "SEnergy.h"
#include "SRoadMonitor.h"
#include "SResourceMonitor.h"
/**
 * ------------------------------------------------------------------------------------
 * exceptions 
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
 * function base 
 * ------------------------------------------------------------------------------------
 **/
class SFunction: public SLog, public SEnergy<FunctionExceptionDEAD> {
public:
    /**
     * constructor
     */
    SFunction(string id, size_t energy = UINT32_MAX, uint8_t verbose = 0)
        : SLog(verbose), SEnergy(energy), __id(id) {
        Recover();
    }
    /**
     * destructor
     */
    virtual ~SFunction() = default;
    /**
     * recover function
     */
    virtual void Recover() {
        SEnergy::Restore();
    }
protected:
    /**
     * function id
     */
    string __id;
    /*---------------------------------------------------------------------------------
     * logging
     *-------------------------------------------------------------------------------**/
    inline void __DEBUG(const string& msg) {
        SLog::__DEBUG(__id, msg);
    }
    inline void __INFO(const string& msg) {
        SLog::__INFO(__id, msg);
    }
    inline void __WARNING(const string& msg) {
        SLog::__WARNING(__id, msg);
    }
    inline void __ERROR(const string& msg) {
        SLog::__ERROR(__id, msg);
    }
    inline void __CRITITAL(const string& msg) {
        SLog::__CRITITAL(__id, msg);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * spread template 
 *-------------------------------------------------------------------------------------------------
 **/
template<class K, class I, class D, class O>
class SFunctionSpread : public SFunction {
public:
    /**
     * type definitions
     */
    using IRoad = SRoadMonitor<K, I>;
    using ORoad = SRoad<K, O>;
    using Data  = D;
    /**
     * constructor
     */
    using SFunction::SFunction;
    /**--------------------------------------------------------------------------------
     * process 
     *-------------------------------------------------------------------------------**/
    void Process(IRoad& in, ORoad& out) {
        try {
            /**
             * waiting, read and process container
             **/
            for (auto& it : in.Wait()) {
                try {
                    processData(it->second->Read(), out);
                } catch (ConnectorExceptionDEAD& ex) {
                    try {
                        for(auto& d: it->second->Drain()){ processData(move(d), out); }
                    } catch (...) {}
                    in.Exception(it);
                } catch (ConnectorExceptionTIMEOUT& ex){}
            }
        } catch (MonitorException& ex) {
            /**
             * drain and process container
             **/
            for (auto s : in) {
                try {
                    for(auto& d: s.second->Drain()){ processData(move(d), out); }
                } catch (...) {}
            }
            /**
             * send exception
             **/
            throw;
        }
        SEnergy::Restore();
    }
    /**--------------------------------------------------------------------------------
     * drain
     *-------------------------------------------------------------------------------**/
    void Drain(IRoad& in, ORoad& out) {
        // drain road
        drainRoad(in, out);
        // process 
        processData(out);
    }
protected:
    /*---------------------------------------------------------------------------------
     * drain road 
     *-------------------------------------------------------------------------------**/
    inline void drainRoad(IRoad& in, ORoad& out) {
        for (auto it = in.begin(), end = in.end(); it != end;) {
            try {
                for (auto& d : it->second->Drain()) { processData(move(d), out); } ++it;
            } catch (IConnectorExceptionDEAD& ex) {
                in.Exception(it);
            }
        }
    }
    /**--------------------------------------------------------------------------------
     * process Data
     *-------------------------------------------------------------------------------**/
    virtual void processData(Data&& data, ORoad& out) {
        for (auto it = out.begin(), end = out.end(); it != end;) {
            try {
                it->second->Write(data); ++it;
            } catch (ConnectorExceptionDEAD& ex) {
                out.Exception(it);
            } catch (ConnectorExceptionTIMEOUT& ex) {
            }
        }
	}
    virtual void processData(ORoad& out) {
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
     * base constructor
     */
    using SFunction::SFunction;
    /**
     * default constructor
     */ 
    SFunctionSpliter(size_t energy = UINT32_MAX, uint8_t verbose = 0)
    : SFunction("Spliter", energy, verbose) {}
    /**--------------------------------------------------------------------------------
     * process
     *-------------------------------------------------------------------------------**/
    inline void Process(IORoad& io, IRoad& in, ORoad& out) {
        for (auto& i : SResourceMonitor<>(
            std::min(io.GetTimeout(), in.GetTimeout()), &io, &in
        ).Wait()) {
            if (i == 0) {
                processRoad(io, out);
                continue;
            }
            if (i == 1) {
                processRoad(in, io);
                continue;
            }
        }
        SEnergy::Restore();
    }
    inline void Process(IORoad& io, ORoad& out) {
        processRoad(io, out);
        SEnergy::Restore();
    }
    inline void Process(IRoad& in, IORoad& io) {
        processRoad(in, io);
        SEnergy::Restore();
    }
    /**--------------------------------------------------------------------------------
     * drain
     *-------------------------------------------------------------------------------**/
    inline void Drain(IORoad& io, IRoad& in, ORoad& out) {
        // drain roads
        drainRoad(io, out);
        drainRoad(in, io);
    }
protected:
    /*---------------------------------------------------------------------------------
     * process road
     *-------------------------------------------------------------------------------**/
    template<class I, class O>
    void processRoad(I& in, O& out) {
        for (auto& it : in.Wait()) {
            try {
                processData(it->second->Read(), out);
            } catch (ConnectorExceptionDEAD& ex) {
                try {
                    for(auto& d: it->second->Drain()){ processData(move(d), out); }
                } catch (...) {}
                in.Exception(it);
            } catch (ConnectorExceptionTIMEOUT& ex) {}
        }
    }
    /*---------------------------------------------------------------------------------
     * drain road 
     *-------------------------------------------------------------------------------**/
    template<class I, class O>
    void drainRoad(I& in, O& out) {
        for (auto it = in.begin(), end = in.end(); it != end;) {
            try {
                for (auto& d : it->second->Drain()) { processData(move(d), out); } ++it;
            } catch (IConnectorExceptionDEAD& ex) {
                in.Exception(it);
            }
        }
    }
    /*---------------------------------------------------------------------------------
     * process data 
     *-------------------------------------------------------------------------------**/
    template<class D, class O>
    inline void processData(D&& data, O& out) {
        for (auto it = out.begin(), end = out.end(); it != end;) {
            try {
                it->second->Write(data); ++it;
            } catch (ConnectorExceptionDEAD& ex) {
                out.Exception(it);
            } catch (ConnectorExceptionTIMEOUT& ex) {
            }
        }
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * end
 *-------------------------------------------------------------------------------------------------
 **/
#endif /* SFUNCTION_H */

