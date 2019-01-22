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
	inline std::shared_ptr<H> GetHandler() {
		return static_pointer_cast<H>(__h);
	}
	/**
	 * ----------------------------------------------------
	 * adpters 
	 * ----------------------------------------------------
	 */
	struct SDirect {
		template<typename T>
		static SResource::pHandler<> GetHandler(T obj) {
			return obj->GetHandler();
		}
	};
	struct SIndirect {
		template<typename T>
		static SResource::pHandler<> GetHandler(T obj) {
			return obj->GetResource().GetHandler();
		}
	};
protected:
	/**
	 * ----------------------------------------------------
	 * constructor
	 * ----------------------------------------------------
	 */
	SMonitor() = default;
private:
	/**
	 * pointer to handler
	 */
	std::shared_ptr<SHandler> __h;
};
/**
 * ------------------------------------------------------------------------------------------------
 * static monitor
 * ------------------------------------------------------------------------------------------------
 */
class SStaticMonitor: public SMonitor {
protected:
	/**
	 * constructor
	 */
	SStaticMonitor() = default;
	/**
	 * destructor
	 */
	virtual ~SStaticMonitor() = default; 
};
/**
 * ------------------------------------------------------------------------------------------------
 * dynamic monitor
 * ------------------------------------------------------------------------------------------------
 */
class SDynamicMonitor: public SMonitor, public SResource {
protected:
	/**
	 * constructor
	 */
	SDynamicMonitor() = default;
	/**
	 * destructor
	 */
	virtual ~SDynamicMonitor() = default; 
};
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* MONITOR_H */

