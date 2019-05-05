/**
 * ------------------------------------------------------------------------------------------------
 * File:   SIDirConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 * ------------------------------------------------------------------------------------------------
 **
 * linux
 */
#include <sys/inotify.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
/**
 * share
 */
#include "SIDirConnector.h"
/**
 * namespaces
 */
using namespace Encoded;
using namespace Message;
/**
 * ----------------------------------------------------------------------------
 * Constructor
 * ----------------------------------------------------------------------------
 */
SIDirConnector::SIDirConnector(const SText address)
: SInputConnector(address) {}
/** 
 * ----------------------------------------------------------------------------
 * Drain
 * ----------------------------------------------------------------------------
 */
std::list<Document> SIDirConnector::_drain() {
	/**
	 * log info
	 */
	INFO("CODE(drain)::IN::n=0");
	/**
	 * drain empty container
	 */
	return {};
}
/**
 * ----------------------------------------------------------------------------
 * Read
 * ----------------------------------------------------------------------------
 */
Document SIDirConnector::_read() {
	// // create resource
	// auto res = __res.resource();
	// // read context ---------------------------------------
	// auto position = res.read(sizeof(reference_t)).Number<reference_t>();
	// auto nframest = res.read(sizeof(framecount_t)).Number<framecount_t>();
	// auto nframesp = res.read(sizeof(framecount_t)).Number<framecount_t>();
	// auto framelen = res.read(sizeof(framesize_t)).Number<framesize_t>();
	// // log
	// INFO("CODE::IN::" 
	// 	<< "pos=" << position << " " 
	// 	<< "n="   << nframest << " " 
	// 	<< "sz="  << nframesp << " " 
	// 	<< "len=" << framelen
	// );
	// // read nframes ---------------------------------------
	// Document container(Context(position, nframest, framelen));
	// container.reserve(nframesp);
	// while(!container.full()){
	// 	container.push_back(res.read(framelen));
	// }
	// // return full container ------------------------------
	// return container;
	return {};
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
