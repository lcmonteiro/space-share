/** 
 * ------------------------------------------------------------------------------------------------
 * File:   SModule.h
 * Author: Luis Monteiro
 *
 * Created on January 20, 2017, 11:34 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SMODULE_H
#define SMODULE_H
/**
 * std
 */
#include <random>
#include <atomic>
/**
 * space
 */
#include "SProcess.h"
#include "SCommand.h"
#include "SVariable.h"
#include "SEnergy.h"
#include "SClock.h"
#include "SRoad.h"
/**
 * ------------------------------------------------------------------------------------------------
 * exceptions 
 * ------------------------------------------------------------------------------------------------
 **/
typedef class SModuleException : public std::logic_error {
public:
    using std::logic_error::logic_error;
    /**
     * constructor
     */
    SModuleException(const std::string& msg): std::logic_error(msg){
    }
} ModuleException;

typedef class SModuleExceptionDead : public SModuleException {
public:
    using SModuleException::SModuleException;
    /**
     * constructor
     */
    SModuleExceptionDead(std::string s) : SModuleException(s) {
    }
} ModuleExceptionDEAD;
/**
 * ------------------------------------------------------------------------------------------------
 * module 
 * ------------------------------------------------------------------------------------------------
 **/
class SModuleCommand: public SCommand<std::string, std::string> {
public:
    using Command = SCommand<std::string, std::string>;
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
            __opts.emplace(Key_, Groups({conf}));   \
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
        __opts.emplace(Key_, Groups({conf}));       \
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
/**
 * ------------------------------------------------------------------------------------------------
 * module 
 * ------------------------------------------------------------------------------------------------
 **/
class SModule 
: public SProcess<SModuleCommand, SVariable<std::string>>, public SEnergy<ModuleExceptionDEAD> {
public:   
    using Time = std::chrono::milliseconds;
    /**
     * --------------------------------------------------------------------------------------------
     * Definitions
     * --------------------------------------------------------------------------------------------
     * state type
     */
    typedef enum {OPEN = 0, OWAIT, IOWAIT, IWAIT, PLAY, UPDATE, CLOSE} State;
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
     * Fabric - create modules
     * --------------------------------------------------------------------------------------------
     */
    static Link Create(const Command& cmd);
    /**
     * --------------------------------------------------------------------------------------------
     * Check state
     * --------------------------------------------------------------------------------------------
     */
    inline State GetState(void) {
        return __state;
    }
    inline bool IsState(State s) {
        return __state >= s;
    }
    inline bool WaitState(const Time& timeout, State s) {
        SClock<Time>::Alarm timer(timeout, Time(10));
        // verify -----------------------------------------
	    do {
		    if(IsState(s)) {
			    return true;
		    }
	    } while (!timer.Sleep().Active());
        // time expired -----------------------------------
        return false;
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
     * internal interfaces
     * ------------------------------------------------------------------------
     */
    inline void SetState(State s) {
        __state = s;
    }
private:
    /**
     * ------------------------------------------------------------------------
     * variables
     * ------------------------------------------------------------------------
     */
    std::atomic<State> __state;
};
/**
 * ------------------------------------------------------------------------------------------------
 * end 
 * ------------------------------------------------------------------------------------------------
 **/
#endif /* SMODULE */
