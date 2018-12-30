/* 
 * Stream: STask.h
 * Author: Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
 */
#ifndef STASK_H
#define STASK_H
/*------------------------------------------------------------------------------------------------*
 * linux platform
 *------------------------------------------------------------------------------------------------*/
#ifdef __linux__
/**
 */
#include "SLinuxTask.h"
/**
 */
class STask : public SLinuxTask {
public:
    using SLinuxTask::SLinuxTask;
};
/**
 */
#endif
/**
 */
#endif /* STASK_H */

