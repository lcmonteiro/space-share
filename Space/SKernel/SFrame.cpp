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
 * ------------------------------------------------------------------------------------------------
 * convertions
 * ------------------------------------------------------------------------------------------------
 * SFrame
 * ----------------------------------------------------------------------------
 * operatores
 * --------------------------------------------------------
 **/
SFrame& SFrame::operator=(SIOFrame&& f) {
    return (*this = std::forward<SFrame>(f.Shrink()));
} 
SFrame& SFrame::operator=(const SIOFrame& f) {
    return (*this = std::forward<SFrame>(SIOFrame(f).Shrink()));
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
__end(Super::end()), __beg(Super::begin()) {}

SIOFrame::SIOFrame(SIOFrame&& f) 
: SFrame(std::forward<SFrame>(f)), 
__end(f.end()), __beg(f.begin()) {}

SIOFrame::SIOFrame(SFrame&& f)
: SFrame(std::forward<SFrame>(f)), 
__end(Super::end()), __beg(Super::begin()) {}

SIOFrame::SIOFrame(const SFrame& f) 
: SFrame(f.begin(), f.end()), 
__end(Super::end()), __beg(Super::begin()) {}

SIOFrame::SIOFrame(const SIOFrame& f) 
: SFrame(f.SFrame::begin(), f.Frame::end()), 
__end(std::prev(Super::end(), f.ISize())), __beg(std::prev(__end, f.OSize())) {}
/*
 * --------------------------------------------------------
 * operatores
 * --------------------------------------------------------
 **/
SIOFrame& SIOFrame::operator=(SFrame&& f) {
    return (*this = std::forward<SFrame>(f.Shrink()));
} 
SIOFrame& SIOFrame::operator=(SIOFrame&& f) {
    return (*this = std::forward<SFrame>(f.Shrink()));
} 
SIOFrame& SIOFrame::operator=(const SFrame& f) {
    return (*this = std::forward<SFrame>(SIOFrame(f).Shrink()));
}
SIOFrame& SIOFrame::operator=(const SIOFrame& f) {
    return (*this = std::forward<SFrame>(SIOFrame(f).Shrink()));
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 **/