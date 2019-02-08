/*
 * Container:   SFrame.cpp
 * Author: Luis Monteiro
 *
 * Created on February  2, 2019, 10:21 AM
 **
 * std 
 */
#include <iostream>
/** 
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
: Super(std::move(f.Shrink().__frame)) {
    f.Reset();
}
SFrame::SFrame(SOFrame&& f) 
: Super(std::move(f.Shrink().__frame)) {
    f.Reset();
}
SFrame::SFrame(const SIFrame& f) 
: Super(std::move(SIFrame(f).Shrink().__frame)) {
}
SFrame::SFrame(const SOFrame& f) 
: Super(std::move(SOFrame(f).Shrink().__frame)) {
}
/**
 * ----------------------------------------------------------------------------
 * SIFrame
 * ----------------------------------------------------------------------------
 * constructors
 * --------------------------------------------------------
 **/
SIFrame::SIFrame() 
: __frame(), __it(__frame.end()) { 
}
SIFrame::SIFrame(SFrame&& f)
: __frame(std::move(f)), __it(__frame.end()) {
}
SIFrame::SIFrame(SIFrame&& f)
: __frame(std::move(f.__frame)), __it(f.__it) {
    f.Reset();
}
SIFrame::SIFrame(SOFrame&& f)
: __frame(std::move(f.__frame)), __it(f.__it) {
    f.Reset();
}
SIFrame::SIFrame(const SFrame& f)
: __frame(f), __it(__frame.end()) {
}
SIFrame::SIFrame(const SIFrame& f)
: __frame(f.__frame), __it(std::prev(__frame.end(), f.Size())) {
}
SIFrame::SIFrame(const SOFrame& f)
: __frame(f.__frame), __it(std::prev(__frame.end(), f.Size())) {
}
/**
 * ----------------------------------------------------------------------------
 * SOFrame
 * ----------------------------------------------------------------------------
 * constructors
 * --------------------------------------------------------
 **/
SOFrame::SOFrame()
: __frame(), __it(__frame.begin()) {
}    
SOFrame::SOFrame(SFrame&& f)
: __frame(std::move(f)), __it(__frame.begin()) {
}
SOFrame::SOFrame(SIFrame&& f)
: __frame(std::move(f.__frame)), __it(f.__it) {
    f.Reset();
}    
SOFrame::SOFrame(SOFrame&& f)
: __frame(std::move(f.__frame)), __it(f.__it) {
    f.Reset();
}    
SOFrame::SOFrame(const SFrame& f)
: __frame(f), __it(__frame.begin()) {   
}
SOFrame::SOFrame(const SIFrame& f)
: __frame(f.__frame), __it(std::prev(__frame.end(), f.Size())) {   
}
SOFrame::SOFrame(const SOFrame& f)
: __frame(f.__frame), __it(std::prev(__frame.end(), f.Size())) {   
}

/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 **/