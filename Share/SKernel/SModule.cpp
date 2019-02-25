/*
 * File:   SModule.cpp
 * Author: Luis Monteiro
 *
 * Created on February 10, 2019, 23:00
 **
 * Share 
 */
#include "SModule.h"
/**
 * ------------------------------------------------------------------------------------------------
 * definitions
 * ------------------------------------------------------------------------------------------------
 */
constexpr const char* SModuleCommand::MODULE;
constexpr const char* SModuleCommand::FUNCTION;
constexpr const char* SModuleCommand::INPUT;
constexpr const char* SModuleCommand::OUTPUT;
constexpr const char* SModuleCommand::INOUT;
/**
 * ------------------------------------------------------------------------------------------------
 * fabric
 * ------------------------------------------------------------------------------------------------
 */
SModule::Link SModule::Create(const Command& cmd) {
    static std::map<Key, std::function <Link(const Command& cmd)>> GENERATOR {
        {"encode", [](const Command& cmd) {
            auto in = nullptr;
            return in;
        }}
    };
    try {
        return GENERATOR[""](cmd);
    } catch(...) {
        throw std::runtime_error("invalid input");
    }
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */