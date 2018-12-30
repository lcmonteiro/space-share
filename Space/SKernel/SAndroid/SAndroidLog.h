/* 
 * File:   SLogAndroid.h
 * Author: root
 *
 * Created on January 23, 2017, 11:27 PM
 */
#ifndef SLOGANDROID_H
#define SLOGANDROID_H
/**
 * std
 */
#include <android/log.h>
/*------------------------------------------------------------------------------------------------*
 * PRINT
 *------------------------------------------------------------------------------------------------*/
#define PRINT(pattern,...) do {\
        __android_log_print(ANDROID_LOG_DEBUG, "SHARE", pattern,__VA_ARGS__);\
}while(0)
/*------------------------------------------------------------------------------------------------*
 * log base
 *------------------------------------------------------------------------------------------------*/
using namespace std;
class SLog {
        const char* LOG_TAG = "Share";
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
                        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "[%s] [%s]", id.data(), msg.data());
		}
	}
	inline void __INFO(const string& id, const string& msg) {
		if (__verbose >= 3) {
			__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "[%s] [%s]", id.data(), msg.data());
		}
	}
	inline void __WARNING(const string& id, const string& msg) {
		if (__verbose >= 2) {
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "[%s] [%s]", id.data(), msg.data());
		}
	}
	inline void __ERROR(const string& id, const string& msg) {
		if (__verbose >= 1) {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s] [%s]", id.data(), msg.data());
		}
	}
	inline void __CRITITAL(const string& id, const string& msg) {
		if (__verbose >= 0) {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s] [%s]", id.data(), msg.data());
		}
	}
};
#endif /* SLOGANDROID_H */

