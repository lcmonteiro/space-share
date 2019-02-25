/**
 * ------------------------------------------------------------------------------------------------
 * File:   SContainer.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 * ------------------------------------------------------------------------------------------------
 **
 * std 
 */
#include <iostream>
/** 
 * space
 */
#include "SDocument.h"
/**
 * ------------------------------------------------------------------------------------------------
 * encoded 
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
/**
 * ----------------------------------------------------------------------------
 * push frame
 * ----------------------------------------------------------------------------
 */
SIDocument& SIDocument::Push(Frame&& data) {
	// process --------------------------------------------
	switch (__init++) {
		case 0:
		{
			if (data.size()>sizeof (reference_t)) {
				// reset ----------------------------------
				__init = 0;
				return *this;
			}
			__pos = data.Number<reference_t>();
			return *this;
		}
		case 1:
		{
			if (data.size()>sizeof (numframes_t)) {
				// reset ----------------------------------
				__init = 0;
				return *this;
			}
			__n_frames = data.Number<numframes_t>();
			return *this;
		}
		case 2:
		{
			if (data.size()>sizeof (numframes_t)) {
				// reset ----------------------------------
				__init = 0;
				return *this;
			}
			__capacity = data.Number<numframes_t>();
			return *this;
		}
		case 3:
		{	
			if (data.size()>sizeof (framesize_t)) {
				// reset ----------------------------------
				__init = 0;
				return *this;
			}
			__frame_sz = data.Number<framesize_t>();
			return *this;
		}
		default:
		{
			if (data.size() != __frame_sz) {
				// reset ----------------------------------
				clear();
				__init = 0;
				return *this;
			}
			push_back(move(data));
		}
	}
	return *this;
}
}
/**
 * ------------------------------------------------------------------------------------------------
 * end 
 * ------------------------------------------------------------------------------------------------
 */