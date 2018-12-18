/* 
 * File:   SMachine.cpp
 * Author: Luis Monteiro
 * 
 * Created on July 4, 2017, 11:51 PM
 */
#include <stdbool.h>
/**
 * Local
 */
#include "SMachine.h"
/**
 * Space Kernel
 */
#include "SCommand.h"
/**
 *----------------------------------------------------------------------------------------------------------------------
 * constructors 
 *----------------------------------------------------------------------------------------------------------------------
 * main constructor
 */
SMachine::SMachine(const SAddress& uri, const vector<SModule::Command> conf) 
: __uri(uri), __monitor(uri) {    
    /**
     * create modules
     */
    for(auto& c : conf) {
        ProcessData(c);
    }    
}
/**
 *----------------------------------------------------------------------------------------------------------------------
 * interface
 *----------------------------------------------------------------------------------------------------------------------
 * process
 */
bool SMachine::Process(chrono::milliseconds timeout) {
    try {
        /**
         * wait data
         */
        SResourceMonitor(timeout, &__monitor).Wait();
        /**
         * process data
         */
        ProcessData(__monitor.Read());
        /** 
         */
    } catch (ResourceExceptionTIMEOUT& ex) {
        cout << ex.what() << endl;
    } catch (MonitorExceptionTIMEOUT& ex) {
        cout << ex.what() << endl;
    }
    return true;
}
/**
 *----------------------------------------------------------------------------------------------------------------------
 * protected functions
 *----------------------------------------------------------------------------------------------------------------------
 * process data
 * 
 * M = module
 * F = function
 * I = input
 * O = output
 */
void SMachine::ProcessData(const Command& cmd) {
    /**
     * uri - resource identify
     */
    for(auto& m : cmd[MODULE]) {
        try {
            InsertModule(MakeURI(m[SModule::URI]), cmd);
        } catch(...){
            UpdateModule(MakeURI(m[SModule::URI]), cmd);
        }
    }
}
/**
 * insert module
 */
void SMachine::InsertModule(Key uri, const Command& cmd) {
    /**
     * install module
     */
    __modules.emplace(uri, SModule::Create(cmd));
    /**
     * start module
     */
    __modules[uri]->Detach();
}
/**
 * update module
 */
void SMachine::UpdateModule(Key uri, const Command& cmd) {

}
/**
 * remove module
 */
void SMachine::RemoveModule(Key uri) {
    __modules.erase(uri);
}
/**
 *----------------------------------------------------------------------------------------------------------------------
 * utilities
 *----------------------------------------------------------------------------------------------------------------------
 * print configuration
 */
//void SMachine::Print(const Config& conf) {
//    for(auto& t : conf) {
//        cout << t.first << ":" << "[ "; 
//    for (auto& a : get<0>(t.second)) {
//        cout << a.first << ":" << a.second << ", ";
//    }
//    cout << endl;
//    for (auto& a : get<1>(t.second)) {
//        cout << a.first << ":" << a.second << ", ";
//    }
//    cout << endl;
//    for (auto& e : get<2>(t.second)) {
//        for (auto& a : e.second) {
//        cout << a.first << ":" << a.second << ", ";ter
//        }
//        cout << endl;
//    }
//    for (auto& e : get<3>(t.second)) {
//        for (auto& a : e.second) {
//        cout << a.first << ":" << a.second << ", ";
//        }
//        cout << endl;
//    }
//    cout << "]" << endl;
//    }
//}