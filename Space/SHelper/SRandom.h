/* 
 * File:   SRandom.h
 * Author: Luis Monteiro
 *
 * Created on January 14, 2017, 12:03 AM
 */
#ifndef SRANDOM_H
#define SRANDOM_H
/**
 * std
 */
#include <istream>
#include <string>
#include <random>
#include <list>
/**
 * space
 */
#include "SContainer.h"
#include "SFileResource.h"
/**
 */
using namespace std;
/**
 */
class SRandom {
public:
    typedef mt19937 Generator;
    /**
     * --------------------------------------------------------------------------------------------
     * Random String
     * --------------------------------------------------------------------------------------------
     **/
    static string String(size_t n) {
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
    static string Name(size_t n) {
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
    static string Name(GEN& gen, size_t n) {
        const vector<string> alphabet{
            "bcdfghjklmnpqrstvwxyz", "aeiouy"    
        };
        /**
         */
        string out;
        out.reserve(n);
        for (unsigned int i = 0; i < n; ++i) {
            auto& group = alphabet[i % alphabet.size()];
            //
            out.push_back(group[gen() % group.length()]);
        }
        return out;
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Random Frame
     * --------------------------------------------------------------------------------------------
     **/
	static SFrame Frame(size_t n) {
        SFrame out;
        /**
         */
        out.reserve(n);
        for (unsigned int i = 0; i < n; ++i) {
            out.push_back(Frame::value_type(rand()));
        }
        return out;
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Random File
     * --------------------------------------------------------------------------------------------
     **/
    template<size_t CHUNK=0x1000>
    static SOFileResource File(const string& path, size_t n) {
        SOFileResource out;
        auto d = div(int(n), int(CHUNK));
        for(size_t i=0; i<d.quot; ++i) {
                out.Drain(SRandom::Frame(CHUNK));
        }
        out.Drain(SRandom::Frame(d.rem)).Flush();
        return out;
    }
};

#endif /* SRANDOM_H */

