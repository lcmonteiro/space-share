/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   MFunctions.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SMODULE_FUNCTIONS_H
#define SMODULE_FUNCTIONS_H
/**
 * Space Kernel
 */
#include "SHash.h"
/**
 * Share Functions
 */
#include "SEncode.h"
#include "SDecode.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Module name space
 * ------------------------------------------------------------------------------------------------
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
    inline SharedStamp CreateStamp(SModule::Key type, string pass) {
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
     * --------------------------------------------------------------------------------------------
     * Default Builder
     * --------------------------------------------------------------------------------------------
     */
    template <class I, class D, class O>
    struct Builder : BaseBuilder<I, D, O> {
        using Pointer = typename BaseBuilder<I, D, O>::Pointer;
        static inline Pointer Build(const SModule::Command::Group& o){
            /** 
             * create function
             */
            return make_shared<SFunctionSpread<SConnector::Key, I, D, O>>(
                o.Get(Function::ENERGY,  10), 
                o.Get(Function::VERBOSE, 1)
            );
        }
    };
    /**
     * --------------------------------------------------------------------------------------------
     * Encode Builder
     * --------------------------------------------------------------------------------------------
     */
    template <>
    struct Builder<Decoded::IConnector, Decoded::Document, Encoded::OConnector> 
    : BaseBuilder<Decoded::IConnector, Decoded::Document, Encoded::OConnector> {
        using Pointer = typename BaseBuilder<Decoded::IConnector, Decoded::Document, Encoded::OConnector>::Pointer;
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
            try {
                return GENERATOR.at(
                    o.Get(Function::TYPE, Function::Type::MESSAGE)
                )(o);
            } catch(...) {
                throw std::runtime_error(
                    SText("invalid function: ", o.Get(Function::TYPE, Function::Type::MESSAGE))
                );
            }
        }
    };
    /**
     * --------------------------------------------------------------------------------------------
     * Decode Builder
     * --------------------------------------------------------------------------------------------
     */
    template <>
    struct Builder<Encoded::IConnector, Encoded::Document, Decoded::OConnector> 
    : BaseBuilder<Encoded::IConnector, Encoded::Document, Decoded::OConnector> {
        using Pointer = typename BaseBuilder<Encoded::IConnector, Encoded::Document, Decoded::OConnector>::Pointer;
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
            try {
                return GENERATOR.at(
                    o.Get(Function::TYPE, Function::Type::MESSAGE)
                )(o);
            } catch(...) {
                throw std::runtime_error(
                    SText("invalid function: ", o.Get(Function::TYPE, Function::Type::MESSAGE))
                );
            }
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
     * --------------------------------------------------------------------------------------------
     * Default Builder
     * --------------------------------------------------------------------------------------------
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
/**
 *-------------------------------------------------------------------------------------------------
 * End
 *-------------------------------------------------------------------------------------------------
 */
#endif /* SMODULE_FUNCTIONS_H */