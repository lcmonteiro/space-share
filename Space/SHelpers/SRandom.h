/**
 * -------------------------------------------------------------------------------------------------------------------- 
 * File:   SRandom.h
 * Author: Luis Monteiro
 *
 * Created on January 14, 2017, 12:03 AM
 * --------------------------------------------------------------------------------------------------------------------
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
 * --------------------------------------------------------------------------------------------------------------------
 * Random
 * --------------------------------------------------------------------------------------------------------------------
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
        auto gen = G(__device());
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
            /**
             */
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
        auto out = SFrame(n);
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
    static SOFileResource File(const std::string& path, size_t n) {
        SOFileResource out(path);
        auto d = div(int(n), int(CHUNK));
        for(size_t i=0; i<d.quot; ++i) {
            out.drain(SRandom::Frame(CHUNK));
        }
        out.drain(SRandom::Frame(d.rem)).flush();
        return out;
    }
    static std::string FileName() {
        return SFileResource::PathTemp() + "/" + SRandom::String(16);
    }
private:
    /**
     * --------------------------------------------------------------------------------------------
     * Random Device
     * --------------------------------------------------------------------------------------------
     **/
    static std::random_device::result_type __device() {
        static std::random_device device;
        return device();
    }
};
/**
 * --------------------------------------------------------------------------------------------------------------------
 * End
 * --------------------------------------------------------------------------------------------------------------------
 */
#endif /* SRANDOM_H */

