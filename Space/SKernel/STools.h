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
	typedef mt19937 Generator;
	/**
	 * random string
	 */
	static string Ramdom(size_t n) {
		const string alphabet("abcdefghijklmnopqrstuvwxyz0123456789");
		/**
		 */
		string out;
		out.reserve(n);
		for (unsigned int i = 0; i < n; ++i) {
			out.push_back(alphabet[rand() % alphabet.length()]);
		}
		return out;
	}
	static string RamdomName(size_t n) {
		const vector<string> alphabet{
			"bcdfghjklmnpqrstvwxyz", "aeiouy"	
		};
		/**
		 */
		string out;
		out.reserve(n);
		for (unsigned int i = 0; i < n; ++i) {
			auto& group = alphabet[i % alphabet.size()];
			/**
			 */
			out.push_back(group[rand() % group.length()]);
		}
		return out;
	}
	template<class GEN>
	static string RamdomName(GEN& gen, size_t n) {
		const vector<string> alphabet{
			"bcdfghjklmnpqrstvwxyz", "aeiouy"	
		};
		/**
		 */
		string out;
		out.reserve(n);
		for (unsigned int i = 0; i < n; ++i) {
			auto& group = alphabet[i % alphabet.size()];
			/**
			 */
			out.push_back(group[gen() % group.length()]);
		}
		return out;
	}
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

