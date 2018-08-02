/*
 * Container:   SIUdpConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
#include <sys/socket.h>
/**
 */
#include <regex>
/**
 */
#include "SIUdpConnector.h"
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
SIUdpConnector::SIUdpConnector(
        const string address, 
        const string local,
        const size_t nnframes
) : SInputConnector(address), __local(local), __container(nnframes) {
}
/**
 */
Container SIUdpConnector::_read() {
//	IBreakFrame buffer;
//	/**------------------------------------------------------------------------------------------------------------*
//	 * Fill buffer
//	 *-------------------------------------------------------------------------------------------------------------*/
//	__res.Fill(__buffer);
//	/*-------------------------------------------------------------------------------------------------------------*
//	 * check if frame is full 
//	 *-------------------------------------------------------------------------------------------------------------*/
//	if (__buffer.Full()) {
//		buffer = IBreakFrame(__buffer.size());
//		swap(__buffer, buffer);
//		__container.push_back(move(buffer));
//	}
	/**
	 */
	return Container();
}
/**
 */
void SIUdpConnector::_open() {
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
