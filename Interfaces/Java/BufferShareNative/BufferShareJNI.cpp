/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
/**
 */
#include <map>
/**
 * JNI interface
 */
#include "BufferShareJNI.h"
/*---------------------------------------------------------------------------------------------------------------------*
 * definitions
 *---------------------------------------------------------------------------------------------------------------------*/
typedef enum {
        ENCODER, DECODER
} Type;
/*---------------------------------------------------------------------------------------------------------------------*
 * container
 *---------------------------------------------------------------------------------------------------------------------*/
static std::map<uint32_t, OBufferShare> __encoder;
static std::map<uint32_t, IBufferShare> __decoder;
/*---------------------------------------------------------------------------------------------------------------------*
 * std C functions
 *---------------------------------------------------------------------------------------------------------------------*/
extern "C" {
        /*-------------------------------------------------------------------------------------------------------------*
         * converters
         *-------------------------------------------------------------------------------------------------------------*/
        inline Frame toFrame(JNIEnv*& env, jbyteArray& data);
        /**/
        inline jbyteArray toByteArray(JNIEnv*& env, const Frame& data);
        /*-------------------------------------------------------------------------------------------------------------*
         * interfaces
         *-------------------------------------------------------------------------------------------------------------*/
        JNIEXPORT jboolean JNICALL Java_com_share_cwrapper_buffershare_BufferShare_Open(
                JNIEnv * env, jobject obj, jint coder, jint id
        ) {
                switch (coder) {
                        case ENCODER: return __encoder.emplace(
                                std::piecewise_construct,std::forward_as_tuple(id), std::forward_as_tuple()).second;
                        case DECODER: return __decoder.emplace(
                                std::piecewise_construct,std::forward_as_tuple(id), std::forward_as_tuple()).second;
                }
                return false;
        }
        /**
         */
        JNIEXPORT jint JNICALL Java_com_share_cwrapper_buffershare_BufferShare_Encode(
                JNIEnv * env, jobject obj, jbyteArray data, jint size, jint id
        ) {
                return __encoder[id].Set(toFrame(env, data), static_cast<size_t>(size));
        }
        /**
         */
        JNIEXPORT jbyteArray JNICALL Java_com_share_cwrapper_buffershare_BufferShare_GetFrame(
                JNIEnv * env, jobject obj, jint id
        ) {
                return toByteArray(env, __encoder[id].Get());
        }
        /**
         */
        JNIEXPORT jboolean JNICALL Java_com_share_cwrapper_buffershare_BufferShare_SetFrame(
                JNIEnv * env, jobject obj, jbyteArray data, jint id
        ) {
                return __decoder[id].Set(toFrame(env, data));
        }
        /**
         */
        JNIEXPORT jbyteArray JNICALL Java_com_share_cwrapper_buffershare_BufferShare_Decode(
                JNIEnv * env, jobject obj, jint id
        ) {
                return toByteArray(env, __decoder[id].Get());
        }
        /**
         */
        JNIEXPORT jboolean JNICALL Java_com_share_cwrapper_buffershare_BufferShare_Close(
                JNIEnv * env, jobject obj, jint coder, jint id
        ) {
                switch (coder) {
                        case ENCODER: __encoder.erase(id); return true;
                        case DECODER: __decoder.erase(id); return true;
                }
                return false;
        }
        /*-------------------------------------------------------------------------------------------------------------*
         * converters
         *-------------------------------------------------------------------------------------------------------------*/
        Frame toFrame(JNIEnv*& env, jbyteArray& array){
                jsize len = env->GetArrayLength(array);
                jbyte*body = env->GetByteArrayElements(array, 0);
                Frame out(reinterpret_cast<uint8_t*>(body), reinterpret_cast<uint8_t*>(body) + static_cast<size_t>(len)); 
                env->ReleaseByteArrayElements(array, body, 0);
                return out;
        }
        jbyteArray toByteArray(JNIEnv*& env, const Frame& buf){
                jbyteArray ret = env->NewByteArray(buf.size());
                env->SetByteArrayRegion (ret, 0, buf.size(), reinterpret_cast<const jbyte*>(buf.data()));
                return ret;
        }
}