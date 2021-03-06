/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   STools.h
 * Author: Luis Monteiro
 *
 * Created on January 14, 2017, 12:03 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef STOOLS_H
#define STOOLS_H
/**
 * std
 */
#include <string>
#include <random>
#include <list>
/**
 * space
 */
#include "SContainer.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Tools
 * ------------------------------------------------------------------------------------------------
 */
class STools {
public:
    /**
     * ------------------------------------------------------------------------
     * Split
     * ------------------------------------------------------------------------
     */
    static std::list<Container> Split(Container container, size_t max) {
        std::list<Container> out;
        /**
         * process
         */
        size_t size = 0;
        Container chunk;
        for(auto& frame : container) {
			size += frame.size();
        	/**
             * verify limit
             */
			if (size > max) {
				out.emplace_back(chunk.detach());
				size = frame.size();
			}
			/**
             * move frame to chunk 
             */
			chunk.emplace_back(frame.detach());
        }
        out.emplace_back(chunk.detach());
        /**
         * return split
         */
        return out;
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* STOOLS_H */

