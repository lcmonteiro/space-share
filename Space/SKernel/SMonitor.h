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
	inline pHandler<H> GetHandler() const {
		return std::static_pointer_cast<H>(__h);
	}
	/**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     * size 
     */
    virtual size_t size() = 0;
	/**
	 * insert 
     */
    virtual size_t Insert(Handler h) = 0;
    /**
     * wait
     */
    virtual std::list<size_t> Wait(const Time& timeout) = 0;
protected:
	/**
	 * ------------------------------------------------------------------------
	 * constructor
	 * ------------------------------------------------------------------------
	 */
	SMonitor() = default;
	/***
	 * ------------------------------------------------------------------------
	 * methods
	 * ------------------------------------------------------------------------
	 * set phandler
	 */
	template<class H = SHandler>
	void SetHandler(pHandler<H> h) {
		__h = std::static_pointer_cast<SHandler>(h);	
	}
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

namespace Monitor {
/**
 * ------------------------------------------------------------------------------------------------
 * base - static monitor
 * ------------------------------------------------------------------------------------------------
 */
class SStatic: public SMonitor {
protected:
	/**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------ 
     */
    SStatic(SStatic &&)            = default;
    SStatic& operator=(SStatic &&) = default;
	/**
	 * ------------------------------------------------------------------------
	 * constructor
	 * ------------------------------------------------------------------------
	 */
	SStatic();
	/**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     * size 
     */
    size_t size() override;
	/**
	 * insert 
     */
    size_t Insert(Handler h) override;
    /**
     * wait
     */
    std::list<size_t> Wait(const Time& timeout) override;
};
/**
 * ------------------------------------------------------------------------------------------------
 * base - dynamic monitor
 * ------------------------------------------------------------------------------------------------
 */
class SDynamic: public SMonitor, public SResource {
protected:
	/**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------ 
     */
    SDynamic(SDynamic &&)            = default;
    SDynamic& operator=(SDynamic &&) = default;
	/**
	 * ------------------------------------------------------------------------
	 * constructor
	 * ------------------------------------------------------------------------
	 */
	SDynamic();
	/**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     * size 
     */
    size_t size() override;
	/**
	 * insert 
     */
    size_t Insert(Handler h) override;
    /**
     * wait
     */
    std::list<size_t> Wait(const Time& timeout) override;
};
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
}
#endif /* MONITOR_H */

