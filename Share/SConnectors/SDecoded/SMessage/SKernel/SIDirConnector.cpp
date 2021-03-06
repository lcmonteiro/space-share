/**
 * -------------------------------------------------------------------------------------------------
 * File:   SIDirConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 * ------------------------------------------------------------------------------------------------
 **
 * std
 */
#include <sys/inotify.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
/**
 * space
 */
#include "SIDirConnector.h"
/**
 * namespaces
 */
using namespace Decoded;
using namespace Message;
/**
 * ----------------------------------------------------------------------------
 * Constructor
 * ----------------------------------------------------------------------------
 */
SIDirConnector::SIDirConnector(const SText address, const SText file)
: SInputConnector(address), __file(file) {}
/**
 * ----------------------------------------------------------------------------
 * Read
 * ----------------------------------------------------------------------------
 */
Document SIDirConnector::_read() {
	/**
	 * open file
	 */
//	auto fd = __openfile();
//	if (fd <= 0) {
//		return Frame();
//	}
	/**
	 * create resource
	 */
//	auto res = SDireResource(fd);
	// read nframes
	Document container;
//	container.reserve(nnframesp);
//	for (auto i = size_t(0); i < nnframesp; ++i) {
//		container.push_back(res.read(framelen));
//	}
	/**
	 */
	return container;
}
/**
 * ----------------------------------------------------------------------------
 * Open
 * ----------------------------------------------------------------------------
 */
void SIDirConnector::_open(){
//	/**
//	 * open file watch
//	 */
//	auto fd = inotify_init();
//	if (fd < 0) {
//		throw ConnectorExection(__uri, make_error_code(errc(errno)));
//        }
//	/**
//	 * register directory
//	 */
//	if (inotify_add_watch(fd, __uri.path().c_str(), IN_CLOSE_WRITE | IN_MOVED_TO) < 0) {
//		throw ConnectorExection(__uri, make_error_code(errc(errno)), "inotify_add_watch");
//	}
//	/*
//	 * create resource
//	 */
//	__res = SLinuxResource(fd);
}
/**
 */
//int SIDirConnector::__openfile() {
//	char buf[sizeof (struct inotify_event) + 0x400] __attribute__((aligned(__alignof__(struct inotify_event))));
//	/**
//	 * read raw data
//	 */
//	int len = 0;
//	for (int s = __file.size(); (len <= 0) && (s < 0x400); s += __file.size()) {
//		len = read(__res._Handler(), buf, sizeof (struct inotify_event) + s);
//	}
//	if (len <= 0) {
//		throw ConnectorExection(__uri, make_error_code(errc(errno)));
//	}
//	/**
//	 * map event on raw data
//	 */
//	auto event = (const struct inotify_event *) buf;
//	/**
//	 * verify and open file
//	 */
//	if ((event->mask & (IN_CLOSE | IN_MOVED_TO)) && event->len) {
//		string name(event->name);
//		if (name.find(__file) != std::string::npos) {
//			string path(__uri + "/" + name);
//			int fd = open(path.c_str(), (O_RDONLY));
//			if (fd <= 0) {
//				throw ConnectorExection(__uri, make_error_code(errc(errno)), "file=" + name);
//			}
//			INFO(string(__func__) << "::path=" << path);
//			return fd;
//		}
//	}
//	return -1;
//}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
