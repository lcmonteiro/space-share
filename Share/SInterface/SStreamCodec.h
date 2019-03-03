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
 * Share Kernel
 */
#include "SCodec.h"
#include "SBuffer.h"
#include "SDocument.h"
/**
 * ------------------------------------------------------------------------------------------------
 * SStreamCodec
 * ------------------------------------------------------------------------------------------------
 */
class SStreamCodec {
public:
    /**
     * ------------------------------------------------------------------------    
     * Encode
     *-------------------------------------------------------------------------
     */
    template<class IS, class OS, CodecStamp::Type T =CodecStamp::MESSAGE>
    static void Encode(IS in, std::vector<std::pair<size_t, OS>> out, size_t chunks, uint64_t seed) {
        typedef typename IS::char_type* ipointer;
        typedef typename OS::char_type* opointer;
        /**
         */
        Container box(chunks);
        /**
         * get end position
         */
        size_t len = Size(in);
        /**
         * compute frame size 
         */
        size_t sz = Split(len, chunks);
        /**
         * insert length
         */   
        Buffer buff(Frame().Number(filesize_t(len)));
        //
        auto frame = IFrame(sz);
        //
        for (Fill(buff, frame); frame.Full(); Fill(buff, frame)){
            //
            box.emplace_back(move(frame));
            frame = IFrame(sz);
        }
        /**
         * insert data
         */
        for (Fill(in, frame); !box.Full(); Fill(in, frame)){
            //
            box.emplace_back(std::move(frame));
            frame = IFrame(sz);
        }
        /**
         * create stamp
         */
        auto stamp = CodecStamp::Generate(T, seed);
        /**
         * create encoder
         */
        CodecEncoder en(std::move(box), stamp);
        /**
         * drain coded data to OS
         */
        for (auto& o : out) {
            en.length(o.first);
            for (auto& d : en.pop()) {
                o.second.write(opointer(d.data()), d.size());
            }
        }
    }
    /**
     * ------------------------------------------------------------------------
     * Decode
     *-------------------------------------------------------------------------
     */
    template<class IS, class OS, CodecStamp::Type T =CodecStamp::MESSAGE>
    static void Decode(std::vector<std::pair<size_t, IS>> in, OS out, size_t chunks, uint64_t seed) {
        typedef typename IS::char_type* ipointer;
        typedef typename OS::char_type* opointer;
        /**
         * sort istreams 
         */
        for (auto& s : Selector(std::move(in))) {
            Container box(chunks);
            /**
             */
            for (auto& ss : s.second) {
                /** 
                 * fill box
                 */
                auto frame = IFrame(s.first);
                //
                for (Fill(ss, frame); frame.Full(); Fill(ss, frame)) {
                    //
                    box.emplace_back(std::move(frame));
                    frame = IFrame(s.first);
                }
            }
            /**
             * create stamp
             */
            auto stamp = CodecStamp::Generate(T, seed);
            /**
             * decoder
             */
            auto data = CodecDecoder(chunks, std::move(box), stamp).pop();
            /**
             * iterators
             */
            auto it = data.begin(), end = data.end();
            /**
             * remove length length
             */
            auto iframe = IFrame(sizeof(filesize_t));
            auto oframe = OFrame();
            for (; (it != end) && (!iframe.Full()); ++it) {
                oframe = OFrame(std::move(*it));
                oframe.Fill(iframe);
            }
            size_t len = iframe.Number<filesize_t>();
            /**
             * drain oframe
             */
            out.write(opointer(oframe.Data()), oframe.Size());
            /**
             * write 
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
     * --------------------------------------------------------------------
     * Helpers
     * --------------------------------------------------------------------
     ** 
     * Split
     */
    inline static size_t Split(size_t len, size_t chunks){
        auto ref = div(
            int(len) + sizeof(filesize_t), 
            int(chunks)
        );
        return ref.rem == 0 ? ref.quot : ref.quot + 1;
    }
    /**
     * Size 
     */
    template<class IS>
    static size_t Size(IS& s){
        s.seekg (0, s.end);
        size_t len = s.tellg();
        s.seekg (0, s.beg);
        return len;
    }
    /**
     * Fill 
     */
    template<class IS>
    static void Fill(IS& s, IFrame& f){
        typedef typename IS::char_type* ipointer;
        do{ 
            f.Insert(s.readsome(ipointer(f.Data()), f.Size())); 
        } while (s.gcount());
    }
    /**
     * Select files
     */
    template<class IS>
    static std::map<size_t, std::vector<IS>> Selector(std::vector<std::pair<size_t, IS>> in){
        std::map<size_t, std::vector<IS>> out;
        for(auto& s : in){
            auto ref = std::div(Size(s.second), int(s.first));
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
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SSTREAMCODEC_H */

