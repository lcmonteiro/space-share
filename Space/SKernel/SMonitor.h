/* 
 * Stream: Monitor.h
 * Author: Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef MONITOR_H
#define MONITOR_H
/**
 * std
 */
#include <system_error>
#include <memory>
/**
 */
using namespace std;
/**
 * ----------------------------------------------------------------------------
 * monitor base
 * ----------------------------------------------------------------------------
 */
class SMonitor {
public:
	/**
	 * ----------------------------------------------------
	 * handler for native system
	 * ----------------------------------------------------
	 */
	class SHandler {
	protected:
		/**
		 * constructor
		 */
		SHandler() = default;
		/**
		 * destructor
		 */
		virtual ~SHandler() = default;
	};
	/**
	 * get handler
	 */
	template<class H = SHandler>
	inline shared_ptr<H> Handler() {
		return static_pointer_cast<H>(__h);
	}
protected:
	/**
	 * constructor
	 */
	SMonitor() = default;
	/**
	 * destructor
	 */
	virtual ~SMonitor() = default; 
private:
	/**
	 * pointer to handler
	 */
	shared_ptr<SHandler> __h;
};
/**
 * ------------------------------------------------------------------------------------------------
 * monitor exceptions
 * ------------------------------------------------------------------------------------------------
 */
typedef class SMonitorException : public system_error {
public:
	using system_error::system_error;
	/**
	 * constructor
	 */
	SMonitorException(error_code ec) : system_error(ec) {
	}
} MonitorException;

typedef class SMonitorExceptionTIMEOUT : public SMonitorException {
public:
	using SMonitorException::SMonitorException;
	/**
	 * constructor
	 */
	SMonitorExceptionTIMEOUT(const string& msg) : SMonitorException(make_error_code(errc::stream_timeout), msg) {
	}
	SMonitorExceptionTIMEOUT() : SMonitorException(make_error_code(errc::stream_timeout)) {
	}
} MonitorExceptionTIMEOUT;

typedef class SMonitorExceptionCANCEL : public SMonitorException {
public:
	using SMonitorException::SMonitorException;
	/**
	 * constructor
	 */
	SMonitorExceptionCANCEL(const string& msg) : SMonitorException(make_error_code(errc::no_such_process), msg) {
	}
	SMonitorExceptionCANCEL() : SMonitorException(make_error_code(errc::no_such_process)) {
	}
} MonitorExceptionCANCEL;
/**
 */
#endif /* MONITOR_H */

