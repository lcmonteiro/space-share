/**
 * ------------------------------------------------------------------------------------------------
 * File:   SEngineCodec.h
 * Author: Luis Monteiro
 *
 * Created on November 30, 2015, 5:48 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SENGINECODEC_H
#define SENGINECODEC_H
/**
 * std
 */
#include <utility>
#include <vector>
#include <random>
#include <functional>
#include <cstdint>
/**
 * space
 */
#include "SContainer.h"
/**
 * local
 */
#include "SStampCodec.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Codec Engine
 * ------------------------------------------------------------------------------------------------
 */
namespace Codec {
/**
 * ----------------------------------------------------------------------------
 * Definitions
 * ----------------------------------------------------------------------------
 */
using StampReference = std::reference_wrapper<const Stamp>; 
/**
 * ----------------------------------------------------------------------------
 * Engine
 * ----------------------------------------------------------------------------
 */
class SEngine {
public:
    using Random = std::random_device;
    /**
     * ----------------------------------------------------
     * Encode 
     * ----------------------------------------------------
     */
    static uint32_t Encode(
        Container& code, 
        uint32_t size, 
        Container& data, 
        Random& rand, 
        uint32_t highDensity, 
        const Stamp& stamp
    );
    /** 
     * ----------------------------------------------------
     * Decode
     * ----------------------------------------------------
     */
    static uint32_t Decode(
        Container&& code, 
        uint32_t capacity, 
        Container& data, 
        Container& coefs, 
        Frame& fields, 
        const Stamp& stamp 
    );
    /**
     * ----------------------------------------------------
     * Header Size
     * ----------------------------------------------------
     */
    static inline uint32_t HeaderSize() {
        /**
         * return seed size
         */
        return (sizeof (uint32_t)); 
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
}
#endif /* SENGINECODEC_H */
