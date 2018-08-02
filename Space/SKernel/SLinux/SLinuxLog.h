/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SLog.h
 * Author: root
 *
 * Created on January 23, 2017, 11:27 PM
 */
#ifndef SLOGSTD_H
#define SLOGSTD_H
/**
 * std
 */
#include <ctime>
#include <iomanip>
#include <iostream>
#if __GNUC__ < 5
#include <ctime>
static inline std::string put_time(const std::tm* tmb, const char* fmt){
        return asctime(tmb);
}
#endif
/*---------------------------------------------------------------------------------------------------------------------*
 * configuration
 *---------------------------------------------------------------------------------------------------------------------*/
//#define __LOG_SSTREAM__
/**/
#ifdef __LOG_SSTREAM__
#include <sstream>
extern std::stringstream sstreamgout;
#define COUT sstreamgout
#define CERR sstreamgout
#else
#define COUT cout
#define CERR cerr
#endif
/*---------------------------------------------------------------------------------------------------------------------*
 * log base
 *---------------------------------------------------------------------------------------------------------------------*/
using namespace std;
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
	 * logging
	 */
	inline void __DEBUG(const string& id, const string& msg) {
		if (__verbose >= 4) {
			auto t = time(nullptr);
			COUT << "[ " << put_time(localtime(&t), "%c %Z") << " ] "
				<< "[  DEBUG  ] " 
				<< "[ " << id << " ] " 
				<< "[ " << msg << " ]" 
			<< endl << flush;
		}
	}
	inline void __INFO(const string& id, const string& msg) {
		if (__verbose >= 3) {
			auto t = time(nullptr);
			COUT << "\e[32m"
				<< "[ " << put_time(localtime(&t), "%c %Z") << " ] "
				<< "[  INFO   ] " 
				<< "[ " << id << " ] " 
				<< "[ " << msg << " ]"
				<< "\e[0m" 
			<< endl << flush;
		}
	}
	inline void __WARNING(const string& id, const string& msg) {
		if (__verbose >= 2) {
			auto t = time(nullptr);
			COUT << "\e[33m"
				<< "[ " << put_time(localtime(&t), "%c %Z") << " ] "
				<< "[ WARNING ] " 
				<< "[ " << id << " ] " 
				<< "[ " << msg << " ]"
				<< "\e[0m" 
			<< endl << flush;
		}
	}
	inline void __ERROR(const string& id, const string& msg) {
		if (__verbose >= 1) {
			auto t = time(nullptr);
			CERR << "\e[31m"
				<< "[ " << put_time(localtime(&t), "%c %Z") << " ] "
				<< "[  ERROR  ] " 
				<< "[ " << id << " ] " 
				<< "[ " << msg << " ]"
				<< "\e[0m" 
			<< endl << flush;
		}
	}
	inline void __CRITITAL(const string& id, const string& msg) {
		if (__verbose >= 0) {
			auto t = time(nullptr);
			CERR << "\e[31m"
				<< "[ " << put_time(localtime(&t), "%c %Z") << " ] "
				<< "[ CRITICAL ] " 
				<< "[ " << id << " ] " 
				<< "[ " << msg << " ]"
				<< "\e[0m" 
			<< endl << flush;
		}
	}
};
#endif /* SLOGSTD_H */

