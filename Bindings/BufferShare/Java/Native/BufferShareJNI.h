/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   BufferShareJNI.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef BUFFERSHAREJNI_H
#define BUFFERSHAREJNI_H
/**
 * external
 */
#include <jni.h>
/** 
 * internal
 */
#include "SBufferShare.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Interfaces
 * ------------------------------------------------------------------------------------------------
 */
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
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* BUFFERSHAREJNI_H */

