/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SFileConnector.h
 * Author: root
 *
 * Created on December 2, 2016, 2:13 PM
 */

#ifndef SFILESTREAMDATA_H
#define SFILESTREAMDATA_H
/**
 * Space Kernel
 */
#include "SContainer.h"
/**
 * Share Kernel
 */
#include "SConnector.h"
/**
 * Stream Kernel
 */
#include "Sbase/SIFileConnector.h"
#include "Sbase/SOFileConnector.h"
/**
 * Begin namespace Data
 */
namespace Stream {
/**
 * Input File Connector template
 */
template<class T>
class SIFileConnectorT : public T {
public:
    /**
     * make
     */
    template<typename...Args>
    static IConnector Make(Args &&...args) {
        return make_shared<SIFileConnectorT>(forward<Args>(args)...);
    }
    /**
     * constructor
     */
    SIFileConnectorT(
        const string address,
        const size_t nframes,
        const size_t sframes
    ) : T(address, nframes, sframes) {
    }
};
/**
 * Output File Connector template
 */
template<class T>
class SOFileConnectorT : public T {
public:
    /**
     * make
     */
    template<typename...Args>
    static OConnector Make(Args &&...args) {
        return make_shared<SOFileConnectorT>(forward<Args>(args)...);
    }
    /**
     * constructor
     */
    SOFileConnectorT(const string address) : T(address) {
    }
};
/**
 * definitions
 */
typedef SIFileConnectorT<SIFileConnector> IFileConnector;
typedef SOFileConnectorT<SOFileConnector> OFileConnector;
/**
 * End namespace Data
 */
}
/**
 */
#endif /* SFILESTREAMDATA_H */

