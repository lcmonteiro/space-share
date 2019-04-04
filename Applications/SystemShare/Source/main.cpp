/*
 * File:   main.cpp
 * Author: Luis Monteiro
 *
 * Created on December 8, 2015, 11:48 PM
 */
#include <getopt.h>
#include <libgen.h>
#include <signal.h>
/**
 */
#include <cmath>
#include <cstdlib>
#include <cstring>
/**
 */
#include <chrono>
#include <fstream>
#include <iostream>
/**
 * Share Interface
 */
#include "SMachine.h"
/**
 */
using namespace std;
/*---------------------------------------------------------------------------------------------------------------------*
 * help
 *---------------------------------------------------------------------------------------------------------------------*/
#define USAGE(os) do{                                                                               \
    os << "USAGE:"<< endl;                                                                          \
    os << "\t" << basename(argv[0])    << " "                                                       \
    <<"[options] (-i --type=TYPE --uri=PATH [options])...(-o --type=TYPE --uri=PATH [options])..."  \
    << endl;                                                                                        \
    os << endl;                                                                                     \
    os << "OPTIONS:"<< endl;                                                                        \
    os << "\t" << "-L, --loading" << endl;                                                          \
    os << "\t" << "-S, --saving" << endl;                                                           \
    os << "\t" << "-E, --encode" << endl;                                                           \
    os << "\t" << "-D, --decode" << endl;                                                           \
    os << "\t" << "-Y, --ypsilon" << endl;                                                          \
    os << "\t" << "-T, --tpsilon" << endl;                                                          \
    os << "\t" << "-I, --input " << endl;                                                           \
    os << "\t" << "-O, --output" << endl;                                                           \
    os << "\t" << "-t, --type      =TYPE    (udp | dir]" << endl;                                   \
    os << "\t" << "-u, --uri      =PATH    path of resource" << endl;                               \
    os << "\t" << "-s, --slice-size       =VALUE   number of bytes "<< endl;                        \
    os << "\t" << "-f, --frame-size       =VALUE   number of bytes"<< endl;                         \
    os << "\t" << "-p, --pack-size    =VALUE   number of frames"<< endl;                            \
    os << "\t" << "-c, --cache-size       =VALUE   number of (packs)"<< endl;                       \
    os << "\t" << "-c, --break      =VALUE   number of (streams)"<< endl;                           \
    os << "\t" << "-r, --redundancy      =VALUE   number of redundancy(frames)"<< endl;             \
    os << "\t" << "-l, --lifetime      =VALUE   life quantity (in cyles)"<< endl;                   \
    os << "\t" << "--, --lifes      =VALUE   life quantity (in lifetime cyles)"<< endl;             \
    os << "\t" << "--, --local        =PATH    local path of resource"<< endl;                      \
    os << "\t" << "--, --name         =NAME    name of resource"<< endl;                            \
    os << "\t" << "--, --timeout      =TIME    data resouce(s) timeout "<< endl;                    \
    os << "\t" << "--, --sleep      =TIME    data resouce(s) sleep "<< endl;                        \
    os << "\t" << "--, --delay        =TIME    data resouce(s) delay "<< endl;                      \
    os << "\t" << "--, --period       =TIME    process quantity (in cyles)  "<< endl;               \
    os << "\t" << "--, --pass      =STRING  password "<< endl;                                      \
    os << "\t" << "--, --verbose      =LEVEL   data resouce(s) log level"<< endl;                   \
    os << "STREAMS:"<< endl;                                                                        \
    os << "\t" << "-e, -i udp -r PATH []"<< endl;                                                   \
    os << "AUTHOR:"<< endl;                                                                         \
    os << "\t" << "Luis Monteiro <monteiro.lcm@gmail.com>"<< endl;                                  \
} while(0)


#include <SVariable.h>
/**--------------------------------------------------------------------------------------------------------------------*
 * main
 *---------------------------------------------------------------------------------------------------------------------*/
static void stop(int sig) {
    exit(sig);
}
static void Null(int sig) {
}
int main(int argc, char** argv) {    
    srand(time(NULL));      
    /**------------------------------------------------------------------------------------------------------------*
     * signals
     *-------------------------------------------------------------------------------------------------------------*/
    signal(SIGPIPE, SIG_IGN);
    signal(SIGTERM, stop);
    signal(SIGINT, stop);
    /**------------------------------------------------------------------------------------------------------------*
     * process
     *-------------------------------------------------------------------------------------------------------------*/
    STask::Enable();
    /**
     * configure machine
     */
    SMachine m("system.share", {{
        {"M", {{
            { "uri",  "encoder"},
            { "type", "encode"},
            { "verbose", "4"}
        }}},
        {"F", {{
            {"type", "message"},
            { "verbose", "4"}
        }}},
        {"I", {{
            { "uri",  "127.0.0.1:1357"},
            { "type", "message.udp"},
            { "verbose", "4"}
        }}},
        {"O",{
            { 
                { "uri",  "/tmp/out.1"},
                { "type", "message.file"}
            },
            {
                { "uri",  "/tmp/out.2"},
                { "type", "message.file"}
            },
            {
                { "uri",  "/tmp/out.3"},
                { "type", "message.file"}
            }
        }}
    }});

    
    // SMachine m("system.share", { 
        
    //     Module::Config {
    //         Module::Base {
    //             { "uri",  "encoder"},
    //             { "type", "encode"},
    //             { "verbose", "4"}
    //         },
    //         Module::Function {
    //             {"type", "message"},
    //             { "verbose", "4"}
    //         },
    //         Module::Inputs {
    //             Module::Input {
    //                 { "uri",  "127.0.0.1:1357"},
    //                 { "type", "message.udp"},
    //                 { "verbose", "4"}
    //             }
    //         },
    //         Module::Outputs {
    //             Module::Output { 
    //                 { "uri",  "/tmp/out.1"},
    //                 { "type", "message.file"}
    //             },
    //             Module::Output {
    //                 { "uri",  "/tmp/out.2"},
    //                 { "type", "message.file"}
    //             },
    //             Module::Output {
    //                 { "uri",  "/tmp/out.3"},
    //                 { "type", "message.file"}
    //             }
    //         }
    //     }
    // });
    /**
     * run machine
     */
    while (m.process(chrono::seconds(10))) {
        cout << m.good() << endl;
    }
    /**
     */
    STask::Sleep(chrono::milliseconds(1));
    return -1;
}
