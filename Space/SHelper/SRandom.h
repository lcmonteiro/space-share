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
/**
 */
using namespace std;
/**
 */
class SRandom {
public:
    typedef mt19937 Generator;
    /**
     * random string
     */
    static string RString(size_t n) {
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
    static string RName(size_t n) {
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
    static string RName(GEN& gen, size_t n) {
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
	static Frame RFrame(size_t n) {
        /**
         */
        Frame out;
        out.reserve(n);
        for (unsigned int i = 0; i < n; ++i) {
            out.push_back(Frame::value_type(rand()));
        }
        return out;
    }
};

#endif /* SRANDOM_H */

