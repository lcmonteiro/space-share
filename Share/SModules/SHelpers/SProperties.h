/** 
 * ------------------------------------------------------------------------------------------------
 * File:   SProperties.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SMODULEPROPERTIES_H
#define SMODULEPROPERTIES_H
/**
 * space
 */
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
}
/**
 *-------------------------------------------------------------------------------------------------
 * End
 *-------------------------------------------------------------------------------------------------
 */
#endif /* SMODULEPROPERTIES_H */

