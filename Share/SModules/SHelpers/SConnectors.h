/**
 * -------------------------------------------------------------------------------------------------------------------- 
 * File:   MConnectors.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 * --------------------------------------------------------------------------------------------------------------------
 */
#ifndef SMODULECONNECTORS_H
#define SMODULECONNECTORS_H
/**
 * module
 */
#include "SProperties.h"
#include "SModule.h"
/**
 * connectors
 */
#include "SDecoded/SMessage/SUdpConnector.h"
#include "SDecoded/SMessage/SLocConnector.h"
#include "SDecoded/SMessage/SFileConnector.h"
//#include "SConnector/SDecoded/SMessage/SDirConnector.h"
#include "SDecoded/SStream/STcpConnector.h"
//#include "SConnector/SDecoded/SStream/SFileConnector.h"
//#include "SEncoded/SMessage/SDirConnector.h"
//#include "SEncoded/SMessage/SIrcConnector.h"
#include "SEncoded/SMessage/SLocConnector.h"
#include "SEncoded/SMessage/SFileConnector.h"
//#include "SEncoded/SStream/SLocConnector.h"
//#include "SEncoded/SStream/STcpConnector.h"
/**
 *---------------------------------------------------------------------------------------------------------------------
 * Module name space
 *---------------------------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 *---------------------------------------------------------------------------------------------------------------------
 * INPUT
 *---------------------------------------------------------------------------------------------------------------------
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
     * ----------------------------------------------------------------------------------------------------------------
     * Decoder Builder
     * ----------------------------------------------------------------------------------------------------------------
     */
    template <>
    struct Builder<Decoded::IConnector> {
        static inline Decoded::IConnector Build(const SModule::Command::Group& o) {
            static std::map<SConnector::Key, std::function <Decoded::IConnector(const SModule::Command::Group&)>> GENERATOR {
                /**
                 * --------------------------------------------------------------------------------
                 * message file 
                 * --------------------------------------------------------------------------------
                 */
                {SConnector::Key(IO::Type::MESSAGE_FILE), [](const SModule::Command::Group& o) {
                    auto in = Decoded::Message::IFileConnector::Make(
                        o.get(IO::URI),
                        o.get(IO::NFRAMES, size_t(50))
                    );
                    in->verbose(o.get(IO::VERBOSE, 0));
                    in->energy (o.get(IO::ENERGY,  1));
                    return in;
                }},
                /**
                 * --------------------------------------------------------------------------------
                 * message local 
                 * --------------------------------------------------------------------------------
                 */
                {SConnector::Key(IO::Type::MESSAGE_LOCAL), [](const SModule::Command::Group& o) {
                    auto in = Decoded::Message::ILocConnector::Make(
                        o.get(IO::URI),
                        o.get(IO::NFRAMES, size_t(50)),
                        o.get(IO::SFRAMES, size_t(1550))
                    );
                    in->verbose(o.get(IO::VERBOSE, 0));
                    in->energy (o.get(IO::ENERGY,  1));
                    return in;
                }},
                /**
                 * --------------------------------------------------------------------------------
                 * message remote 
                 * --------------------------------------------------------------------------------
                 */
                {SConnector::Key(IO::Type::MESSAGE_REMOTE), [](const SModule::Command::Group& o) {
                    auto in = Decoded::Message::IUdpConnector::Make(
                        o.get(IO::URI),
                        o.get(IO::NFRAMES, size_t(50)),
                        o.get(IO::SFRAMES, size_t(1550))
                    );
                    in->verbose(o.get(IO::VERBOSE, 0));
                    in->energy (o.get( IO::ENERGY, 1));
                    return in;
                }},
                /**
                 * --------------------------------------------------------------------------------
                 * stream remote 
                 * --------------------------------------------------------------------------------
                 */
                {SConnector::Key(IO::Type::STREAM_REMOTE), [](const SModule::Command::Group& o) {
                    auto io = Decoded::Stream::ITcpConnector::Make(
                        o.get(IO::URI),
                        o.get(IO::NFRAMES, size_t(50)),
                        o.get(IO::SFRAMES, size_t(4096))
                    );
                    io->verbose(o.get(IO::VERBOSE, 0));
                    io->energy (o.get(IO::ENERGY,  1));
                    return io;
                }},
            };
            try {
                return GENERATOR.at(
                    o.get(IO::TYPE, SConnector::Key(IO::Type::MESSAGE_LOCAL))
                )(o);
            } catch(...) {
                throw std::runtime_error(SText("invalid input connetor: ", o.get(IO::URI)));
            }
        }
    };
    /**
     * ----------------------------------------------------------------------------------------------------------------
     * Encoded Builder
     * ----------------------------------------------------------------------------------------------------------------
     */
    template <>
    struct Builder<Encoded::IConnector> {
        static inline Encoded::IConnector Build(const SModule::Command::Group& o){
            static std::map<SConnector::Key, std::function<Encoded::IConnector(const SModule::Command::Group&)>> GENERATOR {
                /**
                 * --------------------------------------------------------------------------------
                 * message local 
                 * --------------------------------------------------------------------------------
                 */
                {SConnector::Key(IO::Type::MESSAGE_LOCAL), [](const SModule::Command::Group& o) {
                    auto in = Encoded::Message::ILocConnector::Make(
                        o.get(IO::URI),
                        o.get(IO::SFRAMES, size_t(1550))
                    );
                    in->verbose(o.get(IO::VERBOSE, 0));
                    in->energy (o.get(IO::ENERGY,  1));
                    return in;
                }},
                /**
                 * --------------------------------------------------------------------------------
                 * message file 
                 * --------------------------------------------------------------------------------
                 */
                {SConnector::Key(IO::Type::MESSAGE_FILE), [](const SModule::Command::Group& o) {
                    auto in = Encoded::Message::IFileConnector::Make(
                        o.get(IO::URI)
                    );
                    in->verbose(o.get(IO::VERBOSE, 0));
                    in->energy (o.get(IO::ENERGY,  1));
                    return in;
                }}
            };
            try {
                return GENERATOR.at(
                    o.get(IO::TYPE, SConnector::Key(IO::Type::MESSAGE_FILE))
                )(o);
            } catch(...) {
                throw std::runtime_error(SText("invalid input connetor: ", o.get(IO::URI)));
            }
        }
    };
};
/**
 *---------------------------------------------------------------------------------------------------------------------
 * Output
 *---------------------------------------------------------------------------------------------------------------------
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
     * ----------------------------------------------------------------------------------------------------------------
     * Decoded Builder
     * ----------------------------------------------------------------------------------------------------------------
     */
    template <>
    struct Builder<Decoded::OConnector> {
        static inline Decoded::OConnector Build(const SModule::Command::Group& o) {
            static std::map<SConnector::Key, std::function <Decoded::OConnector(const SModule::Command::Group&)>> GENERATOR {
                /**
                 * --------------------------------------------------------------------------------
                 * message file 
                 * --------------------------------------------------------------------------------
                 */
                {SConnector::Key(IO::Type::MESSAGE_FILE), [](const SModule::Command::Group& o) {
                    auto out = Decoded::Message::OFileConnector::Make(
                        o.get(IO::URI)
                    );
                    out->verbose(o.get(IO::VERBOSE, 0));
                    out->energy (o.get(IO::ENERGY,  1));
                    return out;
                }},
                /**
                 * --------------------------------------------------------------------------------
                 * message local 
                 * --------------------------------------------------------------------------------
                 */
                {SConnector::Key(IO::Type::MESSAGE_LOCAL), [](const SModule::Command::Group& o) {
                    auto out = Decoded::Message::OLocConnector::Make(
                        o.get(IO::URI)
                    );
                    out->verbose(o.get(IO::VERBOSE, 0));
                    out->energy (o.get(IO::ENERGY,  1));
                    return out;
                }},
                /**
                 * --------------------------------------------------------------------------------
                 * message remote 
                 * --------------------------------------------------------------------------------
                 */
                {SConnector::Key(IO::Type::MESSAGE_REMOTE), [](const SModule::Command::Group& o) {
                    auto out = Decoded::Message::OUdpConnector::Make(
                        o.get(IO::URI)
                    );
                    out->verbose(o.get(IO::VERBOSE, 0));
                    out->energy (o.get(IO::ENERGY,  1));
                    return out;
                }},
                /**
                 * --------------------------------------------------------------------------------
                 * stream remote 
                 * --------------------------------------------------------------------------------
                 */
                {SConnector::Key(IO::Type::STREAM_REMOTE), [](const SModule::Command::Group& o) {
                    auto out = Decoded::Stream::OTcpConnector::Make(
                        o.get(IO::URI)
                    );
                    out->verbose(o.get(IO::VERBOSE, 0));
                    out->energy (o.get(IO::ENERGY,  1));
                    return out;
                }}
            };
            try{
                return GENERATOR.at(
                    o.get(IO::TYPE, SConnector::Key(IO::Type::MESSAGE_REMOTE))
                )(o);
            } catch(...) {
                throw std::runtime_error(SText("invalid output connetor: ", o.get(IO::URI)));
            }
        }
    };
    /**
     * ----------------------------------------------------------------------------------------------------------------
     * Encoded Builder
     * ----------------------------------------------------------------------------------------------------------------
     */
    template <>
    struct Builder<Encoded::OConnector> {
        static inline Encoded::OConnector Build(const SModule::Command::Group& o){
            static std::map<SConnector::Key, std::function <Encoded::OConnector(const SModule::Command::Group&)>> GENERATOR {
                /**
                 * --------------------------------------------------------------------------------
                 * message local 
                 * --------------------------------------------------------------------------------
                 */
                {SConnector::Key(IO::Type::MESSAGE_LOCAL), [](const SModule::Command::Group& o) {
                    auto out = Encoded::Message::OLocConnector::Make(
                        o.get(IO::URI),
                        o.get(IO::SFRAMES, size_t(1550))
                    );
                    out->verbose(o.get(IO::VERBOSE, 0));
                    out->energy (o.get(IO::ENERGY,  1));
                    return out;
                }},
                /**
                 * --------------------------------------------------------------------------------
                 * message file 
                 * --------------------------------------------------------------------------------
                 */
                {SConnector::Key(IO::Type::MESSAGE_FILE), [](const SModule::Command::Group& o) {
                    auto out = Encoded::Message::OFileConnector::Make(
                        o.get(IO::URI)
                    );
                    out->verbose(o.get(IO::VERBOSE, 0));
                    out->energy (o.get(IO::ENERGY,  1));
                    return out;
                }}
            };
            try {
                return GENERATOR.at(
                    o.get(IO::TYPE, SConnector::Key(IO::Type::MESSAGE_FILE))
                )(o);
            } catch(...) {
                throw std::runtime_error(SText("invalid output connetor: ", o.get(IO::URI)));
            }
        }
    };
}
/**
 *---------------------------------------------------------------------------------------------------------------------
 * (In|Out)put
 *---------------------------------------------------------------------------------------------------------------------
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
     * ----------------------------------------------------------------------------------------------------------------
     * Decoded Builder
     * ----------------------------------------------------------------------------------------------------------------
     */
    template <>
    struct Builder<Decoded::IOConnector> {
        static inline Decoded::IOConnector Build(const SModule::Command::Group& o) {
            static std::map<SConnector::Key, std::function <Decoded::IOConnector(const SModule::Command::Group&)>> GENERATOR {
                // {SConnector::Key(IO::Type::STREAM_LOCAL), [](const SModule::Command::Group& o) {
                //     auto io = Decoded::Stream::IOLocConnector::Make(
                //         o.get(IO::URI,     std::string("/tmp/data.y")),
                //         o.get(IO::NFRAMES, 50),
                //         o.get(IO::SFRAMES, 4096)
                //     );
                //     io->verbose(o.get(IO::VERBOSE, 0));
                //     io->energy (o.get(IO::ENERGY,  1));
                //     return io;
                // }},
                {SConnector::Key(IO::Type::MESSAGE_REMOTE), [](const SModule::Command::Group& o) {
                    auto in = Decoded::Message::IOUdpConnector::Make(
                        o.get(IO::URI),
                        o.get(IO::NFRAMES, size_t(50)),
                        o.get(IO::SFRAMES, size_t(1550))
                    );
                    in->verbose(o.get(IO::VERBOSE, 0));
                    in->energy (o.get( IO::ENERGY, 1));
                    return in;
                }}
            };
            try {
                return GENERATOR.at(
                    o.get(IO::TYPE, SConnector::Key(IO::Type::STREAM_REMOTE))
                )(o);
            } catch(...) {
                throw std::runtime_error(SText("invalid (in|out)put connetor: ", o.get(IO::URI)));
            }
        }
    };
    /**
     * ----------------------------------------------------------------------------------------------------------------
     * Encoded Builder
     * ----------------------------------------------------------------------------------------------------------------
     */
    template <>
    struct Builder<Encoded::IOConnector> {
        static inline Encoded::IOConnector Build(const SModule::Command::Group& o){
            static std::map<SConnector::Key, std::function <Encoded::IOConnector(const SModule::Command::Group&)>> GENERATOR {
                
            };
            try {
                return GENERATOR.at(
                    o.get(IO::TYPE, SConnector::Key(IO::Type::STREAM_REMOTE))
                )(o);
            } catch(...) {
                throw std::runtime_error(SText("invalid (in|out)put connetor: ", o.get(IO::URI)));
            }
        }
    };
}
}
/**
 *---------------------------------------------------------------------------------------------------------------------
 * End
 *---------------------------------------------------------------------------------------------------------------------
 */
#endif /* SMODULECONNECTORS_H */