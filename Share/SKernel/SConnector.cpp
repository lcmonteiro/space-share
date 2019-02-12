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
SConnector& SConnector::Wait(std::chrono::milliseconds timeout) {
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
std::list<std::pair<size_t, size_t>> SConnector::Shape(size_t len, size_t split) {
	std::list<std::pair<size_t, size_t>> out;
	/**
	 * compute references
	 */
	auto ref = std::div(int(len), int(split));
	/**
	 * conditions
	 */
	if (0 == ref.quot) {
		if (0 == ref.rem) {
			return out;
		}
		out.emplace_back(len, 1);
		return out;
	}
	if (0 == ref.rem) {
		out.emplace_back(split, ref.quot);
		return out;
	}
	if(1 == ref.quot) {
		out.emplace_back(ref.rem + split, 1);
		return out;
	}
	/**
	 * normal
	 */
	out.emplace_back(split, ref.quot - 1);
	out.emplace_back(ref.rem + split, 1);
	return out;
}
