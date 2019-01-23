/* 
 * Container:   SResource.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
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
 */
typedef class SResourceException : public std::system_error {
public:
	using std::system_error::system_error;
	/**
	 * constructor
	 */
	SResourceException()
	: SResourceException(std::make_error_code(std::errc::resource_unavailable_try_again)){
	}

} ResourceException;
/**
 * ExceptionABORT
 */
typedef class SResourceExceptionABORT : public SResourceException {
public:
	using SResourceException::SResourceException;
	/**
	 * constructor
	 */
	SResourceExceptionABORT(const std::string& msg)
	: SResourceException(std::make_error_code(std::errc::connection_aborted), msg){
	}
	SResourceExceptionABORT()
	: SResourceException(std::make_error_code(std::errc::connection_aborted)){
	}

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
 * ExceptionTIMEOUT
 */
typedef class SResourceExceptionTIMEOUT : public SResourceException {
public:
	using SResourceException::SResourceException;
	/**
	 * constructor
	 */
	SResourceExceptionTIMEOUT(const std::string& msg)
	: SResourceException(std::make_error_code(std::errc::timed_out), msg){
	}
	SResourceExceptionTIMEOUT()
	: SResourceException(std::make_error_code(std::errc::timed_out)){
	}

} ResourceExceptionTIMEOUT;
/**
 * ------------------------------------------------------------------------------------------------
 * resource base
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
	inline pHandler<H> GetHandler() {
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
	void SetHandler(pHandler<H> h) {
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
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SRESOURCE_H */

