/*
 * File:   SFrame.cpp
 * Author: Luis Monteiro
 *
 * Created on February  2, 2019, 10:21 AM
 **
 * space
 */
#include "SFrame.h"
/**
 * ------------------------------------------------------------------------------------------------
 * convertions
 * ------------------------------------------------------------------------------------------------
 * SFrame
 * ----------------------------------------------------------------------------
 * constructors
 * --------------------------------------------------------
 **/
SFrame::SFrame(SIFrame&& f) 
: Super(std::move(f.Shrink())) {
    f.Reset();
}
SFrame::SFrame(SOFrame&& f) 
: Super(std::move(f.Shrink())) {
    f.Reset();
}
SFrame::SFrame(SIOFrame&& f) 
: Super(std::move(f.Shrink())) {
    f.Reset();
}
SFrame::SFrame(const SIFrame& f) 
: Super(std::move(SIFrame(f).Shrink())) {
}
SFrame::SFrame(const SOFrame& f) 
: Super(std::move(SOFrame(f).Shrink())) {
}
SFrame::SFrame(const SIOFrame& f) 
: Super(std::move(SIOFrame(f).Shrink())) {
}
/**
 * ----------------------------------------------------------------------------
 * SIFrame
 * ----------------------------------------------------------------------------
 * constructors
 * --------------------------------------------------------
 **/
SIFrame::SIFrame() 
: SFrame(), __end(Super::end()) { 
}
SIFrame::SIFrame(SFrame&& f)
: SFrame(std::forward<SFrame>(f)), __end(Super::end()) {
}
SIFrame::SIFrame(SIFrame&& f)
: SFrame(std::forward<SFrame>(f)), __end(f.end()) {
    f.Reset();
}
SIFrame::SIFrame(SOFrame&& f)
: SFrame(std::forward<SFrame>(f)), __end(f.end()) {
    f.Reset();
}
SIFrame::SIFrame(SIOFrame&& f)
: SFrame(std::forward<SFrame>(f)), __end(f.end()) {
    f.Reset();
}
SIFrame::SIFrame(const SFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __end(Super::end()) {
}
SIFrame::SIFrame(const SIFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __end(std::prev(Super::end(), f.Size())) {
}
SIFrame::SIFrame(const SOFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __end(std::next(Super::begin(), f.Size())) {
}
SIFrame::SIFrame(const SIOFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __end(std::next(Super::begin(), f.OSize())) {
}
/**
 * ----------------------------------------------------------------------------
 * SOFrame
 * ----------------------------------------------------------------------------
 * constructors
 * --------------------------------------------------------
 **/
SOFrame::SOFrame()
: SFrame(), __beg(begin()) {
}    
SOFrame::SOFrame(SFrame&& f)
: SFrame(std::move(f)), __beg(begin()) {
}
SOFrame::SOFrame(SIFrame&& f)
: SFrame(std::move(f)), __beg(f.begin()) {
    f.Reset();
}    
SOFrame::SOFrame(SOFrame&& f)
: SFrame(std::move(f)), __beg(f.begin()) {
    f.Reset();
}    
SOFrame::SOFrame(SIOFrame&& f)
: SFrame(std::move(f.IShrink())), __beg(f.begin()) {
    f.Reset();
}    
SOFrame::SOFrame(const SFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __beg(begin()) {   
}
SOFrame::SOFrame(const SIFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __beg(std::prev(end(), f.Size())) {   
}
SOFrame::SOFrame(const SOFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __beg(std::next(begin(), f.Size())) {   
}
/**
 * ----------------------------------------------------------------------------
 * SIOFrame
 * ----------------------------------------------------------------------------
 * constructors
 * --------------------------------------------------------
 **/
SIOFrame::SIOFrame() 
: SFrame(), __beg(begin()), __end(begin()) { 
}
SIOFrame::SIOFrame(SFrame&& f)
: SFrame(std::forward<SFrame>(f)), __beg(begin()), __end(end()) {
}
SIOFrame::SIOFrame(SIOFrame&& f)
: SFrame(std::forward<SFrame>(f)), __beg(f.__beg), __end(f.__end) {
    f.Reset();
}

// SIOFrame::SIOFrame(SIOFrame&& f)
// : SFrame(std::forward<SFrame>(f)), __it(f.__it) {
//     f.Reset();
// }
SIOFrame::SIOFrame(const SFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), 
__beg(begin()), 
__end(end()) {}

SIOFrame::SIOFrame(const SIOFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), 
__beg(std::prev(end(), f.ISize() + f.OSize())), 
__end(std::prev(end(), f.ISize())) {}
// SIOFrame::SIOFrame(const SIOFrame& f)
// : SFrame(f.capacity(), f.begin(), f.end()), __it(std::next(begin(), f.Size())) {
// }
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 **/