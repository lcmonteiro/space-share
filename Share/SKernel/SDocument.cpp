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
 * Encoded - NameSpace 
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
/**
 * ----------------------------------------------------------------------------
 * Push frame
 * ----------------------------------------------------------------------------
 */
SIDocument& SIDocument::push(Frame&& data) {
	/**
	 * process
	 */
	switch (__init++) {
		case 0:
		{
			if (data.size()>sizeof (reference_t)) {
				/**
				 * reset
				 */
				__init = 0;
				return *this;
			}
			__pos = data.number<reference_t>();
			return *this;
		}
		case 1:
		{
			if (data.size()>sizeof (framecount_t)) {
				/**
				 * reset
				 */
				__init = 0;
				return *this;
			}
			__n_frames = data.number<framecount_t>();
			return *this;
		}
		case 2:
		{
			if (data.size()>sizeof (framecount_t)) {
				/**
				 * reset
				 */
				__init = 0;
				return *this;
			}
			__capacity = data.number<framecount_t>();
			return *this;
		}
		case 3:
		{	
			if (data.size()>sizeof (framesize_t)) {
				/**
				 * reset
				 */
				__init = 0;
				return *this;
			}
			__frame_sz = data.number<framesize_t>();
			return *this;
		}
		default:
		{
			if (data.size() != __frame_sz) {
				/**
				 * reset
				 */
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
 * End 
 * ------------------------------------------------------------------------------------------------
 */