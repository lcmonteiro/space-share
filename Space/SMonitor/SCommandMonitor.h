/* 
 * Container:   SCommandMonitor.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SCOMMANDMONITOR_H
#define SCOMMANDMONITOR_H
#include <string>
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
        using Filter   = typename Command::Filter;
        using Options  = typename Command::Options;
	/**
	 * constructor
	 */
	SCommandMonitor(std::string& uri, Filter filter) : __res(), __filter(filter) {
                __res.Bind(uri);
	}
	/**
	 * destructor
	 */
	virtual ~SCommandMonitor() = default;
	/**
         * get resource
         */
        inline Resource& GetResource() {
		return __res;
	}
        /**
         * read command
         */
        inline Options Read(size_t max = 1024) {
                Frame frame(max);
                /**
                 * read data
                 */
                __res.Fill(frame);
                /**
                 * parse data
                 */
                return Command::Unserialize(__filter, string(frame.begin(), frame.end()));
        }
private:
        /**
         * resource
         */
	R __res;
        /**
         * filter
         */
        Filter __filter;
};
/**
 */
#endif /* SCOMMANDMONITOR_H */

