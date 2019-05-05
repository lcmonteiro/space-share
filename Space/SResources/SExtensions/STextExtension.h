/**
 * ------------------------------------------------------------------------------------------------
 * File:   STextExtension.h
 * Author: Luis Monteiro
 *
 * Created on February 2612, 2019, 23:37
 * ------------------------------------------------------------------------------------------------
 */
#ifndef STEXTEXTENSION_H
#define STEXTEXTENSION_H
/**
 * space
 */
#include "SFrame.h"
#include "SText.h"
/**
 * ----------------------------------------------------------------------------
 * Text Extension
 * ----------------------------------------------------------------------------
 */
template <typename RESOURCE>
class STextExtension : public RESOURCE {
    using Super = RESOURCE; 
public:
    /**
     * ------------------------------------------------------------------------
     * From Super
     * ------------------------------------------------------------------------
     */
    using Super::Super;
    using Super::operator=;
    /**
     * ------------------------------------------------------------------------
     * Text IO functions
     * ------------------------------------------------------------------------
     * operator >>
     * ----------------------------------------------------
     */
    STextExtension& operator >>(SText& txt) {
        IOFrame in(1);
        /**
         * fill text
         */
        for (auto it = txt.begin(); txt.end() != it; ++it) {
            /**
             * receive
             */
            this->fill(in.clear());
            /**
             * verify end
             */
            if (::iscntrl(in.front())) {
                if (in.front() == '\r') {
                    this->fill(in.clear());
                }
                if(in.front() == '\n') {
                    txt.erase(it, txt.end());
                    break;
                }
                continue;
            }
            /**
             * set value
             */
            *it = in.front();
        }
        return *this;
    }
    /**
     * ----------------------------------------------------
     * operator <<
     * ----------------------------------------------------
     */
    STextExtension& operator<<(const SText& txt) {
        Super::drain(
            IOFrame(Frame(txt.begin(), txt.end())));
        return *this;
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SLINUXSOCKET_H */

