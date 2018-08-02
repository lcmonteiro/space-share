/*
 * Container:   SSContainer.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
#include <sys/socket.h>
/**
 */
#include "SOUdpConnector.h"
/**
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 */
SOUdpConnector::SOUdpConnector(const string address, const string local) : SOutputConnector(address), __local(local){
}
/**
 */
void SOUdpConnector::_write(const Container& Container) {
	/**------------------------------------------------------------------------------------------------------------*
	 * write nframes
	 *-------------------------------------------------------------------------------------------------------------*/
//	__res.Drain(frame);
}
/**
 */
void SOUdpConnector::_open(){
	/**------------------------------------------------------------------------------------------------------------*
	 * connect resources
	 *-------------------------------------------------------------------------------------------------------------*/
	__res.Connect(__uri.Host(), __uri.Port(), SSocketResource::DGRAM, __local.Host(), __local.Port());
}
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
