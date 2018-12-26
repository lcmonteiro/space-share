/* 
 * File:   SIFileConnector.cpp
 * Author: Luis Monteiro
 * 
 * Created on December 11, 2016, 12:47 AM
 */
#include <unistd.h>
#include <fcntl.h>
/**
 */
#include "SIFileConnector.h"
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
SIFileConnector::SIFileConnector(const string address) : SInputConnector(address){
}
/**
 */
Document SIFileConnector::_read() {
	/**------------------------------------------------------------------------------------------------------------*
	 * read context
	 *-------------------------------------------------------------------------------------------------------------*/
	auto position = __res.read(sizeof (reference_t)).Number<reference_t>();
	auto nframest = __res.read(sizeof (numframes_t)).Number<numframes_t>();
	auto nframesp = __res.read(sizeof (numframes_t)).Number<numframes_t>();
	auto framelen = __res.read(sizeof (framesize_t)).Number<framesize_t>();
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
		container.push_back(__res.read(framelen));
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
