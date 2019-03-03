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
SIFrame::SIFrame(const SFrame& f)
: SFrame(f.Capacity(), f.begin(), f.end()), __end(Super::end()) {
    Expand();
}
SIFrame::SIFrame(const SIFrame& f)
: SFrame(f.Capacity(), f.begin(), f.end()), __end(Super::end()) {
    Expand();
}
/**
 * ----------------------------------------------------------------------------
 * SOFrame
 * ----------------------------------------------------------------------------
 * constructors
 * --------------------------------------------------------
 **/
SOFrame::SOFrame()
: SIFrame(), __beg(Super::begin()) {
}    
SOFrame::SOFrame(SFrame&& f)
: SIFrame(std::forward<SFrame>(f)), __beg(Super::begin()) {
}
SOFrame::SOFrame(SIFrame&& f)
: SIFrame(std::forward<SFrame>(f)), __beg(f.begin()) {
    f.Reset();
}    
SOFrame::SOFrame(SOFrame&& f)
: SIFrame(std::forward<SFrame>(f)), __beg(f.begin()) {
    f.Reset();
}        
SOFrame::SOFrame(const SFrame& f)
: SIFrame(SFrame(f.Capacity(), f.begin(), f.end())), __beg(Super::begin()) {   
}
SOFrame::SOFrame(const SIFrame& f)
: SIFrame(SFrame(f.Capacity(), f.begin(), f.end())), __beg(Super::begin()) {   
}
SOFrame::SOFrame(const SOFrame& f)
: SIFrame(Frame(f.Capacity(), f.begin(), f.end())), __beg(Super::begin()) {   
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 **/