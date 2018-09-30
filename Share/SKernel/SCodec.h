/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCodec.h
 * Author: Luis Monteiro
 *
 * Created on January 10, 2017, 10:08 AM
 */

#ifndef SCODECI_H
#define SCODECI_H
/**
 */
#include "SCodecV1/SCodecDecoder.h"
#include "SCodecV1/SCodecEncoder.h"
#include "SCodecV1/SCodecStamp.h"
/**
 */
typedef v1::SCodecEncoder	CodecEncoder;
typedef v1::SCodecDecoder   CodecDecoder;
typedef v1::SCodecStamp 	CodecStamp;
typedef v1::SCodec    		Codec;
typedef v1::Stamp    		Stamp;
typedef v1::StampReference  StampReference;
/**
 */
#endif /* SCODECI_H */

