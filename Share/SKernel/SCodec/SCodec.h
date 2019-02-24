/* 
 * File:   SCodec.h
 * Author: Luis Monteiro
 *
 * Created on November 30, 2015, 5:48 PM
 */
#ifndef SCODEC_H
#define SCODEC_H
/**
 * std
 */
#include <utility>
#include <vector>
#include <random>
#include <functional>
#include <cstdint>
/**
 * space kernel
 */
#include "SContainer.h"
/**
 * local
 */
#include "SCodecStamp.h"
/**
 */
namespace v1 {
    /**
     * Definitions
     */
    using namespace std;
    
    using Random = random_device;

    using StampReference = reference_wrapper<const Stamp>; 
    /**
     * Codec
     */
    class SCodec {
    public:
        /**
         * Definitions
         */
        typedef random_device Random;
        /*-----------------------------------------------------------------------------------------
         * codec functions
         *----------------------------------------------------------------------------------------*/
        static uint32_t Encode(
            Container& code, uint32_t size, Container& data, Random& rand, uint32_t highDensity, const Stamp& stamp
        );
        /** 
         */
        static uint32_t Decode(
            Container&& code, uint32_t capacity, Container& data, Container& coefs, Frame& fields, const Stamp& stamp 
        );
        /**
         */
        static inline uint32_t HeaderSize() {
            return (sizeof (uint32_t)); // seed
        }
    };
}
#endif /* SCODEC_H */