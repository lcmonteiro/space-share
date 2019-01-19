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
/**
 * ------------------------------------------------------------------------------------------------
 * Text
 * ------------------------------------------------------------------------------------------------
 */
class SText : public std::string {
public:
	/**
	 * --------------------------------------------------------------------
	 * constructor
	 * --------------------------------------------------------------------
	 * empty
     */
    using std::string:string;
    /**
	 * native types
	 */
    SText(int    v): std::string(__Set(v)) {}
    SText(float  v): std::string(__Set(v)) {}
    SText(double v): std::string(__Set(v)) {}
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
        istringstream(s) >> val;
        return val;
    }
    /**
     * set
     */
    template <class T>
    static inline std::string  __Set(T v) {
        ostringstream o;
        o << val;
        return o.str();
    }
};

#endif /* STEXT_H */

