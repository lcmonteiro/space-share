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
#include <chrono>
#include <memory>
#include <vector>
#include <list>
/**
 * space
 */
#include "SResource.h"
/**
 * ------------------------------------------------------------------------------------------------
 * monitor exceptions
 * ------------------------------------------------------------------------------------------------
 */
typedef class SMonitorException : public std::system_error {
public:
	using std::system_error::system_error;
	/**
	 * constructor
	 */
	SMonitorException(std::error_code ec) : system_error(ec) {
	}
} MonitorException;

typedef class SMonitorExceptionTIMEOUT : public SMonitorException {
public:
	using SMonitorException::SMonitorException;
	/**
	 * constructor
	 */
	SMonitorExceptionTIMEOUT(const std::string& msg) 
	: SMonitorException(std::make_error_code(std::errc::stream_timeout), msg) {
	}
	SMonitorExceptionTIMEOUT() 
	: SMonitorException(std::make_error_code(std::errc::stream_timeout)) {
	}
} MonitorExceptionTIMEOUT;

typedef class SMonitorExceptionCANCEL : public SMonitorException {
public:
	using SMonitorException::SMonitorException;
	/**
	 * constructor
	 */
	SMonitorExceptionCANCEL(const std::string& msg) 
	: SMonitorException(make_error_code(std::errc::no_such_process), msg) {
	}
	SMonitorExceptionCANCEL() 
	: SMonitorException(make_error_code(std::errc::no_such_process)) {
	}
} MonitorExceptionCANCEL;
/**
 * ------------------------------------------------------------------------------------------------
 * monitor
 * ------------------------------------------------------------------------------------------------
 */
class SMonitor {
public:
	using Handler  = SResource::pHandler<>;
    using Handlers = std::vector<Handler>;
	using Time     = std::chrono::milliseconds; 
	/**
	 * ------------------------------------------------------------------------
	 * adpters 
	 * ------------------------------------------------------------------------
	 */
	struct SDirect {
		template<typename T>
		static Handler GetHandler(T obj) {
			return obj->GetHandler();
		}
	};
	struct SIndirect {
		template<typename T>
		static Handler GetHandler(T obj) {
			return obj->GetResource().GetHandler();
		}
	};
	/**
	 * ------------------------------------------------------------------------
	 * handler for native system
	 * ------------------------------------------------------------------------
	 * handler
	 */
	class SHandler {
	protected:
		SHandler() 			= default;
		virtual ~SHandler() = default;
	};
	/**
	 * handler type 
	 */
	template<class H = SHandler>
	using pHandler = std::shared_ptr<H>;
	/**
	 * handler pointer
	 */
	template<class H = SHandler>
	inline pHandler<H> GetHandler() {
		return std::static_pointer_cast<H>(__h);
	}
	/**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     * size 
     */
    size_t Size();
protected:
	/**
	 * ------------------------------------------------------------------------
	 * constructor
	 * ------------------------------------------------------------------------
	 */
	SMonitor() = default;
private:
	/**
	 * ------------------------------------------------------------------------
	 * variables
	 * ------------------------------------------------------------------------
	 **
	 * pointer to handler
	 */
	pHandler<SHandler> __h;
};
/**
 * ------------------------------------------------------------------------------------------------
 * static monitor
 * ------------------------------------------------------------------------------------------------
 */
class SStaticMonitor: public SMonitor {
protected:
	/**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------ 
     */
    SStaticMonitor(SStaticMonitor &&)            = default;
    SStaticMonitor& operator=(SStaticMonitor &&) = default;
	/**
	 * ------------------------------------------------------------------------
	 * constructor
	 * ------------------------------------------------------------------------
	 */
	SStaticMonitor();
	/**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     * insert 
     */
    size_t Insert(Handler h);
    /**
     * wait
     */
    std::list<size_t> Wait(const Time& timeout);
};
/**
 * ------------------------------------------------------------------------------------------------
 * dynamic monitor
 * ------------------------------------------------------------------------------------------------
 */
class SDynamicMonitor: public SMonitor, public SResource {
protected:
	/**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------ 
     */
    SDynamicMonitor(SDynamicMonitor &&)            = default;
    SDynamicMonitor& operator=(SDynamicMonitor &&) = default;
	/**
	 * ------------------------------------------------------------------------
	 * constructor
	 * ------------------------------------------------------------------------
	 */
	SDynamicMonitor();
	/**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     * insert 
     */
    size_t Insert(Handler h);
    /**
     * wait
     */
    std::list<size_t> Wait(const Time& timeout);
};
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* MONITOR_H */

