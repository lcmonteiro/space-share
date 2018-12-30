/*
 * Container:   SIFileConnector.cpp
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
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 */
SIFileConnector::SIFileConnector(const string address, const size_t nframesize)
: SInputConnector(address), __sframes(nframesize) {
	//__state = 0;
}
/**
 */
Container SIFileConnector::_Read() {
//	IFrame out(__sframes);
//	/**
//	 * states 
//	 */
//	vector < function < size_t(IFrame&) >> machine {
//		/**----------------------------------------------------------------------------------------------------*
//		 * add start sequence 
//		 *-----------------------------------------------------------------------------------------------------*/
//		[this](IFrame& frame){
//			frame = Frame{1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233};			return 1;
//		},
//		/**----------------------------------------------------------------------------------------------------*
//		 * add address size
//		 *-----------------------------------------------------------------------------------------------------*/
//		[this](IFrame& frame){
//			frame = Frame(sizeof(uint32_t)).Number(SFileResource::Basename(__uri).size());	return 2;
//		},
//		/**----------------------------------------------------------------------------------------------------*
//		 * add address
//		 *-----------------------------------------------------------------------------------------------------*/
//		[this](IFrame& frame){
//			frame = Frame(SFileResource::Basename(__uri));					return 3;
//		},
//		/**----------------------------------------------------------------------------------------------------*
//		 * add file size
//		 *-----------------------------------------------------------------------------------------------------*/
//		[this](IFrame& frame){
//			frame = Frame(sizeof(filesize_t)).Number(__res.Size());				return 4;
//		},
//		/**----------------------------------------------------------------------------------------------------*
//		 * read frame
//		 *-----------------------------------------------------------------------------------------------------*/
//		[this](IFrame& frame){
//			__res.Fill(frame); frame.Shrink();						return 4;
//		}
//	};
//	/**
//	 * process state
//	 */
//	__state = machine[__state](out);
	/**------------------------------------------------------------------------------------------------------------*
	 * info
	 *----------------------------------------------------------------------------------------*/
//	INFO("DATA(read)::IN::n=" << out.size() << "=" << out);
	return Container();
}
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
