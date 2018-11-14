/** 
 * File:   MConnectors.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 */
#ifndef SMODULE_CONNECTORS_H
#define SMODULE_CONNECTORS_H
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------------------------------------------------
 */
#include "MProperties.h"
/**
 * connectors
 */
#include "SDecoded/SMessage/SUdpConnector.h"
#include "SDecoded/SMessage/SLocConnector.h"
//#include "SConnector/SDecoded/SMessage/SDirConnector.h"
//#include "SConnector/SDecoded/SMessage/SFileConnector.h"
#include "SDecoded/SStream/SLocConnector.h"
#include "SDecoded/SStream/STcpConnector.h"
//#include "SConnector/SDecoded/SStream/SFileConnector.h"
#include "SEncoded/SMessage/SFileConnector.h"
//#include "SConnector/SEncoded/SMessage/SDirConnector.h"
//#include "SConnector/SEncoded/SMessage/SIrcConnector.h"
//#include "SConnector/SEncoded/SMessage/SLocConnector.h"
#include "SEncoded/SStream/SLocConnector.h"
#include "SEncoded/SStream/STcpConnector.h"
/**
 *----------------------------------------------------------------------------------------------------------------------
 * Module name space
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 *----------------------------------------------------------------------------------------------------------------------
 * Input
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Input {
    /**
     * Template Builder
     */
    template <class I>
    struct Builder {
        static inline I Build(const SModule::Command::Group& o){
            return nullptr;
        }
    };
    /**
     * Decoder Builder
     */
    template <>
    struct Builder<Decoded::IConnector> {
        static inline Decoded::IConnector Build(const SModule::Command::Group& o) {
            static map<SConnector::Key, function <Decoded::IConnector(const SModule::Command::Group&)>> GENERATOR {
                {SConnector::Key(Properties::MESSAGE_LOCAL), [](const SModule::Command::Group& o) {
                    auto in = Decoded::Message::ILocConnector::Make(
                        SModule::Command::Peek(o, Properties::URI),
                        SModule::Command::Peek(o, Properties::NFRAMES, 50),
                        SModule::Command::Peek(o, Properties::SFRAMES, 1550)
                    );
                    in->SetVerbose(SModule::Command::Peek(o, Properties::VERBOSE, 0));
                    in->SetEnergy(SModule::Command::Peek(o,  Properties::ENERGY,  0));
                    return in;
                }},
                {SConnector::Key(Properties::MESSAGE_UDP), [](const SModule::Command::Group& o) {
                    auto in = Decoded::Message::IUdpConnector::Make(
                        SModule::Command::Peek(o, Properties::URI),
                        SModule::Command::Peek(o, Properties::NFRAMES, 50),
                        SModule::Command::Peek(o, Properties::SFRAMES, 1550)
                    );
                    in->SetVerbose(SModule::Command::Peek(o, Properties::VERBOSE, 0));
                    in->SetEnergy(SModule::Command::Peek(o,  Properties::ENERGY,  0));
                    return in;
                }}
            };
            return GENERATOR[
                SModule::Command::Peek(o, Properties::TYPE, SConnector::Key(Properties::MESSAGE_LOCAL))
            ](o);
        }
    };
    /**
     * Encoded Builder
     */
    template <>
    struct Builder<Encoded::IConnector> {
        static inline Encoded::IConnector Build(const SModule::Command::Group& o){
            static map<SConnector::Key, function <Encoded::IConnector(const SModule::Command::Group&)>> GENERATOR {
                {SConnector::Key(Properties::MESSAGE_FILE), [](const SModule::Command::Group& o) {
                    auto in = Encoded::Message::IFileConnector::Make(
                        SModule::Command::Peek(o, Properties::URI, string("/tmp/coded"))
                    );
                    in->SetVerbose(SModule::Command::Peek(o, Properties::VERBOSE, 0));
                    in->SetEnergy(SModule::Command::Peek(o,  Properties::ENERGY,  1));
                    return in;
                }}
            };
            return GENERATOR[
                SModule::Command::Peek(o, Properties::TYPE, SConnector::Key(Properties::MESSAGE_FILE))
            ](o);
        }
    };
};
/**
 *----------------------------------------------------------------------------------------------------------------------
 * Output
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Output {
    /**
     * Template Builder
     */
    template <class O>
    struct Builder {
        static inline O Build(const SModule::Command::Group o){
            return nullptr;
        }
    };
    /**
     * Decoded Builder
     */
    template <>
    struct Builder<Decoded::OConnector> {
        static inline Decoded::OConnector Build(const SModule::Command::Group& o) {
            static map<SConnector::Key, function <Decoded::OConnector(const SModule::Command::Group&)>> GENERATOR {
                {SConnector::Key(Properties::MESSAGE_UDP), [](const SModule::Command::Group& o) {
                    auto out = Decoded::Message::OUdpConnector::Make(
                        SModule::Command::Peek(o, Properties::URI,  string("127.0.0.1:9751"))
                    );
                    out->SetVerbose(SModule::Command::Peek(o, Properties::VERBOSE, 0));
                    out->SetEnergy(SModule::Command::Peek(o,  Properties::ENERGY,  1));
                    return out;
                }}
            };
            return GENERATOR[
                SModule::Command::Peek(o, Properties::TYPE, SConnector::Key(Properties::MESSAGE_UDP))
            ](o);
        }
    };
    /**
     * Encoded Builder
     */
    template <>
    struct Builder<Encoded::OConnector> {
        static inline Encoded::OConnector Build(const SModule::Command::Group& o){
            static map<SConnector::Key, function <Encoded::OConnector(const SModule::Command::Group&)>> GENERATOR {
                {SConnector::Key(Properties::MESSAGE_FILE), [](const SModule::Command::Group& o) {
                    auto out = Encoded::Message::OFileConnector::Make(
                        SModule::Command::Peek(o, Properties::URI, string("/tmp/code"))
                    );
                    out->SetVerbose(SModule::Command::Peek(o, Properties::VERBOSE, 0));
                    out->SetEnergy(SModule::Command::Peek(o,  Properties::ENERGY,  1));
                    return out;
                }}
            };
            return GENERATOR[
                SModule::Command::Peek(o, Properties::TYPE, SConnector::Key(Properties::MESSAGE_FILE))
            ](o);
        }
    };
}
/**
 *----------------------------------------------------------------------------------------------------------------------
 * (In|Out)put
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace IOput {
    /**
     * Template Builder
     */
    template <class O>
    struct Builder {
        static inline O Build(const SModule::Command::Group& o){
            return nullptr;
        }
    };
    /**
     * Decoded Builder
     */
    template <>
    struct Builder<Decoded::IOConnector> {
        static inline Decoded::IOConnector Build(const SModule::Command::Group& o) {
            static map<SConnector::Key, function <Decoded::IOConnector(const SModule::Command::Group&)>> GENERATOR {
                {SConnector::Key(Properties::STREAM_LOCAL), [](const SModule::Command::Group& o) {
                    auto io = Decoded::Stream::IOLocConnector::Make(
                        SModule::Command::Peek(o, Properties::URI,  string("/tmp/data.y")),
                        SModule::Command::Peek(o, Properties::NFRAMES, 50),
                        SModule::Command::Peek(o, Properties::SFRAMES, 4096)
                    );
                    io->SetVerbose(SModule::Command::Peek(o, Properties::VERBOSE, 0));
                    io->SetEnergy(SModule::Command::Peek(o,  Properties::ENERGY,  1));
                    return io;
                }}
            };
            return GENERATOR[
                SModule::Command::Peek(o, Properties::TYPE, SConnector::Key(Properties::STREAM_TCP))
            ](o);
        }
    };
    /**
     * Encoded Builder
     */
    template <>
    struct Builder<Encoded::IOConnector> {
        static inline Encoded::IOConnector Build(const SModule::Command::Group& o){
            static map<SConnector::Key, function <Encoded::IOConnector(const SModule::Command::Group&)>> GENERATOR {
                
            };
            return GENERATOR[
                SModule::Command::Peek(o, Properties::TYPE, SConnector::Key(Properties::STREAM_TCP))
            ](o);
        }
    };
}
}
#endif /* SMODULE_CONNECTORS_H */