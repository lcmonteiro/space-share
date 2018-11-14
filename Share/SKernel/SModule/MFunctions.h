/** 
 * File:   MFunctions.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 */
#ifndef SMODULE_FUNCTIONS_H
#define SMODULE_FUNCTIONS_H
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------------------------------------------------
 **
 * Space Kernel
 */
#include "SHash.h"
/**
 * Share Functions
 */
#include "SEncode.h"
#include "SDecode.h"
/**
 */
//#include "MProcess.h"
/**
 *----------------------------------------------------------------------------------------------------------------------
 * Module name space
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Helpers
 * ---------------------------------------------------------------------------------------------------------------------
 */
namespace Helpers {
    /**
     * create codec stamp
     */
    inline Stamp CreateStamp(SModule::Key type, string pass) {
        return CodecStamp::Generate(map<SModule::Key, CodecStamp::Type> {
            {Properties::SPARSE,  CodecStamp::SPARSE},
            {Properties::STREAM,  CodecStamp::STREAM},
            {Properties::MESSAGE, CodecStamp::MESSAGE},
            {Properties::FULL,    CodecStamp::FULL},
        }.at(type), SHash::Digest(pass));
    }
}
/**
 *----------------------------------------------------------------------------------------------------------------------
 * Transform functions
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Transform {
    /**
     * Template Base Builder
     */
    template <class I, class D, class O>
    struct BaseBuilder {
        using Pointer = shared_ptr<SFunctionTransform<SConnector::Key, I, D, O>>;
    };
    /**
     * Template Builder
     */
    template <class I, class D, class O>
    struct Builder : BaseBuilder<I, D, O> {
        using Pointer = typename BaseBuilder<I, D, O>::Pointer;
        static inline Pointer Build(const SModule::Command::Group& o){
            return nullptr;
        }
    };
    /**
     * Encode Builder
     */
    template <>
    struct Builder<Decoded::IConnector, Container, Encoded::OConnector> 
    : BaseBuilder<Decoded::IConnector, Container, Encoded::OConnector> {
        using Pointer = typename BaseBuilder<Decoded::IConnector, Container, Encoded::OConnector>::Pointer;
        static inline Pointer Build(const SModule::Command::Group& o){
            static map<SConnector::Key, function <Pointer(const SModule::Command::Group&)>> GENERATOR {
                {Properties::MESSAGE, [](const SModule::Command::Group& o) {
                    /** 
                     * create function
                     */
                    return make_shared<Message::SEncode>(Helpers::CreateStamp(
                        SModule::Command::Peek(o, Properties::TYPE,   Properties::MESSAGE),
                        SModule::Command::Peek(o, Properties::SECRET, string(""))
                    ), 
                        SModule::Command::Peek(o, Properties::CACHE,  10),
                        SModule::Command::Peek(o, Properties::ENERGY, 10),
                        SModule::Command::Peek(o, Properties::VERBOSE, 1)
                    );
                }}
            };
            return GENERATOR[
                SModule::Command::Peek(o, Properties::TYPE, Properties::MESSAGE)
            ](o);
            
        }
    };
    /**
     * Decode Builder
     */
    template <>
    struct Builder<Encoded::IConnector, Document, Decoded::OConnector> 
    : BaseBuilder<Encoded::IConnector, Document, Decoded::OConnector> {
        using Pointer = typename BaseBuilder<Encoded::IConnector, Document, Decoded::OConnector>::Pointer;
        static inline Pointer Build(const SModule::Command::Group& o){
            static map<SConnector::Key, function <Pointer(const SModule::Command::Group&)>> GENERATOR {
                {Properties::MESSAGE, [](const SModule::Command::Group& o) {
                    /** 
                     * create function
                     */
                    return make_shared<Message::SDecode>(Helpers::CreateStamp(
                        SModule::Command::Peek(o, Properties::TYPE,   Properties::MESSAGE),
                        SModule::Command::Peek(o, Properties::SECRET, SConnector::Key())
                    ), 
                        SModule::Command::Peek(o, Properties::CACHE,  10),
                        SModule::Command::Peek(o, Properties::ENERGY, 10),
                        SModule::Command::Peek(o, Properties::VERBOSE, 1)
                    );
                }}
            };
            return GENERATOR[
                SModule::Command::Peek(o, Properties::TYPE, Properties::MESSAGE)
            ](o);
        }
    };
}
/**
 *----------------------------------------------------------------------------------------------------------------------
 * Ypsilon functions
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Ypsilon {
    /**
     * Template Base Builder
     */
    template <class IO, class I, class O>
    struct BaseBuilder {
        using Pointer = shared_ptr<SFunctionYpsilon<IO, I, O>>;
    };
    /**
     * Template Builder
     */
    template <class IO, class I, class O>
    struct Builder : BaseBuilder<IO, I, O> {
        using Pointer = typename BaseBuilder<IO, I, O>::Pointer;
        static inline Pointer Build(const SModule::Command::Group& o){
            return make_shared<SFunctionYpsilon<IO, I, O>>(
                SModule::Command::Peek(o, Properties::TIMEOUT, 1000), 
                SModule::Command::Peek(o, Properties::ENERGY,  2), 
                SModule::Command::Peek(o, Properties::VERBOSE, 1)
            );
        }
    };
};
}
#endif /* SMODULE_FUNCTIONS_H */