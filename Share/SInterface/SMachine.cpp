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
SMachine::SMachine(const Key& uri, const vector<SModule::Command> conf) : __uri(uri) {    
    /**
     * create link
     */
    __link.Bind(uri);
    /**
     * create modules
     */
    for(auto& c : conf) {
        InsertModule(MakeURI(c[""][0][SModule::URI]), c);
    }    
}

SMachine::SMachine(const Key& uri, const vector<string> conf) : __uri(uri) {
    /**
     * create link
     */
    __link.Bind(uri);
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
    Frame frame(0x1000);
    try {
        /**
         * wait data
         */
        __link.Wait(timeout).Fill(frame);
        /**
         * process data
         */
        ProcessData(string(frame.begin(), frame.end()));
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
void SMachine::ProcessData(string data) {
    /**
     * parse data
     */
    auto cmd = Module::Command::Unserialize({"M", "F", "I", "O"}, data);
    /**
     * uri - resource identify
     */
    for(auto& m : cmd["M"]) {
        try {
            InsertModule(MakeURI(m[Module::URI]), MakeConfig(cmd));
        } catch(...){
            UpdateModule(MakeURI(m[Module::URI]), MakeConfig(cmd));
        }
    }
}
/**
 * insert module
 */
void SMachine::InsertModule(Module::Key uri, Module::Config config) {
    /**
     * install module
     */
    __modules.emplace(std::piecewise_construct,
        std::forward_as_tuple(uri),
        std::forward_as_tuple(uri, config)
    );
    /**
     * start module
     */
    __modules[uri].Detach();
}
/**
 * update module
 */
void SMachine::UpdateModule(Module::Key uri, Module::Config config) {

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
//        cout << a.first << ":" << a.second << ", ";
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