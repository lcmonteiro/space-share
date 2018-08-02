/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
/**
 */
#include <string>
/**
 * JNI interface
 */
#include "NetShareJNI.h"
/*---------------------------------------------------------------------------------------------------------------------*
 * container
 *---------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------*
 * std C functions
 *---------------------------------------------------------------------------------------------------------------------*/
extern "C" {
	/*-------------------------------------------------------------------------------------------------------------*
	 * converters
	 *-------------------------------------------------------------------------------------------------------------*/
        inline std::string toString(JNIEnv* env, jstring prompt);
	/*-------------------------------------------------------------------------------------------------------------*
	 * interfaces
	 *-------------------------------------------------------------------------------------------------------------*/
	JNIEXPORT jboolean JNICALL Java_NetShare_NetShare_Open(
                JNIEnv * env, jobject obj, jstring location, jstring password, jint id, jint ref
        ) {
                return true;
	}
	/**
	 */
	JNIEXPORT jfloat JNICALL Java_NetShare_NetShare_Good(JNIEnv * env, jobject obj, jint id) {
		return 0.0;
	}
	/**
	 */
	JNIEXPORT jboolean JNICALL Java_NetShare_NetShare_Close(JNIEnv * env, jobject obj, jint id) {
                return true;
	}
#ifdef __LOG_SSTREAM__
	/**
	 */
	JNIEXPORT jbyteArray JNICALL Java_NetShare_NetShare_Log(JNIEnv * env, jobject obj) {
		return toByteArray(env, GetLog());
	}
#endif
	/*-------------------------------------------------------------------------------------------------------------*
	 * converters
	 *-------------------------------------------------------------------------------------------------------------*/
	std::string toString(JNIEnv* env, jstring prompt){
                const char *str = env->GetStringUTFChars(prompt, 0);
                std::string out(str);
                env->ReleaseStringUTFChars(prompt, str);
                return out;
        }
}