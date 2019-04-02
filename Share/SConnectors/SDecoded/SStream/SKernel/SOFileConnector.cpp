/*
 * File:   SSContainer.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
/**
 */
#include "SOFileConnector.h"
/**
 */
#ifdef __CYGWIN__
#define ftruncate64 ftruncate
#endif
/**
 * Begin namespace Data
 */
namespace Decoded {
/**
 * Begin namespace Data
 */
namespace Stream {
/**
 */
SOFileConnector::SOFileConnector(const string address) : SOutputConnector(address) {
}
/**
 */
void SOFileConnector::_Write(const Container& container) {
	/*----------------------------------------------------------------------------------------*
	 * log
	 *----------------------------------------------------------------------------------------*/
	INFO("DATA::OUT::n=" <<container.size() << "=" << container.front());
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
 * End namespace Stream
 */
}
/**
 * End namespace Decoded
 */
}
