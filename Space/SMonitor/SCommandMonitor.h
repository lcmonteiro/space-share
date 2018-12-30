/* 
 * Container:   SCommandMonitor.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SCOMMANDMONITOR_H
#define SCOMMANDMONITOR_H
/**
 * Space
 */
#include <SContainer.h>
#include <SAddress.h>
/**
 */
using namespace std;
/**
 */
template<class C, class R>
class SCommandMonitor {
public:
        /**
         * types
         */
        using Command  = C;
        using Resource = R;
	/**
	 * constructor
	 */
	SCommandMonitor(const SAddress& add) : __res() {
                __res.Bind(add.Host());
	}
	/**
	 * destructor
	 */
	virtual ~SCommandMonitor() = default;
	/**
         * get resource
         */
        inline Resource& resource() {
		return __res;
	}
        /**
         * read command
         */
        inline Command Read(size_t max = 1024) {
                SFrame frame(max);
                //read data up to max 
                __res.fill(frame);
                // create a comand (by parse a command)
                return Command(string(frame.begin(), frame.end()));
        }
private:
        /**
         * resource
         */
	Resource __res;
};
/**
 */
#endif /* SCOMMANDMONITOR_H */

