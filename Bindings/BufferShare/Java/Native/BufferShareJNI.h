/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <jni.h>
/* 
 * File:   ShareJNI.h
 * Author: Luis Monteiro
 *
 * Created on October 30, 2016, 4:22 PM
 */
#include "SBufferShare.h"
/**
 * 
 */
#ifndef BUFFERSHAREJNI_H
#define BUFFERSHAREJNI_H

extern "C" {
        /*
         * Class:     BufferSharee_BufferShare
         * Method:    Open
         * Signature: (II)Z
         */
        JNIEXPORT jboolean JNICALL Java_com_share_cwrapper_buffershare_BufferShare_Open(
                JNIEnv *, jobject, jint, jint
        );
        /*
         * Class:     BufferShare_BufferShare
         * Method:    Encode
         * Signature: ([BII)I
         */
        JNIEXPORT jint JNICALL Java_com_share_cwrapper_buffershare_BufferShare_Encode(
                JNIEnv *, jobject, jbyteArray, jint, jint
        );
        /*
         * Class:     BufferShare_BufferShare
         * Method:    GetFrame
         * Signature: (I)[B
         */
        JNIEXPORT jbyteArray JNICALL Java_com_share_cwrapper_buffershare_BufferShare_GetFrame(
                JNIEnv *, jobject, jint
        );
        /*
         * Class:     BufferShare_BufferShare
         * Method:    SetFrame
         * Signature: ([BI)Z
         */
        JNIEXPORT jboolean JNICALL Java_com_share_cwrapper_buffershare_BufferShare_SetFrame(
                JNIEnv *, jobject, jbyteArray, jint
        );
        /*
         * Class:     BufferShare_BufferShare
         * Method:    Decode
         * Signature: (I)[B
         */
        JNIEXPORT jbyteArray JNICALL Java_com_share_cwrapper_buffershare_BufferShare_Decode(
                JNIEnv *, jobject, jint
        );
        /*
         * Class:     BufferShare_BufferShare
         * Method:    Close
         * Signature: (II)Z
         */
        JNIEXPORT jboolean JNICALL Java_com_share_cwrapper_buffershare_BufferShare_Close(
                JNIEnv *, jobject, jint, jint
        );
}
#endif /* BUFFERSHAREJNI_H */

