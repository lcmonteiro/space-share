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
    using Properties = const SText;
    /**
     * ------------------------------------------------------------------------
     * Funtion properties
     * ------------------------------------------------------------------------
     */
    namespace Function {
        /**
         * type
         */
        Properties TYPE = "type";
        namespace Type {
            Properties MESSAGE = "message";
        }
        /**
         * stamps types
         */
        Properties MESSAGE = "message";
        Properties STREAM  = "stream" ;
        Properties SPARSE = "sparse"  ;
        Properties FULL   = "full"    ;
        /**
         * others
         */
        Properties SECRET = "secret" ;
        Properties CACHE  = "cache"  ;
        Properties ENERGY = "energy" ;
        Properties VERBOSE= "verbose";
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
        Properties TYPE = "type";
        namespace Type {
            Properties MESSAGE_REMOTE = "message.remote";
            Properties MESSAGE_LOCAL  = "message.local" ;
            Properties MESSAGE_FILE   = "message.file"  ;
            Properties STREAM_REMOTE  = "stream.remote" ;
            Properties STREAM_LOCAL   = "stream.local"  ;
        }
        /**
         * others
         */
        Properties URI     = "uri"     ;
        Properties VERBOSE = "verbose" ;
        Properties ENERGY  = "energy"  ;
        Properties NFRAMES = "nframes" ;
        Properties SFRAMES = "sframes" ;
        Properties SECRET  = "secret"  ;
        Properties TIMEOUT = "timeout" ;
        Properties DELAY   = "delay"   ;
        Properties CACHE   = "cache"   ;
        Properties NOMINAL = "nominal" ;
        Properties MINIMUM = "minimum" ;
    }

    // /**
    //  */
    // namespace Properties {
    //     /**
    //      * -----------------------------------------------------------------------------------------------------
    //      * modules types
    //      * -----------------------------------------------------------------------------------------------------
    //      */
    //     Properties DECODE_Y = "decodeY";
    //     Properties ENCODE   = "encode";
    //     Properties ENCODE_Y = "encodeY";
    //     Properties DECODE   = "decode";
    //     /**
    //      * -----------------------------------------------------------------------------------------------------
    //      * connector types
    //      * -----------------------------------------------------------------------------------------------------
    //      */
    //     Properties MESSAGE_UDP   = "message.udp";
    //     Properties MESSAGE_LOCAL = "message.local";
    //     Properties MESSAGE_FILE  = "message.file";
    //     Properties STREAM_TCP    = "stream.tcp";
    //     Properties STREAM_LOCAL  = "stream.local";
    //     /**
    //      * -----------------------------------------------------------------------------------------------------
    //      * encoder/decoder/stamps types
    //      * -----------------------------------------------------------------------------------------------------
    //      */
    //     Properties MESSAGE = "message";
    //     Properties STREAM  = "stream";
    //     /**
    //      * other stamps types
    //      */
    //     Properties SPARSE = "sparse";
    //     Properties FULL   = "full";
    //     /**
    //      * -----------------------------------------------------------------------------------------------------
    //      * common attributes
    //      * -----------------------------------------------------------------------------------------------------
    //      */
    //     Properties URI     = "uri";
    //     Properties TYPE    = "type";
    //     Properties VERBOSE = "verbose";
    //     Properties BIND    = "bind";
    //     Properties ENERGY  = "energy";
    //     Properties NFRAMES = "nframes";
    //     Properties SFRAMES = "sframes";
    //     Properties SECRET  = "secret";
    //     Properties TIMEOUT = "timeout";
    //     Properties DELAY   = "delay";
    //     Properties CACHE   = "cache";
    //     Properties NOMINAL = "nominal";
    //     Properties MINIMUM = "minimum";
    // }
}
#endif /* SMODULE_PROCESS_H */

