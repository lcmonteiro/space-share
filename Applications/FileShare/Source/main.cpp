/*
 * File:   main.cpp
 * Author: Luis Monteiro
 *
 * Created on December 8, 2015, 11:48 PM
 */
#include <cmath>
#include <cstdlib>
#include <getopt.h>
#include <libgen.h>
#include <signal.h>
/**
 */
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
/**
 */
#include "Sinterface/SStreamCodec.h"
#include "Skernel/SHash.h"
/**
 */
using namespace std;
/*---------------------------------------------------------------------------------------------------------------------*
 * help
 *---------------------------------------------------------------------------------------------------------------------*/
#define USAGE(os) do{													\
	os << "USAGE:"<< endl;												\
	os << "\t" << basename(argv[0])	<< " "										\
		<<"[-E|-D] --uri=ID --size=SIZE (-I --uri=ID --size=SIZE)...(-O --uri=ID --size=SIZE)..."               \
	<< endl;													\
	os << endl;													\
	os << "OPTIONS:"<< endl;											\
	os << "\t" << "-E, --encode" << endl;										\
	os << "\t" << "-D, --decode" << endl;										\
	os << "\t" << "-I, --input " << endl;										\
	os << "\t" << "-O, --output" << endl;										\
	os << "\t" << "-u, --uri    =ID     file path or signature" << endl;                                            \
	os << "\t" << "-s, --size   =SIZE   number of slices "<< endl;                                                  \
	os << "AUTHOR:"<< endl;												\
	os << "\t" << "Luis Monteiro <monteiro.lcm@gmail.com>"<< endl;							\
}while(0)
/*---------------------------------------------------------------------------------------------------------------------*
 * options
 *---------------------------------------------------------------------------------------------------------------------*/
static struct option options[] = {
	{"encode", no_argument, 0, 'E'},
	{"decode", no_argument, 0, 'D'},
	{"input", no_argument, 0, 'I'},
	{"output", no_argument, 0, 'O'},
	{"uri", required_argument, 0, 'u'},
	{"size", required_argument, 0, 's'},
	{0, 0, 0, 0}
};
/**--------------------------------------------------------------------------------------------------------------------*
 * get options
 *---------------------------------------------------------------------------------------------------------------------*/
struct option* getoption(int opt, int index) {
	if (index) {
		return &options[index];
	}
	for (auto& o :options) {
		if (o.val == opt) {
			return &o;
		}
	}
	return nullptr;
}
/**--------------------------------------------------------------------------------------------------------------------*
 * main
 *---------------------------------------------------------------------------------------------------------------------*/
static void stop(int sig) {
        exit(sig);
}
int main(int argc, char** argv) {
        typedef enum {ENCODE, DECODE, NONE} code_t;
        /**------------------------------------------------------------------------------------------------------------*
         * signals
         *-------------------------------------------------------------------------------------------------------------*/
        srand(time(NULL));
        /**------------------------------------------------------------------------------------------------------------*
         * signals
         *-------------------------------------------------------------------------------------------------------------*/
        signal(SIGPIPE, SIG_IGN);
        signal(SIGTERM, stop);
        signal(SIGINT, stop);
        /**------------------------------------------------------------------------------------------------------------*
         * parse arguments
         *-------------------------------------------------------------------------------------------------------------*/
        auto cod = NONE;
        auto cur = make_shared<map<string, size_t>>();
        auto def = make_shared<map<string, size_t>>();
        auto inn = make_shared<map<string, size_t>>();
        auto out = make_shared<map<string, size_t>>();
        auto elm = make_pair<string, size_t>("", 0);
	for (int opt = '\0', i = 0; (opt = getopt_long(argc, argv, "EDIOu:s:", options, &i)) != -1; i = 0) {
		switch (opt) {
                        // encode/decode
			case 'E': cur->insert(move(elm)); cur = def; cod = ENCODE; break;
			case 'D': cur->insert(move(elm)); cur = def; cod = DECODE; break;
                        // input/output
                        case 'O': cur->insert(move(elm)); cur = out;  break;
                        case 'I': cur->insert(move(elm)); cur = inn;  break;
                        // values
                        case 'u': elm.first  = optarg;       break;
                        case 's': elm.second = atoi(optarg); break;
                        // error
                        default: USAGE(cerr);return -1;
                }
        }
        cur->insert(move(elm));
        /**------------------------------------------------------------------------------------------------------------*
         * open
         *-------------------------------------------------------------------------------------------------------------*/
        vector<pair<size_t, ifstream>> i;
        vector<pair<size_t, ofstream>> o;
        //
        for(auto e : *inn){
                i.emplace_back(e.second, ifstream(e.first));
        }
        for(auto e : *out){
                o.emplace_back(e.second, ofstream(e.first));
        }
        /**------------------------------------------------------------------------------------------------------------*
         * process
         *-------------------------------------------------------------------------------------------------------------*/
        switch (cod) {
                case ENCODE:
                {
                        SStreamCodec::Encode<ifstream, ofstream>(
                                move(i.front().second), move(o), def->begin()->second, SHash::Digest(def->begin()->first)
                        );
                        break;
                }
                case DECODE:
                {
                        SStreamCodec::Decode<ifstream, ofstream>(
                                move(i), move(o.front().second), def->begin()->second, SHash::Digest(def->begin()->first)
                        );
                        break;
                }
                default:
                {
                        USAGE(cerr);
                }
        }
        return 0;
}
