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
class SRandom { 
public:
    using Generator = std::mt19937;
    /**
     * --------------------------------------------------------------------------------------------
     * Random Number
     * --------------------------------------------------------------------------------------------
     **/
    template <typename T = int, typename G = Generator>
    static T Number() {
        auto gen = G(__Device());
        return T(gen());
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Random String
     * --------------------------------------------------------------------------------------------
     **/
    static std::string String(size_t n) {
        const std::string alphabet("abcdefghijklmnopqrstuvwxyz0123456789");
        /**
         */
        std::string out;
        out.reserve(n);
        for (unsigned int i = 0; i < n; ++i) {
            out.push_back(alphabet[rand() % alphabet.length()]);
        }
        return out;
    }
    static std::string Name(size_t n) {
        const std::vector<std::string> alphabet{
            "bcdfghjklmnpqrstvwxyz", "aeiouy"    
        };
        /**
         */
        std::string out;
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
    static std::string Name(GEN& gen, size_t n) {
        const std::vector<std::string> alphabet{
            "bcdfghjklmnpqrstvwxyz", "aeiouy"    
        };
        /**
         */
        std::string out;
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
    static SIFileResource File(const std::string& path, size_t n) {
        SIFileResource out;
        auto d = div(int(n), int(CHUNK));
        for(size_t i=0; i<d.quot; ++i) {
            out.Drain(SRandom::Frame(CHUNK));
        }
        out.Drain(SRandom::Frame(d.rem)).Flush();
        return out;
    }
    static std::string FileName() {
        return SFileResource::TmpPath() + "/" + SRandom::String(16);
    }
private:
    static std::random_device::result_type __Device(){
        static std::random_device device;
        return device();
    }
};
/**
 */
#endif /* SRANDOM_H */

