/*
 * Container:   SODirConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
/**
 * std
 */
#include <cstdio>
#include <iostream>
#include <string.h>
/**
 * Space
 */
#include "SFileResource.h"
/**
 */
#include "SODirConnector.h"
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
SODirConnector::SODirConnector(const string address, const uint32_t nfiles)
: SOutputConnector(address), __n(nfiles) {
}
/**
 */
void SODirConnector::_write(const Document& container) {
	/**------------------------------------------------------------------------------------------------------------*
	 * open file
	 *-------------------------------------------------------------------------------------------------------------*/
	auto res = __res.resource();
	/**------------------------------------------------------------------------------------------------------------*
	 * write context
	 *-------------------------------------------------------------------------------------------------------------*/
	res.drain(Frame(sizeof (reference_t)).Number<reference_t>(container.GetPosition()));
	res.drain(Frame(sizeof (numframes_t)).Number<numframes_t>(container.GetNumFrames()));
	res.drain(Frame(sizeof (numframes_t)).Number<numframes_t>(container.size()));
	res.drain(Frame(sizeof (framesize_t)).Number<framesize_t>(container.GetFrameSize()));
	/**------------------------------------------------------------------------------------------------------------*
	 * log
	 *-------------------------------------------------------------------------------------------------------------*/
	INFO("CODE::OUT::"
		<< "pos=" << container.GetPosition() << " " << "n=" << container.GetNumFrames() << " "
		<< "sz=" << container.GetFrameSize() << " " << "len=" << container.size()
	);
	/**------------------------------------------------------------------------------------------------------------*
	 * write nframes
	 *-------------------------------------------------------------------------------------------------------------*/
	for (auto& f : container) {
		res.drain(f);
	}
}
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
