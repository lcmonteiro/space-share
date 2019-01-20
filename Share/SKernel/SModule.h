/** 
 * File:   SProcess.h
 * Author: Luis Monteiro
 *
 * Created on January 20, 2017, 11:34 AM
 */
#ifndef SMODULE_H
#define SMODULE_H
/**
 */
#include <random>
/**
 */
#include "SProcess.h"
#include "SCommand.h"
#include "SVariable.h"
#include "SEnergy.h"
#include "SRoad.h"
/**
 * ------------------------------------------------------------------------------------------------*
 * exceptions 
 * ------------------------------------------------------------------------------------------------
 **/
typedef class SModuleException : public logic_error {
public:
    using logic_error::logic_error;
    /**
     * constructor
     */
    SModuleException(const string& msg):logic_error(msg){
    }
} ModuleException;

typedef class SModuleExceptionDead : public SModuleException {
public:
    using SModuleException::SModuleException;
    /**
     * constructor
     */
    SModuleExceptionDead(string s) : SModuleException(s) {
    }
} ModuleExceptionDEAD;
/**
 * ------------------------------------------------------------------------------------------------*
 * module 
 * ------------------------------------------------------------------------------------------------
 **/
class SModuleCommand: public SCommand<string, string> {
public:
    using Command=SCommand<string, string>;
    /**
     * keys
     */
    static constexpr const char* MODULE   = "M";
    static constexpr const char* FUNCTION = "F";
    static constexpr const char* INPUT    = "I";
    static constexpr const char* OUTPUT   = "O";
    static constexpr const char* INOUT    = "X";
    /**
     * constructor
     */ 
    using Command::Command;
    /**
     * add
     */
    #define ADD(Key_, Name_)                        \
    SModuleCommand& Add##Name_(const Group& conf) { \
        try {                                       \
            __opts.at(Key_).emplace_back(conf);     \
        } catch(...){                               \
            __opts.emplace(MODULE, Groups({conf})); \
        }                                           \
        return *this;                               \
    }
    ADD(MODULE,   Module  );
    ADD(FUNCTION, Function);
    ADD(INPUT,    Input   );
    ADD(OUTPUT,   Output  );
    ADD(INOUT,    InOutput);
    /**
     * set
     */
    #define SET(Key_, Name_)                        \
    SModuleCommand& Set##Name_(const Group& conf) { \
        __opts.emplace(MODULE, Groups({conf}));     \
        return *this;                               \
    }
    SET(MODULE,   Module  );
    SET(FUNCTION, Function);
    /**
     * gets
     */
    #define GETS(Key_, Name_)               \
    const Groups& Get##Name_##s() const {   \
        static const Groups empty{};        \
        try {                               \
            return (*this)[Key_];           \
        } catch(...) {                      \
            return empty;                   \
        }                                   \
    }
    GETS(MODULE,   Module  );
    GETS(FUNCTION, Function);
    GETS(INOUT,    Input   );
    GETS(OUTPUT,   Output  );
    GETS(INOUT,    InOutput);
    /**
     * get
     */
    #define GET(Key_, Name_)                \
    const Group& Get##Name_() const {       \
        static const Group empty{};         \
        try {                               \
            return (*this)[Key_][0];        \
        } catch(...) {                      \
            return empty;                   \
        }                                   \
    }
    GET(MODULE,   Module  );
    GET(FUNCTION, Function);
};
constexpr const char* SModuleCommand::MODULE;
constexpr const char* SModuleCommand::FUNCTION;
constexpr const char* SModuleCommand::INPUT;
constexpr const char* SModuleCommand::OUTPUT;
constexpr const char* SModuleCommand::INOUT;
/**
 * ------------------------------------------------------------------------------------------------
 * module 
 * ------------------------------------------------------------------------------------------------
 **/
class SModule 
: public SProcess<SModuleCommand, SVariable<string>>, public SEnergy<ModuleExceptionDEAD> {
public:   
    /**
     * --------------------------------------------------------------------------------------------
     * Definitions
     * --------------------------------------------------------------------------------------------
     * state type
     */
    typedef enum {OPEN = 0, OWAIT, IWAIT, PROCESS, UPDATE, CLOSE} State;
    /**
     */
    using Key = string;
    using Val = string;
    /**
     */
    using Command = SModuleCommand;
    using Group   = Command::Group;
    using Groups  = Command::Groups;
    using Link    = shared_ptr<SModule>;
    /**
     * --------------------------------------------------------------------------------------------
     * Fabric
     * --------------------------------------------------------------------------------------------
     */
    static Link Create(const Command& cmd) {
        static map<Key, function <Link(const Command& cmd)>> GENERATOR {
            {"encode", [](const Command& cmd) {
                auto in = nullptr;
                return in;
            }}
        };
        try {
            return GENERATOR[""](cmd);
        } catch(...) {
            throw runtime_error("invalid input");
        }
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Check state
     * --------------------------------------------------------------------------------------------
     */
    inline State GetState(void) {
        return __state;
    }
    inline bool IsState(State s) {
        return __state == s;
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     * main constructor
     */
    SModule(const SAddress uri, size_t energy, uint8_t verbose)
    : SProcess(uri, verbose), SEnergy(energy), __state(OPEN) {
    }
    /**
     * default constructor
     */
    SModule() = default;
    /**
     * ------------------------------------------------------------------------
     * Attributes
     * ------------------------------------------------------------------------
     */
    State __state;
    /**
     * setter
     */
    inline void SetState(State s) {
        __state = s;
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * end 
 * ------------------------------------------------------------------------------------------------
 **/
#endif /* SMODULE */
