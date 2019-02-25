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
SFrame::SFrame(const SIFrame& f) 
: Super(std::move(SIFrame(f).Shrink())) {
}
SFrame::SFrame(const SOFrame& f) 
: Super(std::move(SOFrame(f).Shrink())) {
}
/**
 * ----------------------------------------------------------------------------
 * SIFrame
 * ----------------------------------------------------------------------------
 * constructors
 * --------------------------------------------------------
 **/
SIFrame::SIFrame() 
: SFrame(), __it(end()) { 
}
SIFrame::SIFrame(SFrame&& f)
: SFrame(std::forward<SFrame>(f)), __it(end()) {
}
SIFrame::SIFrame(SIFrame&& f)
: SFrame(std::forward<SFrame>(f)), __it(f.__it) {
    f.Reset();
}
SIFrame::SIFrame(SOFrame&& f)
: SFrame(std::forward<SFrame>(f)), __it(f.__it) {
    f.Reset();
}
SIFrame::SIFrame(const SFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __it(end()) {
}
SIFrame::SIFrame(const SIFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __it(std::prev(end(), f.Size())) {
}
SIFrame::SIFrame(const SOFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __it(std::next(begin(), f.Size())) {
}
/**
 * ----------------------------------------------------------------------------
 * SOFrame
 * ----------------------------------------------------------------------------
 * constructors
 * --------------------------------------------------------
 **/
SOFrame::SOFrame()
: SFrame(), __it(begin()) {
}    
SOFrame::SOFrame(SFrame&& f)
: SFrame(std::move(f)), __it(begin()) {
}
SOFrame::SOFrame(SIFrame&& f)
: SFrame(std::move(f)), __it(f.__it) {
    f.Reset();
}    
SOFrame::SOFrame(SOFrame&& f)
: SFrame(std::move(f)), __it(f.__it) {
    f.Reset();
}    
SOFrame::SOFrame(const SFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __it(begin()) {   
}
SOFrame::SOFrame(const SIFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __it(std::prev(end(), f.Size())) {   
}
SOFrame::SOFrame(const SOFrame& f)
: SFrame(f.capacity(), f.begin(), f.end()), __it(std::next(begin(), f.Size())) {   
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 **/