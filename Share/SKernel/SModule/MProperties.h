/** 
 * File:   MProperties.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 */
#ifndef SMODULE_PROPERTIES_H
#define SMODULE_PROPERTIES_H
/**
 */
#include "SProcess.h"
/** 
 */
namespace SModule {
    /**
     */
    namespace Properties {
        using Tag = const SProcess::Key;
        /**
         * -----------------------------------------------------------------------------------------------------
         * modules types
         * -----------------------------------------------------------------------------------------------------
         */
        Tag DECODE_Y = "decodeY";
        Tag ENCODE   = "encode";
        Tag ENCODE_Y = "encodeY";
        Tag DECODE   = "decode";
        /**
         * -----------------------------------------------------------------------------------------------------
         * connector types
         * -----------------------------------------------------------------------------------------------------
         */
        Tag MESSAGE_UDP   = "message.udp";
        Tag MESSAGE_LOCAL = "message.local";
        Tag MESSAGE_FILE  = "message.file";
        Tag STREAM_TCP    = "stream.tcp";
        Tag STREAM_LOCAL  = "stream.local";
        /**
         * -----------------------------------------------------------------------------------------------------
         * encoder/decoder/stamps types
         * -----------------------------------------------------------------------------------------------------
         */
        Tag MESSAGE = "message";
        Tag STREAM  = "stream";
        /**
         * other stamps types
         */
        Tag SPARSE = "sparse";
        Tag FULL   = "full";
        /**
         * -----------------------------------------------------------------------------------------------------
         * common attributes
         * -----------------------------------------------------------------------------------------------------
         */
        Tag URI     = "uri";
        Tag TYPE    = "type";
        Tag VERBOSE = "verbose";
        Tag BIND    = "bind";
        Tag ENERGY  = "energy";
        Tag NFRAMES = "nframes";
        Tag SFRAMES = "sframes";
        Tag SECRET  = "secret";
        Tag TIMEOUT = "timeout";
        Tag DELAY   = "delay";
        Tag CACHE   = "cache";
        Tag NOMINAL = "nominal";
        Tag MINIMUM = "minimum";
    }
}
#endif /* SMODULE_PROCESS_H */

