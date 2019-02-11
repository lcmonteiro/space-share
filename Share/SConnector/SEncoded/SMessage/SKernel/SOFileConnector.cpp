/* 
 * File:   SOFileConnector.cpp
 * Author: Luis Monteiro
 * 
 * Created on December 10, 2016, 4:32 PM
 * 
 * c++ std
 */
#include <sstream>
/**
 */
#include "SOFileConnector.h"
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
SOFileConnector::SOFileConnector(const string address) : SOutputConnector(address) {
}
/**
 */
void SOFileConnector::_Write(const Document& container) {
	/**------------------------------------------------------------------------------------------------------------*
	 * write context
	 *----------------------------------------------------------------------------------------*/
	__res.Drain(Frame().Number<reference_t>(container.GetPosition()));
	__res.Drain(Frame().Number<numframes_t>(container.GetNumFrames()));
	__res.Drain(Frame().Number<numframes_t>(container.size()));
	__res.Drain(Frame().Number<framesize_t>(container.GetFrameSize()));
	// log ------------------------------------------------
	INFO("CODE::OUT::"
		<< "pos=" << container.GetPosition()  << " " 
		<< "n="   << container.GetNumFrames() << " "
		<< "sz="  << container.GetFrameSize() << " " 
		<< "len=" << container.size()
	);
	/**------------------------------------------------------------------------------------------------------------*
	 * write nframes
	 *----------------------------------------------------------------------------------------*/
	for (auto& f : container) {
		__res.Drain(f);
	}
	/**------------------------------------------------------------------------------------------------------------*
	 * flush resource
	 *----------------------------------------------------------------------------------------*/
	__res.Flush();
}
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
