/* 
 * File:   main.cpp
 * Author: Luis Monteiro
 *
 * Created on July 4, 2017, 10:27 PM
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
#include "Kernel/NetMachine.h"
/**
 */
using namespace std;
/**
 * 
 */
/*---------------------------------------------------------------------------------------------------------------------*
 * help
 *---------------------------------------------------------------------------------------------------------------------*/
#define USAGE(os) do{													\
	os << "USAGE:"<< endl;												\
	os << "\t" << basename(argv[0])	<< " "										\
		<<"[options]..."\
	<< endl;													\
	os << endl;													\
	os << "OPTIONS:"<< endl;											\
	os << "\t" << "-i, --instance" << endl;										\
	os << "\t" << "-r, --reference" << endl;									\
	os << "\t" << "-l, --location" << endl;										\
	os << "\t" << "-p, --password" << endl;										\
	os << "AUTHOR:"<< endl;												\
	os << "\t" << "Luis Monteiro <monteiro.lcm@gmail.com>"<< endl;							\
}while(0)
/*---------------------------------------------------------------------------------------------------------------------*
 * options
 *---------------------------------------------------------------------------------------------------------------------*/
static struct option options[] = {
	{"instance",	required_argument, 0, 'i'},
	{"reference",	required_argument, 0, 'r'},
	{"location",	required_argument, 0, 'l'},
	{"password",	required_argument, 0, 'p'},
	{0, 0, 0, 0}
};
/**--------------------------------------------------------------------------------------------------------------------*
 * main
 *---------------------------------------------------------------------------------------------------------------------*/
static void stop(int sig) {
        exit(sig);
}
int main(int argc, char** argv) {
        
	/**------------------------------------------------------------------------------------------------------------*
	 * signals
	 *-------------------------------------------------------------------------------------------------------------*/
	//signal(SIGPIPE, SIG_IGN);
	signal(SIGTERM, stop);
	signal(SIGINT, stop);
	/**------------------------------------------------------------------------------------------------------------*
	 * parse arguments
	 *-------------------------------------------------------------------------------------------------------------*/
	string instance	= "0";
	string reference= "10000";
	string location = "";
	string password = "";
	/** 
	 */
	for (int opt = '\0', i = 0; (opt = getopt_long(argc, argv, "hi:r:l:p:", options, &i)) != -1; i = 0) {
		switch (opt) {
			/**
			 * instance
			 */
			case 'i': instance = optarg; break;
			/**
			 * reference
			 */
			case 'r': reference = optarg; break;
			/**
			 * location
			 */
			case 'l': location = optarg; break;
			/**
			 * password
			 */
			case 'p': password = optarg; break;
			/**
			 * help
			 */
			case 'h': USAGE(cout);       return 0;
			/**
			 * error
			 */
			default:  USAGE(cerr);       return -1;
		}
	}
	/**------------------------------------------------------------------------------------------------------------*
	 * process
	 *-------------------------------------------------------------------------------------------------------------*/
        STask::Enable();
        /**
         */
	for(
		NetMachine nm (location, password, stoi(instance), stoi(reference));
		true;
		this_thread::sleep_for(chrono::seconds(10))
	){
		cout << nm.Good() << endl;
	}
	/** 
	 */
	return 0;
}

