/* 
 * File:   SBufferShare.h
 * Author: Luis Monteiro
 *
 * Created on September 14, 2016, 9:49 AM
 */
#ifndef SBUFFERSHARE_H
#define    SBUFFERSHARE_H
/**
 */
#include <cstdint>
#include <cstddef>
/**
 * space kernel
 */
#include "SContainer.h"
#include "SCodec.h"
/*---------------------------------------------------------------------------------------------------------------------*
 * default definitions
 *---------------------------------------------------------------------------------------------------------------------*/
#define BS_CAPACITY 100
/*---------------------------------------------------------------------------------------------------------------------*
 * OBufferShare
 *---------------------------------------------------------------------------------------------------------------------*/
class OBufferShare {
public:
    /**
     * constructor 
     */
    OBufferShare(size_t capacity = BS_CAPACITY) : __encoder(capacity) {
    }
    /**
     * destructor 
     */
    virtual ~OBufferShare() = default;
    /**
     * set buffer
     */
    size_t Set(const Frame& data, size_t sframes, size_t redundancy = 0);
    /**
     * get coded frame
     */
    Frame Get();
protected:
    /**
     * worker
     */
    CodecEncoder __encoder;
};
/*---------------------------------------------------------------------------------------------------------------------*
 * IBufferShare
 *---------------------------------------------------------------------------------------------------------------------*/
class IBufferShare {
public:
    /**
     * constructor 
     */
    IBufferShare(size_t capacity = BS_CAPACITY) : __decoder(capacity) {
    }
    /**
     * destructor 
     */
    virtual ~IBufferShare() = default;
    /**
     * set coded frame
     */
    bool Set(Frame frame);
    /**
     * get buffer
     */
    Frame Get();
protected:
    /**
     */
    CodecDecoder __decoder; 
};
/**
 */
#endif    /* SBUFFERSHARE_H */

