/** 
 * File:   MProperties.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 */
#ifndef SMODULE_PROPERTIES_H
#define SMODULE_PROPERTIES_H
/**
 * space
 */
#include "SModule.h"
#include "SText.h"
/** 
 * -------------------------------------------------------------------------------------------------
 * Module properties
 * -------------------------------------------------------------------------------------------------
 */
namespace Module {
    using TXT = const SText;
    /**
     * ------------------------------------------------------------------------
     * Funtion properties
     * ------------------------------------------------------------------------
     */
    namespace Function {
        /**
         * type
         */
        TXT TYPE = "type";
        namespace Type {
            TXT MESSAGE = "message";
        }
        /**
         * others
         */
        TXT SECRET = "secret" ;
        TXT CACHE  = "cache"  ;
        TXT ENERGY = "energy" ;
        TXT VERBOSE= "verbose";
    }
    /**
     * ------------------------------------------------------------------------
     * Input properties
     * ------------------------------------------------------------------------
     */
    namespace IO {
        /**
         * type
         */
        TXT TYPE = "type";
        namespace Type {
            TXT MESSAGE_REMOTE = "message.remote";
            TXT MESSAGE_LOCAL  = "message.local" ;
            TXT MESSAGE_FILE   = "message.file"  ;
            TXT STREAM_REMOTE  = "stream.remote" ;
            TXT STREAM_LOCAL   = "stream.local"  ;
        }
        /**
         * others
         */
        TXT URI = "uri";
    }

    /**
     */
    namespace Properties {
        /**
         * -----------------------------------------------------------------------------------------------------
         * modules types
         * -----------------------------------------------------------------------------------------------------
         */
        TXT DECODE_Y = "decodeY";
        TXT ENCODE   = "encode";
        TXT ENCODE_Y = "encodeY";
        TXT DECODE   = "decode";
        /**
         * -----------------------------------------------------------------------------------------------------
         * connector types
         * -----------------------------------------------------------------------------------------------------
         */
        TXT MESSAGE_UDP   = "message.udp";
        TXT MESSAGE_LOCAL = "message.local";
        TXT MESSAGE_FILE  = "message.file";
        TXT STREAM_TCP    = "stream.tcp";
        TXT STREAM_LOCAL  = "stream.local";
        /**
         * -----------------------------------------------------------------------------------------------------
         * encoder/decoder/stamps types
         * -----------------------------------------------------------------------------------------------------
         */
        TXT MESSAGE = "message";
        TXT STREAM  = "stream";
        /**
         * other stamps types
         */
        TXT SPARSE = "sparse";
        TXT FULL   = "full";
        /**
         * -----------------------------------------------------------------------------------------------------
         * common attributes
         * -----------------------------------------------------------------------------------------------------
         */
        TXT URI     = "uri";
        TXT TYPE    = "type";
        TXT VERBOSE = "verbose";
        TXT BIND    = "bind";
        TXT ENERGY  = "energy";
        TXT NFRAMES = "nframes";
        TXT SFRAMES = "sframes";
        TXT SECRET  = "secret";
        TXT TIMEOUT = "timeout";
        TXT DELAY   = "delay";
        TXT CACHE   = "cache";
        TXT NOMINAL = "nominal";
        TXT MINIMUM = "minimum";
    }
}
#endif /* SMODULE_PROCESS_H */

