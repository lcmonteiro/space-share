/* 
 * File:   STools.h
 * Author: Luis Monteiro
 *
 * Created on January 14, 2017, 12:03 AM
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
 */
using namespace std;
/**
 */
class STools {
public:
    /**
     * split
     */
    static list<Container> Split(Container container, size_t max) {
        list<Container> out;
        /**
         * process 
         */
        size_t size = 0;
        Container chunk;
        for(auto& frame : container) {
			size += frame.Size();
			// verify limit
			if (size > max) {
					out.push_back(move(chunk));
					size = frame.Size();
			}
			// move frame to chunk
			chunk.push_back(move(frame));
        }
        out.push_back(move(chunk));
        /**
         * return  
         */
        return out;
    }
};

#endif /* STOOLS_H */

