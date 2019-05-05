/**
 * ------------------------------------------------------------------------------------------------
 * File:   SODirConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 * ------------------------------------------------------------------------------------------------
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
 * share
 */
#include "SODirConnector.h"
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
SODirConnector::SODirConnector(const SText address)
: SOutputConnector(address) {
	/**
	 * create directory
	 */
	::mkdir(address.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	/**
	 * initial state
	 */
	//__state = 0;
}
/**
 * ----------------------------------------------------------------------------
 * Write
 * ----------------------------------------------------------------------------
 */
void SODirConnector::_write(const Document& container) {
//	/**
//	 * log
//	 */
//	INFO("DATA::OUT::n=" << frame.size() << frame);
//	/**
//	 * fill buffer
//	 */
//	__buffer.write(frame);
//	/**
//	 * states 
//	 */
//	static vector < function < size_t() >> machine {
//		/**
//		 * check start sequence 
//		 */
//		[this]() {
//			static Frame SEQ({1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233});
//			/**
//			 * check sequency
//			 */
//			auto check = [](Buffer& buffer) {
//				for (auto& n : SEQ){
//					auto g = buffer.get();
//					if (g != n) {
//						return false;
//					}
//				}
//				return true;
//			};
//			/**
//			 * wait sequency
//			 */
//			while (__buffer.size() >= SEQ.size()) {
//				if (check(__buffer)) {
//					return 1;
//				}
//			}
//			return 0;
//		},
//		/**
//		 * read address size
//		 */
//		[this]() {
//			try {
//			       __size = __buffer.read(sizeof (uint32_t)).Number<uint32_t>();
//			} catch (...) {
//			       return 1;
//			}
//			return 2;
//		},
//		/**
//		 * read address
//		 */
//		[this]() {
//			try {
//			       __path = __buffer.read(__size);
//			} catch (...) {
//			       return 2;
//			}
//			return 3;
//		},
//		/**
//		 * read file size
//		 */
//		[this]() {
//			try {
//			       __size = __buffer.read(sizeof (filesize_t)).Number<filesize_t>();
//			} catch (...) {
//			       return 3;
//			}
//			return 4;
//		},
//		/**
//		 * open file
//		 */
//		[this]() {
//			try {
//			       __res = __dir.resource(string(__path.begin(),__path.end()));
//			} catch (...) {
//			       return 4;
//			}
//			return 5;
//		},
//		/**
//		 * write frame
//		 */
//		[this]() {
//			if (__res.position() + __buffer.size() < __size) {
//				__res.Drain(__buffer.read());
//				return 5;
//			}
//			return 6;
//		},
//		/**
//		 * close resource
//		 */
//		[this]() {
//			__res.Drain(__buffer.read(__size  -__res.position())).Flush();
//			return 0;
//		}
//	};
//	/**
//	 * process state
//	 */	
//	for (auto last = __state; (__state = machine[__state]()) != last; last = __state);
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
