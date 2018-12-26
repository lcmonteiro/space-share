/*
 * Container:   SIDirConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
#include <sys/inotify.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
/**
 */
#include "SIDirConnector.h"
/**
 * Begin namespace Encoded
 */
namespace Encoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 */
SIDirConnector::SIDirConnector(const string address): SInputConnector(address){
}
/** 
 */
list<Document> SIDirConnector::_drain() {
	/**------------------------------------------------------------------------------------------------------------*
	 * log
	 *-------------------------------------------------------------------------------------------------------------*/
	INFO("CODE(drain)::IN::n=0");
	/*-------------------------------------------------------------------------------------------------------------*
	 * drain container
	 *-------------------------------------------------------------------------------------------------------------*/
	return {};
}
/**
 */
Document SIDirConnector::_read() {
	/**------------------------------------------------------------------------------------------------------------*
	 * create resource
	 *-------------------------------------------------------------------------------------------------------------*/
	auto res = __res.getResource();
	/**------------------------------------------------------------------------------------------------------------*
	 * read context
	 *-------------------------------------------------------------------------------------------------------------*/
	auto position = res.read(sizeof(reference_t)).Number<reference_t>();
	auto nframest = res.read(sizeof(numframes_t)).Number<numframes_t>();
	auto nframesp = res.read(sizeof(numframes_t)).Number<numframes_t>();
	auto framelen = res.read(sizeof(framesize_t)).Number<framesize_t>();
	/**------------------------------------------------------------------------------------------------------------*
	 * log
	 *-------------------------------------------------------------------------------------------------------------*/
	INFO("CODE::IN::" 
		<< "pos=" << position << " " << "n=" << nframest << " " << "sz=" << nframesp<< " " << "len=" << framelen
	);
	/**------------------------------------------------------------------------------------------------------------*
	 * read nframes
	 *-------------------------------------------------------------------------------------------------------------*/
	Document container(Context(position, nframest, framelen));
	container.reserve(nframesp);
	while(!container.Full()){
		container.push_back(res.read(framelen));
	}
	/**
	 */
	return container;
}
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
