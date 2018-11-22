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
#include "SRoadMonitor.h"
#include "SResourceMonitor.h"
/**
 * ---------------------------------------------------------------------------------------------------------------------*
 * exceptions 
 * ---------------------------------------------------------------------------------------------------------------------
 **/
typedef class SFunctionException : public logic_error {
public:
    using logic_error::logic_error;
    /**
     * constructor
     */
    SFunctionException(const string& msg):logic_error(msg){
    }
} FunctionException;
/**
 * ---------------------------------------------------------------------------------------------------------------------*
 * function base 
 * ---------------------------------------------------------------------------------------------------------------------
 **/
class SFunction: public SLog {
public:
    /**
     * constructor
     */
    SFunction(string id, size_t energy = UINT32_MAX, uint8_t verbose = 0)
        : SLog(verbose), __id(id), __capacity(energy) {
        Recover();
    }
    /**
     * destructor
     */
    virtual ~SFunction() = default;
    /**
     * check if function is dead
     */
    inline bool Dead() {
        return (__energy == 0) ? true : (--__energy == 0);
    }
    /**
     * set energy
     */
    inline void SetEnergy(size_t energy) {
        __energy = energy;
    }
    /**
     * recover function
     */
    virtual void Recover() {
        refresh();
    }
protected:
    /**
     * function id
     */
    string __id;
    /**
     * energy capacity
     */
    size_t __capacity;
    /**
     * energy level
     */
    size_t __energy;
    /**
     * refresh energy
     */
    inline void refresh() {
        __energy = __capacity;
    }
    /*-------------------------------------------------------------------------------------------------------------*
     * logging
     *-------------------------------------------------------------------------------------------------------------*/
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
/*---------------------------------------------------------------------------------------------------------------------*
 * spread template 
 *---------------------------------------------------------------------------------------------------------------------*/
template<class K, class I, class D, class O>
class SFunctionSpread : public SFunction {
public:
    /**
     * 
     */
    using RoadMonitor = SRoadMonitor<K, I>;
    using Road    = SRoad<K, O>;
    using Data    = D;
    /**
     * constructor
     */
    using SFunction::SFunction;
    /**
     * process
     */
    void Process(RoadMonitor& in, Road& out) {
        try {
            /**--------------------------------------------------------------------------------------------*
             * waiting, read and process container
             *---------------------------------------------------------------------------------------------*/
            for (auto& it : in.Wait()) {
                try {
                    processData(it->second->Read(), out);
                } catch (ConnectorExceptionDEAD& ex) {
                    try {
                        for(auto& d: it->second->Drain()){ processData(move(d), out); }
                    } catch (...) {}
                    in.Repair(it);
                } catch (ConnectorExceptionTIMEOUT& ex){}
            }
            /**
             */
        } catch (MonitorException& ex) {
            /*---------------------------------------------------------------------------------------------*
             * drain and process container
             *---------------------------------------------------------------------------------------------*/
            for (auto s : in) {
                try {
                    for(auto& d: s.second->Drain()){ processData(move(d), out); }
                } catch (...) {}
            }
            /*---------------------------------------------------------------------------------------------*
             * send exception
             *---------------------------------------------------------------------------------------------*/
            throw;
        }
        refresh();
    }
    /**
     * drain
     */
    void Drain(Road& out) {
        processData(out);
    }
    
protected:
    /*-------------------------------------------------------------------------------------------------------------*
     * process Data
     *-------------------------------------------------------------------------------------------------------------*/
    virtual void processData(Data&& data, Road& out) = 0;
    
    virtual void processData(Road& out) = 0;
};
/*---------------------------------------------------------------------------------------------------------------------*
 * Spliter template 
 *---------------------------------------------------------------------------------------------------------------------*/
template<class IO, class IN, class OUT>
class SFunctionSpliter : public SFunction {
public:
    /**
     */
    SFunctionSpliter(uint32_t timeout, const uint32_t energy = 1, const uint8_t verbose = 0)
    : SFunction("spliter", energy, verbose), __timeout(timeout) {
    }
    /**------------------------------------------------------------------------------------------------------------*
     * process
     *-------------------------------------------------------------------------------------------------------------*/
    void Process(IO& io, IN& in, OUT& out) {
        try {
            for (auto& i : SResourceMonitor(__timeout, io, in).Wait()) {
                if (i == 0) {
                    processContainer(io, out);
                    continue;
                }
                if (i == 1) {
                    processContainer(in, io);
                    continue;
                }
            }
        } catch (MonitorException& ex) {
            // drain containers
            drainContainers(io, in, out);
            // resend exception
            throw;
        }
        refresh();
    }
protected:
    /*-------------------------------------------------------------------------------------------------------------*
     * process container
     *-------------------------------------------------------------------------------------------------------------*/
    template<class I, class O>
    void processContainer(I& in, O& out) {
        try {
            out->Write(in->Read());
        } catch (IConnectorExceptionDEAD& ex) {
            try {
                for (auto& d : in->Drain()) {out->Write(move(d));}
            } catch (...) {}
            in->Repair();
        } catch (OConnectorExceptionDEAD& ex) {
            out->Repair();
        } catch (ConnectorExceptionTIMEOUT& ex) {
        }
    }
    /*-------------------------------------------------------------------------------------------------------------*
     * drain container
     *-------------------------------------------------------------------------------------------------------------*/
    template<class I, class O>
    void drainContainers(IO& io, I& in, O& out) {
    
        try {
            for (auto& d : io->Drain()) { out->Write(move(d)); }
        } catch (IConnectorExceptionDEAD& ex) {
            io->Repair();
        } catch (OConnectorExceptionDEAD& ex) {
            out->Repair();
        }
        try {
            for (auto& d : in->Drain()) { io->Write(move(d)); }
        } catch (IConnectorExceptionDEAD& ex) {
            in->Repair();
        } catch (OConnectorExceptionDEAD& ex) {
            io->Repair();
        }
    }
private:
    /**
     * settings
     */
    chrono::milliseconds __timeout;
};
/**
 */
#endif /* SFUNCTION_H */

