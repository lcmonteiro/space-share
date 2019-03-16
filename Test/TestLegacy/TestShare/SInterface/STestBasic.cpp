/* 
 * File:   STestBasic.h
 * Author: Luis Monteiro
 *
 * Created on September 26, 2015, 11:20 AM
 */
#include <string>
#include <iostream>
/**
 */
#include "STestBasic.h"
/**
 */
using namespace std;
/**
 * test
 */
int STestBasic::operator()(int iterations, int frameSize, int redundancy, int minBufferSize, int maxBufferSize) {
        int s = 0;
        for (auto i = 0; i < iterations; ++i) {
                OBufferShare enc;
                IBufferShare dec;
                /**
                 *  
                 */
                Frame in = Random(minBufferSize, maxBufferSize);
                cout << "[IN>>]" << in << endl;
                /**
                 *  
                 */
                for (int i = 0,  n = enc.Set(in, frameSize, redundancy); i < n; ++i) {
                        auto coded = enc.Get();
                        /**
                         * 
                         */
                        cout << "[>>PHY>>]" << coded << endl;
                        /*
                         */
                        if (dec.Set(coded)) {
                                Frame out = dec.Get();
                                cout << "[>>OUT]" << out << endl;
                                /** 
                                 */
                                if (in == out) {
                                        cout << "[SUCCESS] " << ++s << endl;
                                } else {
                                        cout << "[FAIL]" << endl;
                                }
                                break;
                        }
                }
        }
        cout << "[SUCCESS] " << s << endl;
        return s;
}

Frame STestBasic::Random(int min, int max) {
        Frame buf;
        buf.reserve(min + (rand() % (max - min)));
        for (int i = 0; i < buf.capacity(); ++i) {
                buf.push_back(Frame::value_type(rand()));
        }
        return buf;
}