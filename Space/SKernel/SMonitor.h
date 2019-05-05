/**
 * ------------------------------------------------------------------------------------------------ 
 * Stream: Monitor.h
 * Author: Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * ------------------------------------------------------------------------------------------------
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
 * Monitor
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
	inline pHandler<H> handler() const {
		return std::static_pointer_cast<H>(__h);
	}
	/**
     * ------------------------------------------------------------------------
     * Interfaces
     * ------------------------------------------------------------------------
     * size 
     */
    virtual size_t size() = 0;
	/**
	 * insert 
     */
    virtual size_t insert(Handler h) = 0;
    /**
     * wait
     */
    virtual std::list<size_t> wait(const Time& timeout) = 0;
protected:
	/**
	 * ------------------------------------------------------------------------
	 * Constructor
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
	void handler(pHandler<H> h) {
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
     * Defaults
     * ------------------------------------------------------------------------ 
     */
    SStatic(SStatic &&)            = default;
    SStatic& operator=(SStatic &&) = default;
	/**
	 * ------------------------------------------------------------------------
	 * Constructor
	 * ------------------------------------------------------------------------
	 */
	SStatic();
	/**
     * ------------------------------------------------------------------------
     * Interfaces
     * ------------------------------------------------------------------------
     * size 
     */
    size_t size() override;
	/**
	 * insert 
     */
    size_t insert(Handler h) override;
    /**
     * wait
     */
    std::list<size_t> wait(const Time& timeout) override;
};
/**
 * ------------------------------------------------------------------------------------------------
 * Base - Dynamic monitor
 * ------------------------------------------------------------------------------------------------
 */
class SDynamic: public SMonitor, public SResource {
protected:
	/**
     * ------------------------------------------------------------------------
     * Defaults
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
     * Interfaces
     * ------------------------------------------------------------------------
     * size 
     */
    size_t size() override;
	/**
	 * insert 
     */
    size_t insert(Handler h) override;
    /**
     * wait
     */
    std::list<size_t> wait(const Time& timeout) override;
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
}
#endif /* MONITOR_H */

