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
 * Definitions
 **/
//#define __LOG_SSTREAM__
/**
 * ------------------------------------------------------------------------------------------------
 * Flags
 * ------------------------------------------------------------------------------------------------
 **/
#ifdef __LOG__
#define __LOG_DEBUG__           true
#define __LOG_INFO__            true
#define __LOG_WARNING__         true
#define __LOG_ERROR__           true
#define __LOG_CRITICAL__        true
#endif
/**
 * ------------------------------------------------------------------------------------------------
 * macros
 * ------------------------------------------------------------------------------------------------
 **/
#if __LOG_DEBUG__
#define DEBUG(__x__)    do{ std::ostringstream o; o << __x__; this->_debug(o.str());    }while(0)
#else
#define DEBUG(__x__)
#endif
#if __LOG_INFO__
#define INFO(__x__)     do{ std::ostringstream o; o << __x__; this->_info(o.str());     }while(0)
#else
#define INFO(__x__)
#endif
#if __LOG_WARNING__
#define WARNING(__x__)  do{ std::ostringstream o; o << __x__; this->_warning(o.str());  }while(0)
#else
#define WARNING(__x__)
#endif
#if __LOG_ERROR__
#define ERROR(__x__)    do{ std::ostringstream o; o << __x__; this->_error(o.str());    }while(0)
#else
#define ERROR(__x__)
#endif
/**
 * ------------------------------------------------------------------------------------------------
 * Log Base
 * ------------------------------------------------------------------------------------------------
 **/
class SLog {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SLog(uint8_t verbose = 0) : __verbose(verbose) {
    }
    /**
     * ------------------------------------------------------------------------
     * Configure
     * ------------------------------------------------------------------------
     */
    inline void verbose(uint8_t level) {
        __verbose = level;
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     * verbose level
     */
    uint8_t __verbose;
    /**
     * ------------------------------------------------------------------------
     * Logging level function
     * ------------------------------------------------------------------------
     */
    void _debug   (const std::string& id, const std::string& msg);
    void _info    (const std::string& id, const std::string& msg);
    void _warning (const std::string& id, const std::string& msg);
    void _error   (const std::string& id, const std::string& msg);
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */ 
#endif /* SLOG_H */

