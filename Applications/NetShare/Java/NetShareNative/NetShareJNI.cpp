/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
/**
 */
#include <map>
#include <csignal>
/**
 * JNI interface
 */
#include "NetShareJNI.h"
/**
 */
#include "Skernel/SLog.h"
/*---------------------------------------------------------------------------------------------------------------------*
 * container
 *---------------------------------------------------------------------------------------------------------------------*/
static std::map<uint32_t, NetMachine> __networks;
/*---------------------------------------------------------------------------------------------------------------------*
 * std C functions
 *---------------------------------------------------------------------------------------------------------------------*/
extern "C" {
        /*-------------------------------------------------------------------------------------------------------------*
         * debug
         *-------------------------------------------------------------------------------------------------------------*/
#ifdef __ANDROID__
        void print_backtrace(int sig) {
                raise(SIGINT);
        }
#else
        void print_backtrace(int sig) {
                raise(SIGINT);
        }
#endif
        /*-------------------------------------------------------------------------------------------------------------*
         * converters
         *-------------------------------------------------------------------------------------------------------------*/
        inline Frame toFrame(JNIEnv*& env, jbyteArray& data);
        /**/
        inline string toString(JNIEnv* env, jstring prompt);
        /**/
        inline jbyteArray toByteArray(JNIEnv*& env, const Frame& data);
        /*-------------------------------------------------------------------------------------------------------------*
         * interfaces
         *-------------------------------------------------------------------------------------------------------------*/
        JNIEXPORT jboolean JNICALL Java_com_share_cwrapper_netshare_NetShare_Init(
                JNIEnv * env, jobject obj
        ) {
                STask::Enable();
                return true;
        }
        /**
         */
        JNIEXPORT jboolean JNICALL Java_com_share_cwrapper_netshare_NetShare_Open(
                JNIEnv * env, jobject obj, jstring location, jstring password, jint id, jint ref
        ) {
                return __networks.emplace(std::piecewise_construct,
                        std::forward_as_tuple(id),
                        std::forward_as_tuple(toString(env, location), toString(env, password), id, ref)
                ).second;
        }
        /**
         */
        JNIEXPORT jfloat JNICALL Java_com_share_cwrapper_netshare_NetShare_Good(
                JNIEnv * env, jobject obj, jint id
        ) {
                return __networks.at(id).Good();
        }
        /**
         */
        JNIEXPORT jboolean JNICALL Java_com_share_cwrapper_netshare_NetShare_Close(
                JNIEnv * env, jobject obj, jint id
        ) {
                PRINT("%s:%d", __func__, __LINE__);
                __networks.erase(id);
                PRINT("%s:%d", __func__, __LINE__);
                return true;
//                return __networks.erase(id) > 0;
                
        }
#ifdef __LOG_SSTREAM__
        /**
         */
        JNIEXPORT jbyteArray JNICALL Java_com_share_cwrapper_netshare_NetShare_Log(
                JNIEnv * env, jobject obj
        ) {
                return toByteArray(env, GetLog());
        }
#endif
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
        string toString(JNIEnv* env, jstring prompt){
                const char *str = env->GetStringUTFChars(prompt, 0);
                string out(str);
                env->ReleaseStringUTFChars(prompt, str);
                return out;
        }
        jbyteArray toByteArray(JNIEnv*& env, const Frame& buf){
                jbyteArray ret = env->NewByteArray(buf.size());
                env->SetByteArrayRegion (ret, 0, buf.size(), reinterpret_cast<const jbyte*>(buf.data()));
                return ret;
        }
}