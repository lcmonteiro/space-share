/* 
 * File:   SLog.cpp
 * Author: luis monteiro
 *
 * Created on January 23, 2017, 11:27 PM
 */
#include "SLog.h"
/**
 */
#ifdef __ANDROID__
/**
 * ----------------------------------------------------------------------------
 * android
 * ----------------------------------------------------------------------------
 **/
#include <android/log.h>
/** 
 *---------------------------------------------------------
 * PRINT
 * --------------------------------------------------------
 */
#define PRINT(pattern,...) do {\
        __android_log_print(ANDROID_LOG_DEBUG, "SHARE", pattern,__VA_ARGS__);\
}while(0)
/** 
 *---------------------------------------------------------
 * LOG
 * --------------------------------------------------------
 */
void SLog::__DEBUG(const std::string& id, const std::string& msg) {
    if (__verbose >= 4) {
        __android_log_print(
            ANDROID_LOG_DEBUG, LOG_TAG, "[%s] [%s]", id.data(), msg.data()
        );
    }
}
void SLog::__INFO(const std::string& id, const std::string& msg) {
    if (__verbose >= 3) {
        __android_log_print(
            ANDROID_LOG_INFO, LOG_TAG, "[%s] [%s]", id.data(), msg.data()
        );
    }
}
void SLog::__WARNING(const std::string& id, const std::string& msg) {
    if (__verbose >= 2) {
        __android_log_print(
            ANDROID_LOG_WARN, LOG_TAG, "[%s] [%s]", id.data(), msg.data()
        );
    }
}
void SLog::__ERROR(const std::string& id, const std::string& msg) {
    if (__verbose >= 1) {
        __android_log_print(
            ANDROID_LOG_ERROR, LOG_TAG, "[%s] [%s]", id.data(), msg.data()
        );
    }
}
void SLog::__CRITITAL(const std::string& id, const std::string& msg) {
    if (__verbose >= 0) {
        __android_log_print(
            ANDROID_LOG_ERROR, LOG_TAG, "[%s] [%s]", id.data(), msg.data()
        );
    }
}
#else
/**
 * ----------------------------------------------------------------------------
 * linux base
 * ----------------------------------------------------------------------------
 **/
#include <ctime>
#include <iomanip>
#include <iostream>
/**
 * --------------------------------------------------------
 * helpers
 * --------------------------------------------------------
 */
#if __GNUC__ < 5
namespace std {
static inline std::string put_time(const std::tm* tmb, const char* fmt){
    return asctime(tmb);
}}
#endif
/** 
 *---------------------------------------------------------
 * Stream LOG
 * --------------------------------------------------------
 */
#ifdef __LOG_SSTREAM__
#include <sstream>
std::stringstream sstreamgout;
#define COUT std::sstreamgout
#define CERR std::sstreamgout
#else
#define COUT std::cout
#define CERR std::cerr
#endif
/** 
 *---------------------------------------------------------
 * LOG
 * --------------------------------------------------------
 */
void SLog::__DEBUG(const std::string& id, const std::string& msg) {
    if (__verbose >= 4) {
    auto t = time(nullptr);
    COUT << "[ " << std::put_time(localtime(&t), "%c %Z") << " ] "
        << "[  DEBUG  ] " 
        << "[ " << id << " ] " 
        << "[ " << msg << " ]" 
    << std::endl << std::flush;
    }
}
void SLog::__INFO(const std::string& id, const std::string& msg) {
    if (__verbose >= 3) {
    auto t = time(nullptr);
    COUT << "\e[32m"
        << "[ " << std::put_time(localtime(&t), "%c %Z") << " ] "
        << "[  INFO   ] " 
        << "[ " << id << " ] " 
        << "[ " << msg << " ]"
        << "\e[0m" 
    << std::endl << std::flush;
    }
}
void SLog::__WARNING(const std::string& id, const std::string& msg) {
    if (__verbose >= 2) {
    auto t = time(nullptr);
    COUT << "\e[33m"
        << "[ " << std::put_time(localtime(&t), "%c %Z") << " ] "
        << "[ WARNING ] " 
        << "[ " << id << " ] " 
        << "[ " << msg << " ]"
        << "\e[0m" 
    << std::endl << std::flush;
    }
}
void SLog::__ERROR(const std::string& id, const std::string& msg) {
    if (__verbose >= 1) {
    auto t = time(nullptr);
    CERR << "\e[31m"
        << "[ " << std::put_time(localtime(&t), "%c %Z") << " ] "
        << "[  ERROR  ] " 
        << "[ " << id << " ] " 
        << "[ " << msg << " ]"
        << "\e[0m" 
    << std::endl << std::flush;
    }
}
void SLog::__CRITITAL(const std::string& id, const std::string& msg) {
    if (__verbose >= 0) {
    auto t = time(nullptr);
    CERR << "\e[31m"
        << "[ " << std::put_time(localtime(&t), "%c %Z") << " ] "
        << "[ CRITICAL ] " 
        << "[ " << id << " ] " 
        << "[ " << msg << " ]"
        << "\e[0m" 
    << std::endl << std::flush;
    }
}
#endif
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 **/
