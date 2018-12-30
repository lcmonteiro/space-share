/*
 * File:   SLocation.h
 * Author: Luis Monteiro
 *
 * Created on February 22, 2017, 10:34 PM
 */
#ifndef SLOCATION_H
#define SLOCATION_H
/**
 * std
 */
#include <system_error>
#include <thread>
#include <chrono>
#include <list>
#include <algorithm>
#include <random>
/**
 * space
 */
#include "SLinux/SLinuxTask.h"
/**
 */
using namespace std;
/*---------------------------------------------------------------------------------------------------------------------*
 * Exceptions
 *---------------------------------------------------------------------------------------------------------------------*/
typedef class SLocationException : public system_error {
public:
        /**
         * constructor
         */
        SLocationException(error_code ec) : system_error(ec) {
        }
        SLocationException(error_code ec, const string& what) : system_error(ec, what) {
        }
        /**
         * destructor
         */
        virtual ~SLocationException() = default;
} HandlerException;
/**
 */
template<class T>
class SLocationExceptionTIMEOUT : public SLocationException {
public:
        using SLocationException::SLocationException;
        /**
         * constructor
         */
        SLocationExceptionTIMEOUT() : SLocationException(make_error_code(errc::no_message)) {
        }
        SLocationExceptionTIMEOUT(const string& what) : SLocationException(make_error_code(errc::no_message), what) {
        }
};
/**
 */
template<class T>
class SLocationExceptionDETACHED : public SLocationException {
public:
        using SLocationException::SLocationException;
        /**
         * constructor
         */
        SLocationExceptionDETACHED() : SLocationException(make_error_code(errc::no_message)) {
        }
        SLocationExceptionDETACHED(const string& what) : SLocationException(make_error_code(errc::no_message), what) {
        }
};
/**
 */
template<class T>
class SLocationExceptionDEAD : public SLocationException {
public:
        using SLocationException::SLocationException;
        /**
         * constructor
         */
        SLocationExceptionDEAD() : SLocationException(make_error_code(errc::no_message)) {
        }
        SLocationExceptionDEAD(const string& what) : SLocationException(make_error_code(errc::no_message), what) {
        }
};
/*---------------------------------------------------------------------------------------------------------------------*
 * Handler
 *---------------------------------------------------------------------------------------------------------------------*/
template<class T>
class SLocation : public T {
public:
        /*-------------------------------------------------------------------------------------------------------------*
         * main interfaces
         *-------------------------------------------------------------------------------------------------------------*/
        /**
         * insert an object
         */
        void Insert(T obj) {
                __broken = obj;
        }
        /**
         * try to repair 
         */
        void Repair() {
                (*this)->Repair();
                Jump();
        }
        /**
         * update 
         */
        SLocation<T>& Update(chrono::milliseconds timeout) {
                using Clock = std::chrono::steady_clock;
                using Time = std::chrono::milliseconds;
                using Engine = std::default_random_engine;
                using Distribuition = std::uniform_int_distribution<>;
                /**
                 * waiting loop 
                 */
                Engine gen{random_device{}()};
                Distribuition dis{50, 500};
                for (auto now = Clock::now(), end = now + timeout; now < end; now = Clock::now()) {
                        if (*this) {
                                return *this;
                        }
                        if (!__broken) {
                                throw SLocationExceptionDETACHED<T>(string("hide"));
                        }
                        if (__broken->Good()) {
                                Jump();
                                return *this;
                        }
                        if (__broken->Inactive()) {
                                throw SLocationExceptionDEAD<T>(string("inactive"));
                        }
                        STask::Sleep(Time{1000});
                }
                /**
                 * timeout
                 */
                throw SLocationExceptionDETACHED<T>(string("timeout"));
        }
        /**
         * block all streams
         */
        void Close() {
                if (__hide) {
                        return;
                }
                if (*this) {
                        (*this)->Break();
                }
                if (__broken) {
                        __broken->Break();
                }
                swap(__hide, *this);
                //
                STask::Sleep(std::chrono::milliseconds(10));
        }
        /**
         * enable all streams
         */
        void Open() {
                if (*this) {
                        return;
                }
                if (__hide) {
                        __hide->Repair();
                }
                if (__broken) {
                        __broken->Repair();
                }
                swap(__hide, *this);
                //
                STask::Sleep(std::chrono::milliseconds(10));
        }
        /**
         * reset all streams
         */
        void Reset() {
                Close();
                STask::Sleep(std::chrono::milliseconds(10));
                Open();
                STask::Sleep(std::chrono::milliseconds(10));
        }

protected:
        /**
         * get revision
         */
        size_t revision() {
                return __rev;
        }
        /**
         * move between active and inactive
         */
        void Jump() {
                ++__rev; swap(__broken, *this);
        }
private:
        /**
         * hide resource
         */
        T __hide;
        /**
         * broken resource
         */
        T __broken;
        /**
         * Handler revision
         */
        size_t __rev;
};
#endif /* SLOCATION_H */

