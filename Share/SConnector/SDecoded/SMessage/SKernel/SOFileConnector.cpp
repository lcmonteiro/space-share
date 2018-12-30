/*
 * Container:   SSContainer.cpp
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
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 */
SOFileConnector::SOFileConnector(const string address) : SOutputConnector(address) {
//	__state = 0;
}
/**
 * 
 */
void SOFileConnector::_Write(const Container& frame) {
//	/*----------------------------------------------------------------------------------------*
//	 * log
//	 *----------------------------------------------------------------------------------------*/
//	INFO("DATA::OUT::n=" << frame.size() << frame);
//	/**
//	 * fill buffer
//	 */
//	__buffer.Write(frame);
//	/**
//	 * states 
//	 */
//	vector < function < size_t() >> machine {
//		/**----------------------------------------------------------------------------------------------------*
//		 * check start sequence 
//		 *-----------------------------------------------------------------------------------------------------*/
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
//			while (__buffer.Length() >= SEQ.size()) {
//				if (check(__buffer)) {
//					return 1;
//				}
//			}
//			return 0;
//		},
//		/**----------------------------------------------------------------------------------------------------*
//		 * read address size
//		 *-----------------------------------------------------------------------------------------------------*/
//		[this]() {
//			try {
//			       __size = filesize_t(__buffer.Read(sizeof (uint32_t)).Number<uint32_t>());
//			} catch (...) {
//			       return 1;
//			}
//			return 2;
//		},
//		/**----------------------------------------------------------------------------------------------------*
//		 * read address
//		 *-----------------------------------------------------------------------------------------------------*/
//		[this]() {
//			try {
//			       __path = __buffer.Read(__size);
//			} catch (...) {
//			       return 2;
//			}
//			return 3;
//		},
//		/**----------------------------------------------------------------------------------------------------*
//		 * read file size
//		 *-----------------------------------------------------------------------------------------------------*/
//		[this]() {
//			try {
//			       __size = __buffer.Read(sizeof (filesize_t)).Number<filesize_t>();
//			} catch (...) {
//			       return 3;
//			}
//			return 4;
//		},
//		/**----------------------------------------------------------------------------------------------------*
//		 * write frame
//		 *-----------------------------------------------------------------------------------------------------*/
//		[this]() {
//			if (__res.Position() + __buffer.Length() < __size) {
//				__res.Drain(__buffer.Read());
//				return 4;
//			}
//			return 5;
//		},
//		/**----------------------------------------------------------------------------------------------------*
//		 * close resource
//		 *-----------------------------------------------------------------------------------------------------*/
//		[this]() {
//			__res.Drain(__buffer.Read(__size  -__res.Position())).Flush();
//			/**/
//			_Close();
//			return 6;
//		},
//		/**----------------------------------------------------------------------------------------------------*
//		 * dead
//		 *-----------------------------------------------------------------------------------------------------*/
//		[this]() {
//			throw OConnectorExceptionDEAD(__uri);
//			return 6;
//		}
//	};
//	/**
//	 * process state
//	 */	
//	for (auto last = __state; (__state = machine[__state]()) != last; last = __state);
}
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
