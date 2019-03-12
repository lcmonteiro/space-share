/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SLog.h
 * Author: Luis Monteiro
 *
 * Created on January 23, 2017, 11:27 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SLOG_H
#define SLOG_H
/**
 * std
 */
#include <string>
/**
 * ----------------------------------------------------------------------------
 * Definitions
 * ----------------------------------------------------------------------------
 **/
//#define __LOG_SSTREAM__
/**
 * ----------------------------------------------------------------------------
 * flags
 * ----------------------------------------------------------------------------
 **/
#ifdef __LOG__
#define __LOG_DEBUG__           true
#define __LOG_INFO__            true
#define __LOG_WARNING__         true
#define __LOG_ERROR__           true
#define __LOG_CRITICAL__        true
#endif
/**
 * ----------------------------------------------------------------------------
 * macros
 * ----------------------------------------------------------------------------
 **/
#if __LOG_DEBUG__
#define DEBUG(__x__)    do{ std::ostringstream o; o << __x__; this->__DEBUG(o.str());    }while(0)
#else
#define DEBUG(__x__)
#endif
#if __LOG_INFO__
#define INFO(__x__)     do{ std::ostringstream o; o << __x__; this->__INFO(o.str());     }while(0)
#else
#define INFO(__x__)
#endif
#if __LOG_WARNING__
#define WARNING(__x__)  do{ std::ostringstream o; o << __x__; this->__WARNING(o.str());  }while(0)
#else
#define WARNING(__x__)
#endif
#if __LOG_ERROR__
#define ERROR(__x__)    do{ std::ostringstream o; o << __x__; this->__ERROR(o.str());    }while(0)
#else
#define ERROR(__x__)
#endif
#if __LOG_CRITICAL__
#define CRITITAL(__x__) do{ std::ostringstream o; o << __x__; this->__CRITITAL(o.str()); }while(0)
#else
#define CRITITAL(__x__)
#endif
/**
 * ----------------------------------------------------------------------------
 * log base
 * ----------------------------------------------------------------------------
 **/
class SLog {
public:
    /**
     * constructor
     */
    SLog(uint8_t verbose = 0) : __verbose(verbose) {
    }
    /**
     * destructor
     */
    virtual ~SLog() = default;
    /**
     * configure
     */
    inline void SetVerbose(uint8_t level) {
        __verbose = level;
    }
protected:
    /**
     * verbose level
     */
    uint8_t __verbose;
    /**
     * ----------------------------------------------------
     * logging level function
     * ----------------------------------------------------
     */
    void __DEBUG   (const std::string& id, const std::string& msg);
    void __INFO    (const std::string& id, const std::string& msg);
    void __WARNING (const std::string& id, const std::string& msg);
    void __ERROR   (const std::string& id, const std::string& msg);
    void __CRITITAL(const std::string& id, const std::string& msg);
};
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */ 
#endif /* SLOG_H */

