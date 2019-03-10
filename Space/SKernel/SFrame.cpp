/**
 * ------------------------------------------------------------------------------------------------
 * File:   SFrame.cpp
 * Author: Luis Monteiro
 *
 * Created on February  2, 2019, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 * space
 */
#include "SFrame.h"
/**
 * namespaces
 */
using namespace std;
/**
 * ------------------------------------------------------------------------------------------------
 * convertions
 * ------------------------------------------------------------------------------------------------
 * SFrame
 * ----------------------------------------------------------------------------
 * operatores
 * --------------------------------------------------------
 **/
SFrame& SFrame::operator=(SIOFrame&& f) {
    return (*this = forward<SFrame>(f.Shrink()));
} 
SFrame& SFrame::operator=(const SIOFrame& f) {
    return (*this = forward<SFrame>(SIOFrame(f).Shrink()));
}
/**
 * ------------------------------------------------------------------------
 * conversions
 * ------------------------------------------------------------------------
 * constructors
 * ----------------------------------------------------
 */
SIOFrame::SIOFrame()
: SFrame(), 
__beg(Super::begin()), __end(Super::end()) {}

SIOFrame::SIOFrame(SIOFrame&& f) 
: SFrame(forward<SFrame>(f)), 
__beg(f.begin()), __end(f.end()) {}

SIOFrame::SIOFrame(SFrame&& f)
: SFrame(forward<SFrame>(f)), 
__beg(Super::begin()), __end(Super::end()) {}

SIOFrame::SIOFrame(const SFrame& f) 
: SFrame(f.begin(), f.end()), 
__beg(Super::begin()), __end(Super::end()) {}

SIOFrame::SIOFrame(const SIOFrame& f) 
: SFrame(f.SFrame::begin(), f.Frame::end()), 
__beg(next(Super::begin(), f.OSize())), 
__end(prev(Super::end(),   f.ISize())) {}
/*
 * --------------------------------------------------------
 * operatores
 * --------------------------------------------------------
 **/
SIOFrame& SIOFrame::operator=(SFrame&& f) {
    return (*this = forward<SFrame>(f.Shrink()));
} 
SIOFrame& SIOFrame::operator=(SIOFrame&& f) {
    return (*this = forward<SFrame>(f.Shrink()));
} 
SIOFrame& SIOFrame::operator=(const SFrame& f) {
    return (*this = forward<SFrame>(SIOFrame(f).Shrink()));
}
SIOFrame& SIOFrame::operator=(const SIOFrame& f) {
    return (*this = forward<SFrame>(SIOFrame(f).Shrink()));
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 **/