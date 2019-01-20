/**
 * File:   SText.h
 * Author: Luis Monteiro
 *
 * Created on January 15, 2019, 20:23 PM
 */
#ifndef STEXT_H
#define STEXT_H
/**
 * std
 */
#include <string>
#include <sstream>
/**
 * ------------------------------------------------------------------------------------------------
 * Text
 * ------------------------------------------------------------------------------------------------
 */
class SText : public std::string {
public:
    using Super = std::string;
	/**
	 * --------------------------------------------------------------------
	 * constructor
	 * --------------------------------------------------------------------
	 * empty
     */
    using Super::Super;
    /**
	 * native types
	 */
    SText(int    v): std::string(__Set(v)) {}
    SText(float  v): std::string(__Set(v)) {}
    SText(double v): std::string(__Set(v)) {}
    /**
     * mix types
     */
    template<typename T, typename... Ts>
    SText(T arg, Ts... args) {
        std::ostringstream result;
        result << arg;
        int steps[] = { 
            (result << args, 0)... 
        };
        assign(result.str());
    }
    /**
     * --------------------------------------------------------------------
     * interfaces
     * --------------------------------------------------------------------
     * get native types
     */
    inline operator int()    { return __Get<int>(*this);    }
    inline operator float()  { return __Get<float>(*this);  }
    inline operator double() { return __Get<double>(*this); }
protected:
    /**
     * --------------------------------------------------------------------
     * converters
     * --------------------------------------------------------------------
     * get
     */
    template <class T>
    static inline T __Get(std::string& s) {
        T val;
        std::istringstream(s) >> val;
        return val;
    }
    /**
     * set
     */
    template <class T>
    static inline std::string  __Set(T val) {
        std::ostringstream o;
        o << val;
        return o.str();
    }
};

#endif /* STEXT_H */

