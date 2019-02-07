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
template<>
SFrame::SFrame(SIFrame& f) 
: Super(std::move(SIFrame(f).Shrink().__frame)) {
}


/**
 * --------------------------------------------------------
 * operatores
 * --------------------------------------------------------
 **/
template<>
SFrame& SFrame::operator=(SIFrame&& f) {
    f.Shrink();
    *this = std::move(f.__frame);
    f.Reset();
    return *this;
}
template<>
SFrame& SFrame::operator=(const SIFrame& f) {
    *this = std::move(SIFrame(f).Shrink().__frame);
    return *this;
}
template<>
SFrame& SFrame::operator=(SOFrame&& f) {
    f.Shrink();
    *this = std::move(f.__frame);
    f.Reset();
    return *this;
}
template<>
SFrame& SFrame::operator=(const SOFrame& f) {
    *this = std::move(SOFrame(f).Shrink().__frame);
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * SIFrame
 * ----------------------------------------------------------------------------
 * constructors
 * --------------------------------------------------------
 **/
/**
 * --------------------------------------------------------
 * operatores
 * --------------------------------------------------------
 **/

/**
 * ----------------------------------------------------------------------------
 * SOFrame
 * ----------------------------------------------------------------------------
 * constructors
 * --------------------------------------------------------
 **/
// template<>
// SOFrame::SOFrame(SFrame&& f)
// : __frame(std::move(f)), __it(__frame.begin()) {
// }
// template<>
// SOFrame::SOFrame(const SFrame& f)
// : __frame(f), __it(__frame.begin()) {
// }
/**
 * --------------------------------------------------------
 * operatores
 * --------------------------------------------------------
 **/
// template<>
// SOFrame& SOFrame::operator=(Frame&& f) {
//     *this = SOFrame(std::move(f));
// }
// template<>
// SOFrame& SOFrame::operator=(Frame& f) {
//     *this = SOFrame(f);
// }
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 **/