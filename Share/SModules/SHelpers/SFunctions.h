/**
 * ------------------------------------------------------------------------------------------------
 * File:   MFunctions.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SMODULEFUNCTIONS_H
#define SMODULEFUNCTIONS_H
/**
 * Space Kernel
 */
#include "SHash.h"
/**
 * Share Functions
 */
#include "SEncodeFunction.h"
#include "SDecodeFunction.h"
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
    inline Codec::pStamp CreateStamp(SModule::Key type, const std::string& pass) {
        return Codec::SStamp::Generate(std::map<SModule::Key, Codec::SStamp::Type> {
            {Function::SPARSE,  Codec::SStamp::SPARSE},
            {Function::STREAM,  Codec::SStamp::STREAM},
            {Function::MESSAGE, Codec::SStamp::MESSAGE},
            {Function::FULL,    Codec::SStamp::FULL},
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
        using Pointer = std::shared_ptr<SFunctionSpread<SConnector::Key, I, D, O>>;
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
            return std::make_shared<SFunctionSpread<SConnector::Key, I, D, O>>(
                o.get(Function::ENERGY,  10), 
                o.get(Function::VERBOSE, 1)
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
            static std::map<SConnector::Key, std::function<Pointer(const SModule::Command::Group&)>> GENERATOR {
                {Function::Type::MESSAGE, [](const SModule::Command::Group& o) {
                    /** 
                     * --------------------------------------------------------
                     * create message function
                     * --------------------------------------------------------
                     */
                    return std::make_shared<Message::SEncodeFunction>(Helpers::CreateStamp(
                            o.get(Function::TYPE,   Function::Type::MESSAGE),
                            o.get(Function::SECRET, std::string())
                        ), 
                        o.get(Function::CACHE,  10),
                        o.get(Function::ENERGY, 10),
                        o.get(Function::VERBOSE, 1)
                    );
                }}
            };
            try {
                return GENERATOR.at(
                    o.get(Function::TYPE, Function::Type::MESSAGE)
                )(o);
            } catch(...) {
                throw std::runtime_error(
                    SText("invalid function: ", o.get(Function::TYPE, Function::Type::MESSAGE))
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
            static std::map<SConnector::Key, std::function<Pointer(const SModule::Command::Group&)>> GENERATOR {
                {Function::Type::MESSAGE, [](const SModule::Command::Group& o) {
                    /** 
                     * --------------------------------------------------------
                     * create message function
                     * --------------------------------------------------------
                     */
                    return std::make_shared<Message::SDecodeFunction>(Helpers::CreateStamp(
                            o.get(Function::TYPE,   Function::Type::MESSAGE),
                            o.get(Function::SECRET, SConnector::Key())
                        ), 
                        o.get(Function::CACHE,  10),
                        o.get(Function::ENERGY, 10),
                        o.get(Function::VERBOSE, 1)
                    );
                }}
            };
            try {
                return GENERATOR.at(
                    o.get(Function::TYPE, Function::Type::MESSAGE))(o);
            } catch(...) {
                throw std::runtime_error(
                    SText("invalid function: ", o.get(Function::TYPE, Function::Type::MESSAGE)));
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
        using Pointer = std::shared_ptr<SFunctionSpliter<SConnector::Key, IO, I, O>>;
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
            return std::make_shared<SFunctionSpliter<SConnector::Key, IO, I, O>>(
                o.get(Function::ENERGY,  10), 
                o.get(Function::VERBOSE, 1)
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
#endif /* SMODULEFUNCTIONS_H */