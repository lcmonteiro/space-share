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
 **/
template<>
SFrame& SFrame::operator=(SIFrame&& f) {
    return *this;
}
template<>
SFrame& SFrame::operator=(const SIFrame& f) {
    return *this;
}

template<>
SIFrame& SIFrame::operator=(Frame&& f) {
    *this = SIFrame(std::move(f));
}
template<>
SIFrame& SIFrame::operator=(const Frame& f) {
    *this = SIFrame(f);
}
template<>
SOFrame& SOFrame::operator=(Frame&& f) {
    *this = SOFrame(std::move(f));
}
template<>
SOFrame& SOFrame::operator=(const Frame& f) {
    *this = SOFrame(f);
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 **/