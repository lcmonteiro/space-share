/** 
 * File:   MFunctions.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 */
#ifndef SMODULE_FUNCTIONS_H
#define SMODULE_FUNCTIONS_H
/**
 * ------------------------------------------------------------------------------------------------
 * Includes
 * ------------------------------------------------------------------------------------------------
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
 *-------------------------------------------------------------------------------------------------
 * Module name space
 *-------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 * ------------------------------------------------------------------------------------------------
 * Helpers
 * ------------------------------------------------------------------------------------------------
 */
namespace Helpers {
    /**
     * create codec stamp
     */
    inline Stamp CreateStamp(SModule::Key type, string pass) {
        return CodecStamp::Generate(map<SModule::Key, CodecStamp::Type> {
            {Function::SPARSE,  CodecStamp::SPARSE},
            {Function::STREAM,  CodecStamp::STREAM},
            {Function::MESSAGE, CodecStamp::MESSAGE},
            {Function::FULL,    CodecStamp::FULL},
        }.at(type), SHash::Digest(pass));
    }
}
/**
 *-------------------------------------------------------------------------------------------------
 * Spread functions
 *-------------------------------------------------------------------------------------------------
 */
namespace Spread {
    /**
     * Template Base Builder
     */
    template <class I, class D, class O>
    struct BaseBuilder {
        using Pointer = shared_ptr<SFunctionSpread<SConnector::Key, I, D, O>>;
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
                {Function::Type::MESSAGE, [](const SModule::Command::Group& o) {
                    /** 
                     * create function
                     */
                    return make_shared<Message::SEncode>(Helpers::CreateStamp(
                            o.Get(Function::TYPE,   Function::Type::MESSAGE),
                            o.Get(Function::SECRET, string())
                        ), 
                        o.Get(Function::CACHE,  10),
                        o.Get(Function::ENERGY, 10),
                        o.Get(Function::VERBOSE, 1)
                    );
                }}
            };
            return GENERATOR[
                o.Get(Function::TYPE, Function::Type::MESSAGE)
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
                {Function::Type::MESSAGE, [](const SModule::Command::Group& o) {
                    /** 
                     * create function
                     */
                    return make_shared<Message::SDecode>(Helpers::CreateStamp(
                            o.Get(Function::TYPE,   Function::Type::MESSAGE),
                            o.Get(Function::SECRET, SConnector::Key())
                        ), 
                        o.Get(Function::CACHE,  10),
                        o.Get(Function::ENERGY, 10),
                        o.Get(Function::VERBOSE, 1)
                    );
                }}
            };
            return GENERATOR[
                o.Get(Function::TYPE, Function::Type::MESSAGE)
            ](o);
        }
    };
}
/**
 *-------------------------------------------------------------------------------------------------
 * Spliter functions
 *-------------------------------------------------------------------------------------------------
 */
namespace Spliter {
    /**
     * Template Base Builder
     */
    template <class IO, class I, class O>
    struct BaseBuilder {
        using Pointer = shared_ptr<SFunctionSpliter<SConnector::Key, IO, I, O>>;
    };
    /**
     * Template Builder
     */
    template <class IO, class I, class O>
    struct Builder : BaseBuilder<IO, I, O> {
        using Pointer = typename BaseBuilder<IO, I, O>::Pointer;
        static inline Pointer Build(const SModule::Command::Group& o){
            return make_shared<SFunctionSpliter<SConnector::Key, IO, I, O>>(
                o.Get(Function::ENERGY,  10), 
                o.Get(Function::VERBOSE, 1)
            );
        }
    };
};
}
#endif /* SMODULE_FUNCTIONS_H */