/* 
 * File:   NetMachine.h
 * Author: Luis Monteiro
 *
 * Created on July 4, 2017, 10:58 PM
 */
#ifndef NETMACHINE_H
#define NETMACHINE_H
/**
 */
#include "Sinterface/SMachine.h"
#include "Skernel/STools.h"
#include "Skernel/SHash.h"
/**
 */
#include "NetServers.h"
/**
 */
class NetMachine: public SMachine {
public:
	/**
	 * definitions 
	 */
	static const int SERV_REFERENCE = 20;
	static const int STEP_REFERENCE = 100;
	/**
	 * constructor 
	 */
	NetMachine(const string& location, const string& pass, int instance, int reference) 
	: SMachine(
		Expand(Select(SERVERS, location, SERV_REFERENCE), Init(pass, instance, reference))
	){}
	/**
	 * destructor 
	 */
	virtual ~NetMachine() = default;
protected:
	/**
	 * Machine Initialization 
	 */
	Config Init(string pass, int instance, int reference){
		_instance = instance;
		_reference = reference;
		/**
		 * template
		 */
		return {
			/**
			 * Y function
			 */
			{Setting{
				{  {"type","Y"},   {"name", "11"},   /*{ "----","-----" }//{ "-----","-----" }*/{"verbose","2"}},
				{  {"type","tcp"}, {"uri", Local(0)},/*{ "----","-----" }*/{"lives", "0"},      {"verbose","2"}},
				{{ {"type","tcp"}, {"uri", Local(2)},/*{ "----","-----" }//{ "-----","-----" }*/{"verbose","2"}}},
				{{ {"type","tcp"}, {"uri", Local(1)},/*{ "----","-----" }//{ "-----","-----" }*/{"verbose","2"}}}
			}},
			/**
			 * Encode
			 */
			{Setting{
				{  {"type","E"},   {"name", "21"},     /*{ "----","-----" }//{ "-----","------" }*/{"verbose","2"}},
				{/*{ "---","--" }*/{"redundancy","4"},   {"pass",pass},      {"lives", "0"},       {"verbose","2"}},
				{{ {"type","tcp"}, {"uri", Local(1)},    {"pack-size","20"}, {"frame-size","100"}, {"verbose","2"}}},
				{{ {"type","tcp"}, {"uri", Local(0,1)},/*{ "----","-----" }//{ "-----","------" }*/{"verbose","2"}}}
			}},
			/**
			 * Decode
			 */
			{Setting{
				{  {"type","B"},   {"name", "31"},     /*{ "----","-----" }//{ "-----","-----" }*/{"verbose","2"}},
				{/*{ "---","--" }//{ "-----","-----" } */{"pass",pass},      {"lives", "0"},      {"verbose","2"}},
				{{ {"type","tcp"}, {"uri", Local(0,2)},/*{ "----","-----" }//{ "-----","-----" }*/{"verbose","2"}}},
				{{ {"type","tcp"}, {"uri", Local(2)},  /*{ "----","-----" }//{ "-----","-----" }*/{"verbose","2"}}}
			}},
			/**
			 * T function
			 */
			{Setting{
				{ {"type","T"},   {"name", "41"},     /*{ "----","-----" }//{ "-----","-----" }*/{"verbose","2"}},
				{ {"type","irc"}, {"uri", ""},        /*{ "-----","----" }*/{"lives", "0"},	 {"verbose","2"}},
				{{{"type","tcp"}, {"uri", Local(0,1)},/*{ "----","-----" }//{ "-----","-----" }*/{"verbose","2"}}},
				{{{"type","tcp"}, {"uri", Local(0,2)},/*{ "----","-----" }//{ "-----","-----" }*/{"verbose","2"}}}
			}}	
		};
	}
	/**
	 * expand template given servers list
	 */
	Config Expand(vector<string> servers, Config&& conf){
		/**
		 * first
		 */
		get<1>(conf.back())["uri"] = servers.front();
		/**
		 * next
		 */
		for (unsigned int i = 1; i < servers.size(); ++i) {
			auto& encode = get<3>(conf[1]);
			auto& decode = get<2>(conf[2]);
			/**
			 * encode
			 */
			auto front_e = encode.front();
			front_e["uri"] = Local(i,1);
			encode.push_back(move(front_e));
			/**
			 * decode 
			 */
			auto front_d = encode.front();
			front_d["uri"] = Local(i,2);
			decode.push_back(move(front_d));
			/**
			 * T function 
			 */
			auto back = conf.back();
			get<0>(back)["name"] = to_string(41 + i);
			get<1>(back)["uri"] = servers[i];
			get<2>(back).back()["uri"] = Local(i,1);
			get<3>(back).back()["uri"] = Local(i,2);
			conf.push_back(move(back));
		}
		return conf;
	}
	/**
	 * select servers
	 */
	vector<string> Select(const vector<vector<string>>& servers, string location, size_t n){
		mt19937_64 gen(SHash::Digest(location)); 
		/**
		 * filter
		 */
		vector<string> out;
		for(auto& p : Positions(gen, n, servers.size())){
			auto& server_type = servers[p];
			auto  server_pos  = Position(gen, server_type.size());
			auto  server_name = STools::RamdomName(gen, 8);
			out.push_back(Remote(server_type[server_pos], server_name));
		}
		return out;
	}
protected:
	/**
	 *  properties
	 */
	int _instance;
	int _reference;
private:
	/**
	 * get local address
	 */
	string Local(int i, int d=0){
		return string("localhost:") + to_string(
			_reference + (STEP_REFERENCE * _instance) + (SERV_REFERENCE * d) + i
		);
	}
	/**
	 * get local address
	 */
	string Remote(string address, string name){
		return string("@") + address + string(":6667/") + name;
	}
	/**
	 * get random numbers
	 */
	list<size_t> Positions(mt19937_64& gen, size_t n, size_t total) {
		/**
		 * generate references
		 */
		vector<size_t> ref;
		for (auto i = total, e = total - n; i > e; --i) {
			ref.emplace_back(gen() % i);
		}
		/**
		 * shift holes 
		 */
		list<size_t> out;
		for(auto& r : ref){
			for(auto& o :out) if(o <= r) ++r;
			out.emplace_back(r);
			out.sort();
		}
		return out;
	}
	/**
	 * TESTE???
	 */
	vector<size_t> Positions2(mt19937_64& gen, size_t n, size_t total) {
		/**
		 * generate positions
		 */
		vector<size_t> out;
		out.reserve(n);
		for (auto i = total, e = total - n; i > e; --i) {
			/**
			 * generate reference
			 */
			auto r = gen() % i;
			/**
			 * shift holes 
			 */
			for(auto& o :out) if(o <= r) ++r; else break;
			/**
			 * save position
			 */
			out.emplace_back(r);
		}
		return out;
	}
	/**
	 * get random number
	 */
	size_t Position(mt19937_64& gen, size_t total){
		return gen() % total;
	}
};

#endif /* NETMACHINE_H */

