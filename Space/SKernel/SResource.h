/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SResource.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SRESOURCE_H
#define SRESOURCE_H
/**
 * std
 */
#include <system_error>
#include <memory>
/**
 * ------------------------------------------------------------------------------------------------
 * Exceptions
 * ------------------------------------------------------------------------------------------------
 * Base
 * ----------------------------------------------------------------------------
 */
typedef class SResourceException : public std::system_error {
public:
	using std::system_error::system_error;
	/**
	 * Constructor
	 */
	SResourceException()
	: SResourceException(std::make_error_code(
		std::errc::resource_unavailable_try_again)) {}
} ResourceException;
/**
 * ----------------------------------------------------------------------------
 * ExceptionABORT
 * ----------------------------------------------------------------------------
 */
typedef class SResourceExceptionABORT : public SResourceException {
public:
	using SResourceException::SResourceException;
	/**
	 * Constructor
	 */
	SResourceExceptionABORT(const std::string& msg)
	: SResourceException(
		std::make_error_code(std::errc::connection_aborted), msg){ }

	SResourceExceptionABORT()
	: SResourceException(
		std::make_error_code(std::errc::connection_aborted)){}
} ResourceExceptionABORT;

typedef class SIResourceExceptionABORT : public SResourceExceptionABORT {
public:
	using SResourceExceptionABORT::SResourceExceptionABORT;

} IResourceExceptionABORT;

typedef class SOResourceExceptionABORT : public SResourceExceptionABORT {
public:
	using SResourceExceptionABORT::SResourceExceptionABORT;

} OResourceExceptionABORT;
/**
 * ----------------------------------------------------------------------------
 * ExceptionTIMEOUT
 * ----------------------------------------------------------------------------
 */
typedef class SResourceExceptionTIMEOUT : public SResourceException {
public:
	using SResourceException::SResourceException;
	/**
	 * Constructor
	 */
	SResourceExceptionTIMEOUT(const std::string& msg)
	: SResourceException(
		std::make_error_code(std::errc::timed_out), msg){}
	SResourceExceptionTIMEOUT()
	: SResourceException(
		std::make_error_code(std::errc::timed_out)){}
} ResourceExceptionTIMEOUT;
/**
 * ------------------------------------------------------------------------------------------------
 * Resource Base
 * ------------------------------------------------------------------------------------------------
 */
typedef class SResource {
public:
	SResource& operator=(SResource&& t) = default;
	/**
	 * ------------------------------------------------------------------------
	 * handler for native system
	 * ------------------------------------------------------------------------
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
	 * --------------------------------
	 * definitions
	 * --------------------------------
	 */
	template<class H = SHandler>
	using pHandler = std::shared_ptr<H>;
	/**
	 * --------------------------------
	 * get handler
	 * --------------------------------
	 */
	template<class H = SHandler>
	inline pHandler<H> handler() const {
		if(__h) {
			return std::static_pointer_cast<H>(__h);
		}
		throw ResourceException();
	}
protected:
	/**
	 * ------------------------------------------------------------------------
	 * constructors and destructor
	 * ------------------------------------------------------------------------
	 * default constructor
	 */
	SResource()             = default;
	SResource(SResource&& ) = default;
	/**
	 * default destructor
	 */
	virtual ~SResource() = default; 
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
	 * --------------------------------
	 * pointer to handler
	 * --------------------------------
	 */
	pHandler<SHandler> __h;
} Resource;
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SRESOURCE_H */

