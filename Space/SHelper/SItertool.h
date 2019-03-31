/**
 * -------------------------------------------------------------------------------------------------------------------- 
 * File:   SItertool.h
 * Author: Luis Monteiro
 *
 * Created on March 26, 2019, 12:03 PM
 * --------------------------------------------------------------------------------------------------------------------
 */
#ifndef SITERTOOL_H
#define SITERTOOL_H
/**
 * std
 */
#include <functional>
#include <iterator>
/**
 * --------------------------------------------------------------------------------------------------------------------
 * namespace Itertool
 * --------------------------------------------------------------------------------------------------------------------
 */
namespace Itertool {
/**
 * --------------------------------------------------------------------------------------------------------------------
 * Stretch - container dimension reduction
 * --------------------------------------------------------------------------------------------------------------------
 */
template<typename C>
class Stretch { 
public:
    /**
     * --------------------------------------------------------------------------------------------
     * constructor
     * --------------------------------------------------------------------------------------------
     **/
    Stretch(C& c) : __ref(c) {}
    /**
     * --------------------------------------------------------------------------------------------
     * iterator - class
     * --------------------------------------------------------------------------------------------
     **/
    struct Forward: public std::iterator<
        std::forward_iterator_tag, typename C::value_type::value_type> {
        using iterator1 = typename C::iterator; 
        using iterator2 = typename C::value_type::iterator;
        template <typename T>
        auto end(T& i)   { return i->end();   }
        template <typename T>
        auto begin(T& i) { return i->begin(); }
    };
    struct Backward: public std::iterator<
        std::forward_iterator_tag, typename C::value_type::value_type> {
        using iterator1 = typename C::reverse_iterator; 
        using iterator2 = typename C::value_type::reverse_iterator;
        template <typename T>
        auto end(T& i)   { return i->rend();   }
        template <typename T>
        auto begin(T& i) { return i->rbegin(); }
    };
    template<typename Super>
    class Iterator: public Super {
    public:  
        using reference = typename Super::reference;
        using iterator1 = typename Super::iterator1;
        using iterator2 = typename Super::iterator2;
        /**
         * --------------------------------------------------------------------
         * default
         * --------------------------------------------------------------------
         */
        Iterator() = default;
        Iterator(const Iterator&) = default;
        /**
         * --------------------------------------------------------------------
         * operators
         * --------------------------------------------------------------------
         */
		Iterator& operator++() {
			if(next(__it2) == end(__it1))
                if(next(__it1) != __end) 
                    __it2 = begin(__it1); 
            return *this;
		}
		reference operator*() {
			return *__it2;
		}
		bool operator==(const Iterator& it) {
			return (equal(__it1, it.__it1)) 
                && (equal(__it2, it.__it2) || equal(__it1, __end));
		}
		bool operator!=(const Iterator& it) {
			return (!equal(__it1, it.__it1)) 
                || (!equal(__it2, it.__it2) && !equal(__it1, __end));
		}
    protected:
        friend class Stretch;
        /**
         * --------------------------------------------------------------------
         * constructor
         * --------------------------------------------------------------------
         */
        Iterator(iterator1 end, iterator1 beg):
        __end(end), __it1(beg), 
        __it2(equal(end, beg)?iterator2():begin(beg)) {}

        Iterator(iterator1 end):
        __end(end), __it1(end), __it2() {}
        /**
         * --------------------------------------------------------------------
         * helpers
         * --------------------------------------------------------------------
         */
        template <typename T>
        T& next(T& i) { return ++i; }
        template <typename T>
        bool equal(const T& t1, const T& t2) { return t1==t2; }
    private:
        /**
         * --------------------------------------------------------------------
         * variables
         * --------------------------------------------------------------------
         */
        iterator1 __end;
        iterator1 __it1;
        iterator2 __it2;
    };
    /**
     * --------------------------------------------------------------------------------------------
     * iterator - functions
     * --------------------------------------------------------------------------------------------
     **/
    Iterator<Forward> begin() {
        return Iterator<Forward>(__ref.end(), __ref.begin());
    }
    Iterator<Backward> rbegin() {
        return Iterator<Backward>(__ref.rend(), __ref.rbegin());
    }
    Iterator<Forward> end() {
        return Iterator<Forward>(__ref.end());
    }
    Iterator<Backward> rend() {
        return Iterator<Backward>(__ref.rend());
    }
    /**
     * --------------------------------------------------------------------------------------------
     * standard - functions
     * --------------------------------------------------------------------------------------------
     */  
    inline size_t size() {
        return std::distance(begin(), end());
    }
private:
    /**
     * --------------------------------------------------------------------------------------------
     * Variables
     * --------------------------------------------------------------------------------------------
     **/
    C& __ref;
};
/**
 * --------------------------------------------------------------------------------------------------------------------
 * Functional
 * --------------------------------------------------------------------------------------------------------------------
 * encode - number
 * ------------------------------------------------------------------------------------------------ 
 * set
 * ----------------------------------------------------------------------------
 */
template <typename Iterator, typename Number>
Iterator SetNumber(Iterator it, Iterator end, Number val) {
    using value_type = typename Iterator::value_type;

    // encode number ----------------------------------
    for (auto i = 0; (i < sizeof(val)) && (it != end); ++it, ++i) {
        *it = value_type(val);
        val >>= 8;
    }
    // return current position ------------------------
    return it;
}
/**
 * ----------------------------------------------------------------------------
 * get
 * ----------------------------------------------------------------------------
 */
template <typename Iterator, class Number>
Number GetNumber(Iterator it, Iterator end) {
    auto i = 0;
    // set iterator position --------------------------
    for (; (i < sizeof(Number)) && (it != end); ++i, ++it);

    // decode number ----------------------------------
    Number num = 0;
    for (; (i > 0); --i, --it) {
        num <<= 8;
        num |= Number(*it);
    }
    // return number ----------------------------------
    return num;
}
}
/**
 * --------------------------------------------------------------------------------------------------------------------
 * End
 * --------------------------------------------------------------------------------------------------------------------
 **/
#endif /* SITERTOOL_H */