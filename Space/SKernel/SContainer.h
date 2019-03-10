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
 * std
 */
#include <vector>
#include <ostream>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <stdexcept>
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
     * using from supper 
     **/
    using Super::Super;
    using Super::operator=;
    /**
     * ----------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SContainer(size_t capacity) : Super() {
        reserve(capacity);
    }
    /**
     * ----------------------------------------------------
     * reset
     * ----------------------------------------------------
     */
    inline SContainer& Reset() {
        clear(); 
        return *this;
    }
    /**
     * ----------------------------------------------------
     * append list buffer
     * ---------------------------------------------------
     */
    inline SContainer& Append(const SContainer& buffer) {
        insert(end(), buffer.begin(), buffer.end());
        return *this;
    }
    /**
     * ----------------------------------------------------
     *  check size
     * ----------------------------------------------------
     */
    inline size_t Capacity() const {
        return capacity();
    }
    inline size_t Size() const {
        return size();
    }
    inline bool Full() const {
        return (size() == capacity());
    }
    /**
     * ----------------------------------------------------
     * detach  
     * ----------------------------------------------------
     */
    inline SContainer&& Detach() {
        return std::move(*this);
    }
} Container;
/**
 * ------------------------------------------------------------------------------------------------
 * utilities
 * ------------------------------------------------------------------------------------------------
 **/
inline std::ostream& operator<<(std::ostream& os, const Container& l) {
    os << "[" << std::endl;
    for (auto v : l) {
        os << " " << v << std::endl;
    }
    return os << "]";
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 **/
#endif /* SSCONTAINER_H */

