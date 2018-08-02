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
#include "SConnector/SDecoded/SMessage/SUdpConnector.h"
#include "SConnector/SDecoded/SMessage/SLocConnector.h"
//#include "SConnector/SDecoded/SMessage/SDirConnector.h"
//#include "SConnector/SDecoded/SMessage/SFileConnector.h"
#include "SConnector/SDecoded/SStream/SLocConnector.h"
#include "SConnector/SDecoded/SStream/STcpConnector.h"
//#include "SConnector/SDecoded/SStream/SFileConnector.h"
#include "SConnector/SEncoded/SMessage/SFileConnector.h"
//#include "SConnector/SEncoded/SMessage/SDirConnector.h"
//#include "SConnector/SEncoded/SMessage/SIrcConnector.h"
//#include "SConnector/SEncoded/SMessage/SLocConnector.h"
#include "SConnector/SEncoded/SStream/SLocConnector.h"
#include "SConnector/SEncoded/SStream/STcpConnector.h"
/**
 *----------------------------------------------------------------------------------------------------------------------
 * Module name space
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace SModule {
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
                static inline I Build(const Process::Group& o){
                        return nullptr;
                }
        };
        /**
         * Decoder Builder
         */
        template <>
        struct Builder<Decoded::IConnector> {
                static inline Decoded::IConnector Build(const Process::Group& o) {
                        static map<SConnector::Key, function <Decoded::IConnector(const Process::Group&)>> GENERATOR {
                                {SConnector::Key(Properties ::MESSAGE_LOCAL), [](const Process::Group& o) {
                                        auto in = Decoded::Message::IUdpConnector::Make(
                                                Process::Command::Peek(o, Properties::URI,  string("127.0.0.1:1357")),
                                                Process::Command::Peek(o, Properties::BIND, string("127.0.0.1:1359")),
                                                Process::Command::Peek(o, Properties::NFRAMES, 50)
                                        );
                                        in->SetVerbose(Process::Command::Peek(o, Properties::VERBOSE, 0));
                                        in->SetEnergy(Process::Command::Peek(o,  Properties::ENERGY,  0));
                                        return in;
                                }}
                        };
                        return GENERATOR[
                                Process::Command::Peek(o, Properties::TYPE, SConnector::Key(Properties::MESSAGE_LOCAL))
                        ](o);
                }
        };
        /**
         * Encoded Builder
         */
        template <>
        struct Builder<Encoded::IConnector> {
                static inline Encoded::IConnector Build(const Process::Group& o){
                        static map<SConnector::Key, function <Encoded::IConnector(const Process::Group&)>> GENERATOR {
                                {SConnector::Key(Properties::MESSAGE_FILE), [](const Process::Group& o) {
                                        auto in = Encoded::Message::IFileConnector::Make(
                                                Process::Command::Peek(o, Properties::URI, string("/tmp/coded"))
                                        );
                                        in->SetVerbose(Process::Command::Peek(o, Properties::VERBOSE, 0));
                                        in->SetEnergy(Process::Command::Peek(o,  Properties::ENERGY,  1));
                                        return in;
                                }}
                        };
                        return GENERATOR[
                                Process::Command::Peek(o, Properties::TYPE, SConnector::Key(Properties::MESSAGE_FILE))
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
                static inline O Build(const Process::Group& o){
                        return nullptr;
                }
        };
        /**
         * Decoded Builder
         */
        template <>
        struct Builder<Decoded::OConnector> {
                static inline Decoded::OConnector Build(const Process::Group& o) {
                        static map<SConnector::Key, function <Decoded::OConnector(const Process::Group&)>> GENERATOR {
                                {SConnector::Key(Properties::MESSAGE_UDP), [](const Process::Group& o) {
                                        auto out = Decoded::Message::OUdpConnector::Make(
                                                Process::Command::Peek(o, Properties::URI,  string("127.0.0.1:9751")),
                                                Process::Command::Peek(o, Properties::BIND, string("127.0.0.1:9753"))
                                        );
                                        out->SetVerbose(Process::Command::Peek(o, Properties::VERBOSE, 0));
                                        out->SetEnergy(Process::Command::Peek(o,  Properties::ENERGY,  1));
                                        return out;
                                }}
                        };
                        return GENERATOR[
                                Process::Command::Peek(o, Properties::TYPE, SConnector::Key(Properties::MESSAGE_UDP))
                        ](o);
                }
        };
        /**
         * Encoded Builder
         */
        template <>
        struct Builder<Encoded::OConnector> {
                static inline Encoded::OConnector Build(const Process::Group& o){
                        static map<SConnector::Key, function <Encoded::OConnector(const Process::Group&)>> GENERATOR {
                                {SConnector::Key(Properties::MESSAGE_FILE), [](const Process::Group& o) {
                                        auto out = Encoded::Message::OFileConnector::Make(
                                                Process::Command::Peek(o, Properties::URI, string("/tmp/code"))
                                        );
                                        out->SetVerbose(Process::Command::Peek(o, Properties::VERBOSE, 0));
                                        out->SetEnergy(Process::Command::Peek(o,  Properties::ENERGY,  1));
                                        return out;
                                }}
                        };
                        return GENERATOR[
                                Process::Command::Peek(o, Properties::TYPE, SConnector::Key(Properties::MESSAGE_FILE))
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
                static inline O Build(const Process::Group& o){
                        return nullptr;
                }
        };
        /**
         * Decoded Builder
         */
        template <>
        struct Builder<Decoded::IOConnector> {
                static inline Decoded::IOConnector Build(const Process::Group& o) {
                        static map<SConnector::Key, function <Decoded::IOConnector(const Process::Group&)>> GENERATOR {
                                {SConnector::Key(Properties::STREAM_LOCAL), [](const Process::Group& o) {
                                        auto io = Decoded::Stream::IOLocConnector::Make(
                                                Process::Command::Peek(o, Properties::URI,  string("/tmp/data.y")),
                                                Process::Command::Peek(o, Properties::NFRAMES, 50),
                                                Process::Command::Peek(o, Properties::SFRAMES, 4096)
                                        );
                                        io->SetVerbose(Process::Command::Peek(o, Properties::VERBOSE, 0));
                                        io->SetEnergy(Process::Command::Peek(o,  Properties::ENERGY,  1));
                                        return io;
                                }}
                        };
                        return GENERATOR[
                                Process::Command::Peek(o, Properties::TYPE, SConnector::Key(Properties::STREAM_TCP))
                        ](o);
                }
        };
        /**
         * Encoded Builder
         */
        template <>
        struct Builder<Encoded::IOConnector> {
                static inline Encoded::IOConnector Build(const Process::Group& o){
                        static map<SConnector::Key, function <Encoded::IOConnector(const Process::Group&)>> GENERATOR {
                                
                        };
                        return GENERATOR[
                                Process::Command::Peek(o, Properties::TYPE, SConnector::Key(Properties::STREAM_TCP))
                        ](o);
                }
        };
}
}
#endif /* SMODULE_CONNECTORS_H */