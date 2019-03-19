/*
 * File:   SODirConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
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
 * Space
 */
#include "SFileResource.h"
/**
 */
#include "SODirConnector.h"
/**
 * Begin namespace Encoded
 */
namespace Encoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 */
SODirConnector::SODirConnector(const SText address, const uint32_t nfiles)
: SOutputConnector(address), __n(nfiles) {
}
/**
 */
void SODirConnector::_Write(const Document& container) {
    /**------------------------------------------------------------------------------------------------------------*
     * open file
     *----------------------------------------------------------------------------------------*/
    auto res = __res.GetResource();
    /**------------------------------------------------------------------------------------------------------------*
     * write context
     *----------------------------------------------------------------------------------------*/
    res.Drain(Frame().Number<reference_t>(container.Position()));
    res.Drain(Frame().Number<numframes_t>(container.NumFrames()));
    res.Drain(Frame().Number<numframes_t>(container.size()));
    res.Drain(Frame().Number<framesize_t>(container.FrameSize()));
    // log ------------------------------------------------
    INFO("CODE::OUT::"
        << "pos=" << container.Position()  << " " 
        << "n="   << container.NumFrames() << " "
        << "sz="  << container.FrameSize() << " " 
        << "len=" << container.size()
    );
    /**------------------------------------------------------------------------------------------------------------*
     * write nframes
     *----------------------------------------------------------------------------------------*/
    for (auto& f : container) {
        res.Drain(f);
    }
}
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
