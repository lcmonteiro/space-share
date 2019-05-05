/**
 * ------------------------------------------------------------------------------------------------
 * File:   SODirConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 * ------------------------------------------------------------------------------------------------
 */
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
/**
 * std
 */
#include <cstdio>
#include <iostream>
#include <string.h>
/**
 * space
 */
#include "SFileResource.h"
#include "SODirConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
namespace Message {
/**
 * ----------------------------------------------------------------------------
 * Constructor
 * ----------------------------------------------------------------------------
 */
SODirConnector::SODirConnector(const SText address, const uint32_t nfiles)
: SOutputConnector(address), __n(nfiles) {
}
/**
 * ----------------------------------------------------------------------------
 * Write
 * ----------------------------------------------------------------------------
 */
void SODirConnector::_write(const Document& container) {
    /**
     * open file
     */
    auto res = __res.resource();
    /**
     * write context
     */
    res.drain(Frame().number<reference_t>(container.position()));
    res.drain(Frame().number<framecount_t>(container.frame_count()));
    res.drain(Frame().number<framecount_t>(container.size()));
    res.drain(Frame().number<framesize_t>(container.frame_size()));
    /**
     *  log info
     */
    INFO("CODE::OUT::"
        << "pos=" << container.position()    << " " 
        << "n="   << container.frame_count() << " "
        << "sz="  << container.frame_size()  << " " 
        << "len=" << container.size() );
    /**
     * write nframes
     */
    for (auto& f : container) {
        res.drain(f);
    }
}
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */