/* 
 * File:   Connector.cpp
 * Author: root
 * 
 * Created on March 27, 2017, 11:47 AM
 */
#include "SConnector.h"
/**
 * wait to be good
 */
SConnector& SConnector::Wait(chrono::milliseconds timeout) {
	auto start = std::chrono::steady_clock::now();
	auto end = start + timeout;
	do {
		if(Good()) {
			return *this;
		}
		if(Inactive()){
			throw ConnectorExceptionDEAD(__uri);
		}
		std::this_thread::yield();
	} while (std::chrono::steady_clock::now() < end);
	/**
	 * throw timeout
	 */
	throw ConnectorExceptionTIMEOUT(__uri);
}
/**
 * Shape stream
 */
list<pair<size_t, size_t>> SConnector::Shape(size_t len, size_t split) {
	list<pair<size_t, size_t>> out;
	/**
	 * compute references
	 */
	auto ref = div(int(len), int(split));
	/**
	 * conditions
	 */
	if (ref.quot == 0) {
		if (ref.rem == 0) {
			return out;
		}
		out.emplace_back(len, 1);
		return out;
	}
	if (ref.rem == 0) {
		out.emplace_back(split, ref.quot);
		return out;
	}
	/**
	 * normal
	 */
	out.emplace_back(split, ref.quot - 1);
	out.emplace_back(ref.rem + split, 1);
	/**
	 */
	return out;
}
