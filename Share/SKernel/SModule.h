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
class SModuleCommand: public SCommand<SText, SText> {
public:
    using Command = SCommand<SText, SText>;
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
    #define ADD(key_, name_)                        \
    SModuleCommand& add_##name_(const Group& conf) {\
        try {                                       \
            __opts.at(key_).emplace_back(conf);     \
        } catch(...){                               \
            __opts.emplace(key_, Groups({conf}));   \
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
    #define SET(key_, name_)                        \
    SModuleCommand& set_##name_(const Group& conf) {\
        __opts.emplace(key_, Groups({conf}));       \
        return *this;                               \
    }
    SET(MODULE,   module  );
    SET(FUNCTION, function);
    /**
     * gets
     */
    #define GETS(key_, name_)               \
    const Groups& get_##name_##s() const {   \
        static const Groups empty{};        \
        try {                               \
            return (*this)[key_];           \
        } catch(...) {                      \
            return empty;                   \
        }                                   \
    }
    GETS(MODULE,   module  );
    GETS(FUNCTION, function);
    GETS(INOUT,    input   );
    GETS(OUTPUT,   output  );
    GETS(INOUT,    inoutput);
    /**
     * get
     */
    #define GET(key_, name_)                \
    const Group& get_##name_() const {      \
        static const Group empty{};         \
        try {                               \
            return (*this)[key_][0];        \
        } catch(...) {                      \
            return empty;                   \
        }                                   \
    }
    GET(MODULE,   module  );
    GET(FUNCTION, function);
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
    using Key = std::string;
    using Val = std::string;
    /**
     */
    using Command = SModuleCommand;
    using Group   = Command::Group;
    using Groups  = Command::Groups;
    using Link    = std::shared_ptr<SModule>;
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
