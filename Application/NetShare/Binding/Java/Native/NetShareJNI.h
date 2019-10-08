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
#include "NetMachine.h"
/**
 * 
 */
#ifndef NETSHAREJNI_H
#define NETSHAREJNI_H

extern "C" {
        /*
         * Class:     netshare_NetShare
         * Method:    Init
         * Signature: (II)Z
         */
        JNIEXPORT jboolean JNICALL Java_com_share_cwrapper_netshare_NetShare_Init(
                JNIEnv * env, jobject obj
        );
        /*
         * Class:     netshare_NetShare
         * Method:    Open
         * Signature: (II)Z
         */
        JNIEXPORT jboolean JNICALL Java_com_share_cwrapper_netshare_NetShare_Open(
                JNIEnv *, jobject, jstring, jstring, jint, jint
        );
         /*
         * Class:     netshare_NetShare
         * Method:    Good
         * Signature: (II)Z
         */
        JNIEXPORT jfloat JNICALL Java_com_share_cwrapper_netshare_NetShare_Good(
                JNIEnv *, jobject, jint
        );
        /*
         * Class:     netshare_NetShare
         * Method:    Close
         * Signature: (II)Z
         */
        JNIEXPORT jboolean JNICALL Java_com_share_cwrapper_netshare_NetShare_Close(
                JNIEnv *, jobject, jint
        );
#ifdef __LOG_SSTREAM__
        /*
         * Class:     NetShare_NetShare   
         * Method:    Log
         * Signature: (II)Z
         */
        JNIEXPORT jbyteArray JNICALL Java_com_share_cwrapper_netshare_NetShare_Log(
                JNIEnv *, jobject
        );
#endif
}
#endif /* NETSHAREJNI_H */

