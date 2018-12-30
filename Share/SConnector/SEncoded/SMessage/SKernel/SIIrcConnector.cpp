/*
 * Container:   SIIrcConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
#include "SIIrcConnector.h"
/**
 * Begin namespace Encoded
 */
namespace Encoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 */
SIIrcConnector::SIIrcConnector(const string address)
: SInputConnector(address){
}
/** 
 */
list<Document> SIIrcConnector::_Drain() {
	/**------------------------------------------------------------------------------------------------------------*
	 * log
	 *-------------------------------------------------------------------------------------------------------------*/
	INFO("CODE(drain)::IN::n=0");
	/*-------------------------------------------------------------------------------------------------------------*
	 * drain container
	 *-------------------------------------------------------------------------------------------------------------*/
	return {};
}
/**
 */
Document SIIrcConnector::_Read() {
	/**------------------------------------------------------------------------------------------------------------*
	 * receive
	 *-------------------------------------------------------------------------------------------------------------*/
	OFrame out(__res.Read());
	/**/
	auto position = out.Read(sizeof (reference_t)).Number<reference_t>();
	auto nframest = out.Read(sizeof (numframes_t)).Number<numframes_t>();
	auto framelen = out.Read(sizeof (framesize_t)).Number<framesize_t>();
	/**------------------------------------------------------------------------------------------------------------*
	 * log
	 *-------------------------------------------------------------------------------------------------------------*/
	INFO("CODE::IN::" 
		<< "pos=" << position << " " << "n=" << nframest << " " << "len=" << framelen
	);
	/**------------------------------------------------------------------------------------------------------------*
	 * read nframes
	 *-------------------------------------------------------------------------------------------------------------*/
	Document container(Context(position, nframest, framelen));
	container.reserve(1);
	container.push_back(out.Read(framelen));
	/** 
	 */
	return container;
}
/**
 */
void SIIrcConnector::_Open() {
       mt19937_64 eng{random_device{}()};
       /**
        */
       uniform_int_distribution<> dist{5000, 20000};
       /**
        */
       int i = 0;
       do {
               try {
                       SIRCResource res;
                       /**--------------------------------------------------------------------------------------------*
                        * connect to server
                        *---------------------------------------------------------------------------------------------*/
                       res.Connect(__uri.Host(), __uri.Port());
                       INFO("CONNECT");
                       STask::Sleep(chrono::seconds{1});
                       /**--------------------------------------------------------------------------------------------*
                        * join to channel
                        *---------------------------------------------------------------------------------------------*/
                       res.Join(__uri.User(), __uri.Channel());
                       INFO("JOIN");
                       STask::Sleep(chrono::seconds{1});
                       /*---------------------------------------------------------------------------------------------*
                        * active 
                        *---------------------------------------------------------------------------------------------*/
                       swap(__res, res);
                       /**
                        */
                       break;
               } catch (IRCExceptionBANNED& ex) {
                       ERROR(ex.what());
                       /*---------------------------------------------------------------------------------------------*
                        * reset connection
                        *---------------------------------------------------------------------------------------------*/
                       __res = SIRCResource();
                       break;
               } catch (ResourceExceptionTIMEOUT& ex) {
                       WARNING(ex.what());
               } catch (ResourceExceptionABORT& ex) {
                       WARNING(ex.what());
               } catch (std::system_error& ex) {
                       WARNING(ex.what());
               }
               /**
                * sleep
                */
       } while (STask::Sleep(chrono::milliseconds{dist(eng) + (1000 * i++)}));
}
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
