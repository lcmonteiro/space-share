/**
 * ------------------------------------------------------------------------------------------------
 * File:   SContainer.h
 * Author: Luis Monteiro
 *
 * Created on November 23, 2016, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SCONTAINER_H
#define SCONTAINER_H
/**
 * space
 */
#include "SFrame.h"
#include "SText.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Exceptions
 * ------------------------------------------------------------------------------------------------
 **/
typedef class SContainerException : public std::range_error {
public:
    using std::range_error::range_error;
} ContainerException;
/**
 * ------------------------------------------------------------------------------------------------
 * Container
 * ------------------------------------------------------------------------------------------------
 **/
typedef class SContainer : public std::vector<Frame> {
public:
    using Super = std::vector<Frame>;
    /**
     * ------------------------------------------------------------------------
     * Using from supper 
     * ------------------------------------------------------------------------
     **/
    using Super::Super;
    using Super::operator=;
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     */
    SContainer(size_t capacity) : Super() {
        reserve(capacity);
    }
    /**
     * ------------------------------------------------------------------------
     * Clear container
     * ------------------------------------------------------------------------
     */
    inline SContainer& clear() {
        Super::clear(); return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Push a frame container
     * ------------------------------------------------------------------------
     */
    template<typename Container>
    SContainer& push(const Container& c) {
        Super::insert(end(), c.begin(), c.end());
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Check size
     * ------------------------------------------------------------------------
     */
    inline bool full() const {
        return (size() == capacity());
    }
    /**
     * ------------------------------------------------------------------------
     * Set number
     * ------------------------------------------------------------------------
     */
    template <class T>
    SContainer& number(T val) {
        /**
         * prepare iterator
         */
        auto s = Itertool::BuildStretch(*this);
        /**
         * encode number
         */
        Itertool::SetNumber(s.rbegin(), s.rend(), val);
        /**
         * return itself
         */ 
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Get number
     * ------------------------------------------------------------------------
     */
    template <typename Type>
    Type number() const {
        /**
         * prepare iterator
         */
        auto s = Itertool::BuildStretch(*this);
        /**
         * decode number
         */
        return Itertool::GetNumber<Type>(s.rbegin(), s.rend());
    }
    /**
     * ------------------------------------------------------------------------
     * Detach  
     * ------------------------------------------------------------------------
     */
    inline SContainer&& detach() {
        return std::move(*this);
    }
} Container;
/**
 * ------------------------------------------------------------------------------------------------
 * Utilities
 * ------------------------------------------------------------------------------------------------
 **/
inline std::ostream& operator<<(std::ostream& os, const SContainer& c) {
    os << "[" << std::endl;
    for (auto v : c) {
        os << " " << v << std::endl;
    }
    return os << "]";
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 **/
#endif /* SSCONTAINER_H */

