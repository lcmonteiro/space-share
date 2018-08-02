/* 
 * Container:   SLocationMonitor.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLOCATIONMONITOR_H
#define SLOCATIONMONITOR_H
/**
 */
#include "SKernel/SLocation.h"
/*---------------------------------------------------------------------------------------------------------------------*
 * ILocationMonitor template
 *---------------------------------------------------------------------------------------------------------------------*/
template<class R, class S,  class M>
class SYpsilonMonitorT {
public:
	/**
	 * constructor
	 */
	SYpsilonMonitorT() = default;

	SYpsilonMonitorT(chrono::milliseconds timeout) : __timeout(timeout) {
	}
	SYpsilonMonitorT(R& r, S s, chrono::milliseconds timeout) : __timeout(timeout), _r(r), _s(s) {
	}
	/**
	 * destructor
	 */
	virtual ~SYpsilonMonitorT() = default;
	/**
	 * insert resources
	 */
	void Insert(R& r, S& s) {
		_r = r, _s = s;
	}
	/** 
         * get resources
	 */
	template<int i = 0>
	SLocation<R> Get() {
		return _r;
	}
	template<int i = 1>
	SLocation<S> Get() {
		return _s;
	}
	/**
	 * wait for resources
	 */
	vector<size_t> Wait() {
		return M(__timeout, _r, _s).Wait();
	}
protected:
        /**
	 * timeout
	 */
	chrono::milliseconds __timeout;
        /**
         * resource R
         */
	R _r;
        /**
         * resource S
         */
	S _s;
};

/*---------------------------------------------------------------------------------------------------------------------*
 * linux platform 
 *---------------------------------------------------------------------------------------------------------------------*/
#ifdef __linux__
/**
 */
#include "SLinux/SLinuxResourceMonitor.h"
/**
 */
template<class R, class S>
class SYpsilonMonitor : public SYpsilonMonitorT<R, S, SLinuxResourceMonitor>{
	using SYpsilonMonitorT<R, S, SLinuxResourceMonitor>::SYpsilonMonitorT;
};
/**
 */
#endif
/**
 */
#endif /* SHANDLERMONITOR_H */

