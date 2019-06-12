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
template<typename Container>
class Stretch { 
public:
    /**
     * --------------------------------------------------------------------------------------------
     * Constructor
     * --------------------------------------------------------------------------------------------
     **/
    Stretch(Container& c) : __ref(c) {}
    /**
     * --------------------------------------------------------------------------------------------
     * Iterator - class
     * --------------------------------------------------------------------------------------------
     **/
    struct Forward: public std::iterator<
        std::forward_iterator_tag, typename Container::value_type::value_type> {
        using iterator1 = decltype(Container().begin());
        using iterator2 = decltype(Container().begin()->begin());
        template <typename T>
        auto end(T& i)   { return i->end();   }
        template <typename T>
        auto begin(T& i) { return i->begin(); }
    };
    struct Backward: public std::iterator<
        std::forward_iterator_tag, typename Container::value_type::value_type> {
        using iterator1 = decltype(Container().rbegin());
        using iterator2 = decltype(Container().rbegin()->rbegin());
        template <typename T>
        auto end(T& i)   { return i->rend();   }
        template <typename T>
        auto begin(T& i) { return i->rbegin(); }
    };
    template<typename Super>
    class Iterator: public Super {
    public:  
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
		auto& operator++() {
            for(next(__it2); __it2 == end(__it1); __it2 = begin(__it1)) {
                if(next(__it1) == __end) {
                    return *this;
                }
            }
            return *this;
		}
        auto& operator--() {
            for(; __it2 == begin(__it1); __it2 = end(__it1)) {
                if(__it1 == __beg) {
                    return *this;
                } prev(__it1);
            } prev(__it2);
            return *this;
		}
		auto& operator*() {
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
        Iterator(iterator1 beg, iterator1 it, iterator1 end):
        __beg(beg), 
        __end(end), 
        __it1(it), 
        __it2(equal(it, end) ? iterator2() : begin(beg)) {}
        /**
         * --------------------------------------------------------------------
         * helpers
         * --------------------------------------------------------------------
         */
        template <typename T>
        T& next(T& i) { return ++i; }
        template <typename T>
        T& prev(T& i) { return --i; }
        template <typename T>
        bool equal(const T& t1, const T& t2) { return t1==t2; }
    private:
        /**
         * --------------------------------------------------------------------
         * variables
         * --------------------------------------------------------------------
         */
        iterator1 __end;
        iterator1 __beg;
        iterator1 __it1;
        iterator2 __it2;
    };
    /**
     * --------------------------------------------------------------------------------------------
     * Iterator - Functions
     * --------------------------------------------------------------------------------------------
     **/
    auto begin()  const {
        return Iterator<Forward>(__ref.begin(),   __ref.begin(),  __ref.end());
    }
    auto rbegin() const {
        return Iterator<Backward>(__ref.rbegin(), __ref.rbegin(), __ref.rend());
    }
    auto end()  const {
        return Iterator<Forward>(__ref.begin(),   __ref.end(),    __ref.end());
    }
    auto rend() const {
        return Iterator<Backward>(__ref.rbegin(), __ref.rend(),   __ref.rend());
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Standard - Functions
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
     * container reference
     **/
    Container& __ref;
};
/**
 * --------------------------------------------------------------------------------------------------------------------
 * Build
 * --------------------------------------------------------------------------------------------------------------------
 **/
template<typename Container>
static inline auto BuildStretch(Container& c) {
    return Stretch<Container>(c); 
} 
/**
 * --------------------------------------------------------------------------------------------------------------------
 * Functional
 * --------------------------------------------------------------------------------------------------------------------
 * Set - Encode Number
 * ----------------------------------------------------------------------------
 */
template <typename Iterator, typename Number>
Iterator SetNumber(Iterator it, Iterator end, Number val) {
    using value_type = typename Iterator::value_type;
    /**
     * encode number 
     */
    for (auto i = 0; (i < sizeof(val)) && (it != end); ++it, ++i) {
        *it = value_type(val);
        val >>= 8;
    }
    /**
     * return current position
     */
    return it;
}
/**
 * ----------------------------------------------------------------------------
 * Get - decode Number
 * ----------------------------------------------------------------------------
 */
template <class Number, typename Iterator>
Number GetNumber(Iterator it, Iterator end) {
    auto i = 0;
    /**
     * set iterator position
     */
    for (; (i < sizeof(Number)) && (it != end); ++i, ++it);
    /**
     * decode number
     */
    Number num = 0;
    for (--it; i > 0; --i, --it) {
        num <<= 8;
        num |= Number(*it);
    }
    /**
     * return number
     */
    return num;
}
}
/**
 * --------------------------------------------------------------------------------------------------------------------
 * End
 * --------------------------------------------------------------------------------------------------------------------
 **/
#endif /* SITERTOOL_H */