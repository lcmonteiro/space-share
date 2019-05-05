/**
 * -------------------------------------------------------------------------------------------------------------------- 
 * File:   SMachine.cpp
 * Author: Luis Monteiro
 * 
 * Created on July 4, 2017, 11:51 PM
 * --------------------------------------------------------------------------------------------------------------------
 */
#include <stdbool.h>
/**
 * Local
 */
#include "SMachine.h"
/**
 * Space 
 */
#include "SCommand.h"
#include "SResourceMonitor.h"
/**
 * share
 */
#include "SSpreadModule.h"
/**
 *---------------------------------------------------------------------------------------------------------------------
 * Constructors 
 *---------------------------------------------------------------------------------------------------------------------
 * main constructor
 */
SMachine::SMachine(const SAddress& uri, const Config& conf) 
: __uri(uri), __monitor(uri) {    
    for(auto& c : conf) { _process_cmd(c); }    
}
/**
 *---------------------------------------------------------------------------------------------------------------------
 * Interface
 *---------------------------------------------------------------------------------------------------------------------
 * process
 * ------------------------------------------------------------------------------------------------
 */
bool SMachine::process(Time timeout) {
    try {
        // wait data --------------------------------------
        ResourceMonitor(timeout, &__monitor).wait();

        // process command --------------------------------
        _process_cmd(__monitor.read());

    } catch (ResourceExceptionTIMEOUT& ex) {
    } catch (MonitorExceptionTIMEOUT& ex) {
    }
    return true;
}
/**
 * ------------------------------------------------------------------------------------------------
 * wait
 * ------------------------------------------------------------------------------------------------
 */
void SMachine::wait() {
    for(auto& m : __modules) {
        m.second->join();
    }
}
/**
 *---------------------------------------------------------------------------------------------------------------------
 * Protected functions
 *---------------------------------------------------------------------------------------------------------------------
 * process command
 * ------------------------------------------------------------------------------------------------
 */
void SMachine::_process_cmd(const Command& cmd) {
    for(auto& m : cmd.get_modules()) {
        try {
            _insert_module(__make_uri(m[Module::URI]), cmd);
        } catch(...){
            _update_module(__make_uri(m[Module::URI]), cmd);
        }
    }
}
/**
 * ------------------------------------------------------------------------------------------------
 * insert module
 * ------------------------------------------------------------------------------------------------
 */
void SMachine::_insert_module(Key uri, const Command& cmd) {
    /**
     * install module
     */
    __modules.emplace(uri, CreateModule(cmd));
    /**
     * start module
     */
    __modules[uri]->start();
}
/**
 * ------------------------------------------------------------------------------------------------
 * update module
 * ------------------------------------------------------------------------------------------------
 */
void SMachine::_update_module(Key uri, const Command& cmd) {

}
/**
 * ------------------------------------------------------------------------------------------------
 * remove module
 * ------------------------------------------------------------------------------------------------
 */
void SMachine::_remove_module(Key uri) {
    __modules.erase(uri);
}
/**
 * --------------------------------------------------------------------------------------------------------------------
 * Utilities
 * --------------------------------------------------------------------------------------------------------------------
 * print configuration
 * ------------------------------------------------------------------------------------------------
 */
void SMachine::Print(const Config& conf) {
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
}
/**
 * ------------------------------------------------------------------------------------------------
 * create module
 * ------------------------------------------------------------------------------------------------
 */
SMachine::Link SMachine::CreateModule(const Command& cmd) {
    static std::map<Key, std::function <Link(const Command& cmd)>> GENERATOR {
        // Encode -------------------------------------------------------------
        {Module::Type::ENCODE, [](const Command& cmd) {
            using Encode = Module::SSpreadModule<
                Decoded::IConnector, Decoded::Document, Encoded::OConnector
            >;
            return std::make_shared<Encode>(cmd);
        }},
        // Decode -------------------------------------------------------------
        {Module::Type::DECODE, [](const Command& cmd) {
            using Decode = Module::SSpreadModule<
                Encoded::IConnector, Encoded::Document, Decoded::OConnector
            >;
            return std::make_shared<Decode>(cmd);
        }}
    };
    // genetator --------------------------------------------------------------
    try {
        return GENERATOR.at(cmd.get_module()[Module::TYPE])(cmd);
    } catch(...) {
        throw std::runtime_error(
            SText("invalid module: ", cmd.get_module()[Module::URI])
        );
    }
}
/**
 * --------------------------------------------------------------------------------------------------------------------
 * End
 * --------------------------------------------------------------------------------------------------------------------
 */
