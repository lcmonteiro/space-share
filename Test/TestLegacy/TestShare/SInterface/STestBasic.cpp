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
        for (int i = 0,  n = enc.set(in, frameSize, redundancy); i < n; ++i) {
            auto coded = enc.get();
            /**
             * 
             */
            cout << "[>>PHY>>]" << coded << endl;
            /**
             */
            if (dec.set(coded)) {
                Frame out = dec.get();
                cout << "[>>OUT]" << out << endl;
                /**
                 * verify
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
    auto buf = Frame(min + (rand() % (max - min)));
    for (int i = 0; i < buf.capacity(); ++i) {
        buf.push_back(Frame::value_type(rand()));
    }
    return buf;
}