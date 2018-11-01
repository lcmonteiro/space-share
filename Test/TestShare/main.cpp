/* 
 * File:   main.cpp
 * Author: monteiro
 *
 * Created on September 26, 2016, 10:21 AM
 */
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <iostream>
/**
 */
#include "Sinterface/STestBasic.h"
/**
 */
using namespace std;
/*
 * 
 */
int main(int argc, char** argv) {
        /**
         * test basic interface
         */
        STestBasic test;
        test(
                100,            //iterations
                20,             //frameSize
                0,              //redundancy
                20,             //minBufferSize
                200             //maxBufferSize        
        );
        /**
         */
        cout.flush();
        sleep(4);
        return 0;
}

