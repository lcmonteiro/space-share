/* 
 * Container:   SResourceStream.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SRESOURCESTREAM_H
#define SRESOURCESTREAM_H
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
 * resource base
 * ----------------------------------------------------------------------------
 */
typedef class SResource {
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
	 * --------------------------------
	 * definitions
	 * --------------------------------
	 */
	template<class H = SHandler>
	using pHandler = shared_ptr<H>;
	/**
	 * --------------------------------
	 * get handler
	 * --------------------------------
	 */
	template<class H = SHandler>
	inline pHandler<H> GetHandler() {
		return static_pointer_cast<H>(__h);
	}
protected:
	/**
	 * ----------------------------------------------------
	 * constructors and destructor
	 * ----------------------------------------------------
	 * default constructor
	 */
	SResource() = default;
	SResource(SResource&& ) = default;
	/**
	 * default destructor
	 */
	virtual ~SResource() = default; 
	/***
	 * ----------------------------------------------------
	 * methods
	 * ----------------------------------------------------
	 * set phandler
	 */
	template<class H = SHandler>
	void SetHandler(pHandler<H> h) {
		__h = static_pointer_cast<SHandler>(h);	
	}
private:
	/**
	 * --------------------------------
	 * pointer to handler
	 * --------------------------------
	 */
	shared_ptr<SHandler> __h;
} Resource;
/**
 * ----------------------------------------------------------------------------
 * Exceptions
 * ----------------------------------------------------------------------------
 */
typedef class SResourceException : public system_error {
public:
	using system_error::system_error;

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
	SResourceExceptionABORT(const string& msg):SResourceException(make_error_code(errc::connection_aborted), msg){
	}
	SResourceExceptionABORT():SResourceException(make_error_code(errc::connection_aborted)){
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
	SResourceExceptionTIMEOUT(const string& msg):SResourceException(make_error_code(errc::timed_out), msg){
	}
	SResourceExceptionTIMEOUT():SResourceException(make_error_code(errc::timed_out)){
	}

} ResourceExceptionTIMEOUT;
/**
 */
#endif /* SRESOURCESTREAM_H */

