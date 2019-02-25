/*
 * File:   SIFileConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
#include <unistd.h>
#include <fcntl.h>
/**
 */
#include "SIFileConnector.h"
/**
 * Begin namespace 
 */
namespace Decoded {
/**
 * Begin namespace Stream
 */
namespace Stream {
/**
 */
SIFileConnector::SIFileConnector(
	const string address,
	const size_t nframes, 
	const size_t nframesize
):SInputConnector(address), __container(nframes), __buffer(nframesize) {
}
/**
 */
Document SIFileConnector::_Read() {
	Document container;
	IFrame buffer;
	/**------------------------------------------------------------------------------------------------------------*
	 * Fill container
	 *----------------------------------------------------------------------------------------*/
	for (; !__container.Full(); __container.push_back(move(buffer))) {
		/**----------------------------------------------------------------------------------------------------*
		 * Fill buffer
		 *-----------------------------------------------------------------------------------------------------*/
		while (!__buffer.Full()) {
			__res.Fill(__buffer);
		}
		/*-----------------------------------------------------------------------------------------------------*
		 * swap buffers
		 *-----------------------------------------------------------------------------------------------------*/
		buffer = IFrame(__buffer.size());
		swap(__buffer, buffer);
	}
	/*----------------------------------------------------------------------------------------*
	 * swap containers
	 *----------------------------------------------------------------------------------------*/
	container = Document(__container.capacity());
	swap(__container, container);
	/*----------------------------------------------------------------------------------------*
	 * log
	 *----------------------------------------------------------------------------------------*/
	INFO("DATA(read)::IN::n=" <<container.size());
	/**
	 */
	return move(container);
}
/**
 */
list<Document> SIFileConnector::_Drain() {
	list<Document> out;
	/*----------------------------------------------------------------------------------------*
	 * check if container is full 
	 *----------------------------------------------------------------------------------------*/
	if (!__container.empty()) {
		auto container = Document(__container.capacity());
		swap(__container, container);
		out.push_back(move(container));
	}
	/*----------------------------------------------------------------------------------------*
	 * check if frame is full 
	 *----------------------------------------------------------------------------------------*/
	if (!__buffer.Empty()) {
		auto buffer = IFrame(__buffer.size());
		swap(__buffer, buffer);
		out.push_back(Document{move(buffer.Shrink())});
	}
	/*----------------------------------------------------------------------------------------*
	 * log
	 *----------------------------------------------------------------------------------------*/
	INFO("DATA(drain)::IN::n=" << out.size());
	/**
	 */
	return move(out);
}
/**
 * End namespace Stream
 */
}
/**
 * End namespace Decoded
 */
}
