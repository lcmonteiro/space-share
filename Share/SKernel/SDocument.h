/**
 * ------------------------------------------------------------------------------------------------
 * File:   SDocument.h
 * Author: Luis Monteiro
 *
 * Created on February 10, 2019, 16:21
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SDOCUMENT_H
#define SDOCUMENT_H
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
#include "SContainer.h"
/**
 * -------------------------------------------------------------------------------------------------
 * Definitions
 * -------------------------------------------------------------------------------------------------
 **/
typedef uint64_t filesize_t;
typedef uint32_t reference_t;
typedef uint16_t framecount_t;
typedef uint32_t framesize_t;
/**
 * ------------------------------------------------------------------------------------------------
 * Decoded
 * ------------------------------------------------------------------------------------------------
 **/
namespace Decoded {
/**
 * ----------------------------------------------------------------------------
 * Document
 * ----------------------------------------------------------------------------
 **/
typedef class SDocument : public Container {
public:
    /**
     * ----------------------------------------------------
     * Defaults
     * ----------------------------------------------------
     * constructors
     * --------------------------------
     */
    SDocument()                 = default;
    SDocument(SDocument&&)      = default;
    SDocument(const SDocument&) = default;
    /**
     * --------------------------------
     * operatores
     * --------------------------------
     */
    SDocument& operator=(SDocument&&)      = default;
    SDocument& operator=(const SDocument&) = default;
    /**
     * ----------------------------------------------------
     * Container Constructor
     * ----------------------------------------------------
     */
    SDocument(SContainer&& ctn) 
    : Container(std::move(ctn)) {}

    SDocument(const SContainer& ctn) 
    : Container(ctn) {}
    /**
     * --------------------------------
     * operatores
     * --------------------------------
     */
    using Container::Container;
    using Container::operator=;
} Document;
}
/**
 * ------------------------------------------------------------------------------------------------
 * Encoded
 * ------------------------------------------------------------------------------------------------
 **/
namespace Encoded {
/**
 * ----------------------------------------------------------------------------
 * Context
 * ----------------------------------------------------------------------------
 **/
typedef class SContext {
public:
    /**
     * ----------------------------------------------------
     * defaults
     * ----------------------------------------------------
     * constructors
     * --------------------------------
     */
    SContext(SContext&&     ) = default;
    SContext(const SContext&) = default;
    /**
     * --------------------------------
     * destructor
     * --------------------------------
     */
    virtual ~SContext() = default;
    /**
     * --------------------------------
     * operators
     * --------------------------------
     */
    SContext& operator=(SContext&&     ) = default;
    SContext& operator=(const SContext&) = default;
    /**
     * ----------------------------------------------------
     * Constructors
     * ----------------------------------------------------
     */
    SContext()
    : __init(0),
     __pos(0), __n_frames(0), __frame_sz(0) {}

    SContext(size_t pos, size_t n_frames)
    : __init(2), 
    __pos(pos), __n_frames(n_frames), __frame_sz(0) {}

    SContext(size_t pos, size_t n_frames, size_t frame_sz)
    : __init(3), 
    __pos(pos), __n_frames(n_frames), __frame_sz(frame_sz) {}
    /**
     * ----------------------------------------------------
     * interfaces
     * ----------------------------------------------------
     * getters 
     * --------------------------------
     */
    inline reference_t position() const {
        return __pos;
    }
    inline framecount_t frame_count() const {
        return __n_frames;
    }
    inline framesize_t frame_size() const {
        return __frame_sz;
    }
    /**
     * --------------------------------
     * operator
     * ---------------------------------
     */
    inline bool operator<(const SContext& context) const {
        return __pos < context.__pos;
    }
protected:
    /**
     * ----------------------------------------------------
     * variables
     * ----------------------------------------------------
     */
    size_t       __init;
    reference_t  __pos;
    framecount_t __n_frames;
    framesize_t  __frame_sz;
} Context;
/**
 * ----------------------------------------------------------------------------
 * Base Document
 * ----------------------------------------------------------------------------
 **/
typedef class SDocument : public Container, public Context {
public:
    /**
     * ----------------------------------------------------
     * Defaults
     * ----------------------------------------------------
     * constructors
     */
    SDocument()                 = default;
    SDocument(SDocument&&)      = default;
    SDocument(const SDocument&) = default;
    /**
     * operatores
     */
    SDocument& operator=(SDocument&&)      = default;
    SDocument& operator=(const SDocument&) = default;
    /**
     * ----------------------------------------------------
     * Context Constructor
     * ----------------------------------------------------
     */
    SDocument(Context&& ctx) 
    : Container(), Context(std::move(ctx)) {}

    SDocument(const SContext& ctx) 
    : Container(), Context(ctx) {}
    /**
     * ----------------------------------------------------
     * Container Constructor
     * ----------------------------------------------------
     */
    SDocument(SContainer&& ctn) 
    : Container(std::move(ctn)), Context() {}

    SDocument(const SContainer& ctn) 
    : Container(ctn), Context() {}
    /**
     * ----------------------------------------------------
     * Container&Context Constructor
     * ----------------------------------------------------
     */
    SDocument(SContainer&& ctn, SContext&& ctx) 
    : Container(std::move(ctn)), Context(std::move(ctx)) {}

    SDocument(const SContainer& ctn, const SContext& ctx) 
    : Container(ctn), Context(ctx) {}
    /**
     * ----------------------------------------------------
     * Interfaces
     * ----------------------------------------------------
     **
     * remove n elements
     */
    inline SDocument remove(int n) {
        SDocument d(Context(*this));
        d.reserve(n);
        while(n--) {
            d.push_back(std::move(back()));
            pop_back();
        }
        return d;
    }
    /**
     * insert elements
     */
    inline SDocument& insert(SDocument doc) {
        std::move(
            std::begin(doc), 
            std::end(doc), 
            std::back_inserter(*this));
        return *this;
    }
    /**
     * split context and container
     */
    inline std::pair<Context, Container> split() const {
        return {
            std::move(*this), 
            std::move(*this)
        };
    }
} Document;
/**
 * -----------------------------------------------------------------------------
 * Input Document
 * -----------------------------------------------------------------------------
 */
typedef class SIDocument : public SDocument {
public:
    using SDocument::SDocument;
    /**
     * ----------------------------------------------------
     * Default Constructors
     * -----------------------------------------------------
     */
    SIDocument() : __capacity(0) {}

    SIDocument(SIDocument&& d) = default;

    SIDocument(const SIDocument& d) = default;
    /**
     * ----------------------------------------------------
     * Operatores
     * ----------------------------------------------------
     **
     * move operator
     */
    SIDocument& operator=(SIDocument&& doc) = default;
    /**
     * copy operator
     */
    SIDocument& operator=(const SIDocument& doc) = default;
    /**
     * ----------------------------------------------------
     * Push Data
     * ----------------------------------------------------
     */
    SIDocument& push(Frame&& data);
    /**
     * ----------------------------------------------------
     * Check Container
     * ----------------------------------------------------
     */
    inline bool full() {
        return (__init > 3) && (size() >= __capacity);
    }
protected:
    /**
     * ----------------------------------------------------
     * Variables
     * ----------------------------------------------------
     * capacity
     */
    framecount_t __capacity;
} IDocument;
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 **/
#endif /* SDOCUMENT_H */

