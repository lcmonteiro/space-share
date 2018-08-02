/* 
 * File:   SLog.h
 * Author: Luis Monteiro
 *
 * Created on January 23, 2017, 11:27 PM
 */
#ifndef SLOG_H
#define SLOG_H
/**
 * std
 */
#include <string>
#include <sstream>
/*---------------------------------------------------------------------------------------------------------------------*
 * flags
 *---------------------------------------------------------------------------------------------------------------------*/
#ifdef __LOG__
#define __LOG_DEBUG__           true
#define __LOG_INFO__            true
#define __LOG_WARNING__         true
#define __LOG_ERROR__           true
#define __LOG_CRITICAL__        true
#endif
/*---------------------------------------------------------------------------------------------------------------------*
 * macros
 *---------------------------------------------------------------------------------------------------------------------*/
#if __LOG_DEBUG__
#define DEBUG(__x__)	do{ ostringstream o; o << __x__; __DEBUG(o.str());	}while(0)
#else
#define DEBUG(__x__)
#endif
#if __LOG_INFO__
#define INFO(__x__)	do{ ostringstream o; o << __x__; __INFO(o.str());	}while(0)
#else
#define INFO(__x__)
#endif
#if __LOG_WARNING__
#define WARNING(__x__)	do{ ostringstream o; o << __x__; __WARNING(o.str());	}while(0)
#else
#define WARNING(__x__)
#endif
#if __LOG_ERROR__
#define ERROR(__x__)	do{ ostringstream o; o << __x__; __ERROR(o.str());	}while(0)
#else
#define ERROR(__x__)
#endif
#if __LOG_CRITICAL__
#define CRITITAL(__x__)	do{ ostringstream o; o << __x__; __CRITITAL(o.str());	}while(0)
#else
#define CRITITAL(__x__)
#endif
/*---------------------------------------------------------------------------------------------------------------------*
 * log base
 *---------------------------------------------------------------------------------------------------------------------*/
#ifdef __ANDROID__
#include "Sandroid/SAndroidLog.h"
#else
#include "SLinux/SLinuxLog.h"
#endif
#endif /* SLOG_H */

