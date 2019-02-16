/* 
 * Container:   SCommandMonitor.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SCOMMANDMONITOR_H
#define SCOMMANDMONITOR_H
/**
 * space
 */
#include <SContainer.h>
#include <SAddress.h>
/**
 * -------------------------------------------------------------------------------------------------
 * command monitor
 * -------------------------------------------------------------------------------------------------
 */
template<class C, class R>
class SCommandMonitor {
public:
    /**
     * ------------------------------------------------------------------------
     * helpres
     * ------------------------------------------------------------------------
     */
    using Command  = C;
    using Resource = R;
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    SCommandMonitor(const SAddress& add) : __res() {
        __res.Bind(add.Host());
    }
    /**
     * ------------------------------------------------------------------------
     * get resource
     * ------------------------------------------------------------------------
     */
    inline Resource& GetResource() {
        return __res;
     }
    /**
     * ------------------------------------------------------------------------
     * read command
     * ------------------------------------------------------------------------
     */
    inline Command Read(size_t max = 1024) {
        SFrame frame(max);

        //read data up to max -----------------------------
        __res.Fill(frame);
        
        // create a comand (by parse a command) -----------
        return Command(SText(frame.begin(), frame.end()));
    }
private:
    /**
     * resource
     */
    Resource __res;
};
/**
 * -------------------------------------------------------------------------------------------------
 * end
 * -------------------------------------------------------------------------------------------------
 */
#endif /* SCOMMANDMONITOR_H */

