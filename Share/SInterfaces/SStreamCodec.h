/**
 * ------------------------------------------------------------------------------------------------
 * File:   SConnectorCodec.h
 * Author: Luis Monteiro
 *
 * Created on July 19, 2017, 5:22 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SSTREAMCODEC_H
#define SSTREAMCODEC_H
/**
 * std
 */
#include <map>
/**
 * space
 */
#include "SBuffer.h"
/**
 * share 
 */
#include "SEncoderCodec.h"
#include "SDecoderCodec.h"
#include "SDocument.h"
/**
 * ------------------------------------------------------------------------------------------------
 * SStreamCodec
 * ------------------------------------------------------------------------------------------------
 */
class SStreamCodec {
public:
    /**
     * --------------------------------------------------------------------------------------------    
     * Encode
     *---------------------------------------------------------------------------------------------
     */
    template<class IS, class OS, Codec::SStamp::Type T =Codec::SStamp::MESSAGE>
    static void Encode(
        IS in, std::vector<std::pair<size_t, OS>> out, size_t chunks, uint64_t seed
        ) {
        typedef typename IS::char_type* ipointer;
        typedef typename OS::char_type* opointer;
        /**
         *  container
         */
        auto box = Container(chunks);
        /**
         * stream size
         */
        auto len = __size(in);
        /**
         * compute frame size
         */
        auto sz = __split(len, chunks);
        /**
         * insert length -> buffer 
         */
        auto buff  = Buffer(Frame().number(filesize_t(len)));
        auto frame = IOFrame(sz);
        for (__fill(buff, frame); frame.full(); __fill(buff, frame)) {
            box.emplace_back(frame.detach());
            frame = IOFrame(sz);
        }
        /**
         * insert data
         */
        for (__fill(in, frame); !box.full(); __fill(in, frame)) {
            box.emplace_back(frame.detach());
            frame = IOFrame(sz);
        }
        /**
         * create stamp
         */
        auto stamp = Codec::SStamp::Generate(T, seed);
        /**
         * create encoder
         */ 
        auto en = Codec::SEncoder(std::move(box), stamp);
        /**
         * drain coded data to output stream
         */
        for (auto& o : out) {
            en.frame_count(o.first);
            for (auto& d : en.pop()) {
                o.second.write(opointer(d.data()), d.size());
            }
        }
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Decode
     *---------------------------------------------------------------------------------------------
     */
    template<class IS, class OS, Codec::SStamp::Type T =Codec::SStamp::MESSAGE>
    static void Decode(
        std::vector<std::pair<size_t, IS>> in, OS out, size_t chunks, uint64_t seed
        ) {
        typedef typename IS::char_type* ipointer;
        typedef typename OS::char_type* opointer;
        /**
         *  sort in-streams
         */
        for (auto& s : __selector(std::move(in))) {
            Container box(chunks);
            /**
             *  fill box
             */
            for (auto& ss : s.second) {
                auto frame = IOFrame(s.first);
                for (__fill(ss, frame); frame.full(); __fill(ss, frame)) {
                    box.emplace_back(frame.detach());
                    frame = IOFrame(s.first);
                }
            }
            /**
             * create stamp
             */
            auto stamp = Codec::SStamp::Generate(T, seed);
            /**
             * create decoder
             */
            auto data = Codec::SDecoder(chunks, std::move(box), stamp).pop();
            /**
             * remove lenhgt
             */
            auto it   = data.begin();
            auto end  = data.end();
            auto ifrm = IOFrame(sizeof(filesize_t));
            auto ofrm = IOFrame();
            for (; (it != end) && (!ifrm.full()); ++it) {
                ofrm = IOFrame(std::move(*it));
                ofrm.fill(ifrm);
            }
            size_t len = ifrm.number<filesize_t>();
            /**
             *  drain out-frame 
             */
            out.write(opointer(ofrm.data()), ofrm.size());
            /**
             *  write
             */
            for (; (it != end) && (out.tellp() < (len - it->size())); ++it) {
                out.write(opointer(it->data()), it->size());
            }
            /**
             * write last
             */
            if (it != end) {
                out.write(opointer(it->data()), len - out.tellp());
            }
        }
    }
private:
    /**
     * --------------------------------------------------------------------------------------------
     * Helpers
     * --------------------------------------------------------------------------------------------
     * Split
     * ------------------------------------------------------------------------
     */
    inline static size_t __split(size_t len, size_t chunks) {
        auto ref = div(
            int(len) + sizeof(filesize_t), 
            int(chunks)
        );
        return ref.rem == 0 ? ref.quot : ref.quot + 1;
    }
    /**
     * ------------------------------------------------------------------------
     * Size 
     * ------------------------------------------------------------------------
     */
    template<class IS>
    static size_t __size(IS& s) {
        s.seekg (0, s.end);
        size_t len = s.tellg();
        s.seekg (0, s.beg);
        return len;
    }
    /**
     * ------------------------------------------------------------------------
     * Fill 
     * ------------------------------------------------------------------------
     */
    template<class IS>
    static void __fill(IS& s, IOFrame& f) {
        typedef typename IS::char_type* ipointer;
        do{ 
            f.insert(s.readsome(ipointer(f.idata()), f.isize())); 
        } while (s.gcount());
    }
    /**
     * ------------------------------------------------------------------------
     * Select files
     * ------------------------------------------------------------------------
     */
    template<class IS>
    static auto __selector(std::vector<std::pair<size_t, IS>> in) {
        std::map<size_t, std::vector<IS>> out;
        for(auto& s : in){
            auto ref = std::div(__size(s.second), int(s.first));
            if(ref.rem == 0) {
                auto it = out.find(ref.quot);
                if (it != out.end()) {
                    it->second.emplace_back(std::move(s.second));
                } else {
                    std::vector<IS> tmp;
                    tmp.emplace_back(std::move(s.second));
                    out[ref.quot] = std::move(tmp);
                }
            }
        }
        return out;
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SSTREAMCODEC_H */

