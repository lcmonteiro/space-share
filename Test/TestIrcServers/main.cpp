/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on June 14, 2017, 6:02 PM
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <set>
#include <thread>
#include <mutex>
#include <future>
#include <regex>
/**
 */
#include "Sstream/Slinux/SLinuxIRC.h"
#include "Skernel/STools.h"
/**
 */
using namespace std;
/**
 * 
 */
auto FILE_NAME = "/home/monteiro/workspace/M2Bee/C++/ShareSpace2.0/Tests/TestIrcServers/servers";
/**/
auto CHANNEL_NAME = "EutueU";
/**
 * tools
 */
string Invert(const string& path) {
	static const std::regex re{"[.]"};
	vector<string> container{
		sregex_token_iterator(path.begin(), path.end(), re, -1),
		sregex_token_iterator()
	};
	/**/
	auto it = container.rbegin(), end = container.rend();
	if (it != end) {
		auto s = *it;
		for (++it; it != end; ++it) { 
			s += ("." + *it); 
		}
		return s;
	}
	return {};
}
list<string> Sort(list<string> list) {
	for (auto&s : list) s = Invert(s);
	list.sort();
	for (auto&s : list) s = Invert(s);
	return list;
}
/**
 * load
 */
list<string> Load(const string& file) {
	list<string> out;
	/**
	 * read file
	 */
	ifstream is(file);
	for (string line; getline(is, line);) {
		out.push_back(move(line));
	}
	return out;
}
list<string> Load(const map<string, list<string>>& tree) {
	list<string> out;
	/**
	 * read tree
	 */
	for (auto& e: tree) {
		out.push_back(e.first);
	}
	return Sort(out);
}
/**
 *  
 */
list<list<string>> Split(list<string> in, size_t n) {
	list<list<string >> out;
	/**
	 */
	for (list<string> tmp; in.size() > n; out.emplace_back(move(tmp))) {
		tmp.splice(tmp.begin(), in, in.begin(), next(in.begin(), n));
	}
	out.emplace_back(move(in));
	/**
	 */
	return out;
}
/**
 *  
 */
bool Test(SLinuxIRC& s, SLinuxIRC& r) {
	Frame test(STools::Ramdom(100));
	s.Send(test).Flush();
	cout << "sent(" << test << ")" << endl;
	Frame aux;
	r.Receive(aux, chrono::seconds(5));
	cout << "received(" << aux << ")" << endl;
	/**
	 * verify
	 */
	return (test == aux); 
}

SLinuxIRC Build(const string& address) {
	SLinuxIRC s;
	s.Connect(address, 6667);
	cout << "connected(" << address << ")" << endl;
	s.Join("", CHANNEL_NAME);
	cout << "joined(" << address << ")" << endl;
	return s;
}
/**
 * 
 */
map<string, list<string>> Filter(list<string>&& servers, size_t n = 0) {
	map<string, list<string>> out;
	/** 
	 * Test
	 */
	for (auto it = servers.begin(); it != servers.end(); it = servers.erase(it)) {
		try {
			cout << "s::start(" << *it << ")" << endl;
			/**
			 * Build
			 */
			auto s = Build(*it);
			/**
			 */
			list<string> group; 
			for (auto it_aux = next(it); it_aux != servers.end(); ) {
				try {
					cout << "r::start(" << *it_aux << ")" << endl;
					/** 
					 * Build
					 */
					auto r = Build(*it_aux);
					/**
					 * Test
					 */
					if (Test(s, r) == true) {
						cout << "r::linked(" << *it_aux << ", " << *it << ")" << endl;
						/**
						 */
						group.push_back(move(*it_aux));
						/** 
						 */
						it_aux = servers.erase(it_aux);
						continue;
					}
					cout << "r::failed(" << *it_aux << ", " << *it << ")" << endl;
				} catch (...) {
					cerr << "r::exception(" << *it_aux << ")" << endl;
					if (group.size() >= n) {
						break;
					}
				}
				++it_aux;
			}
			out[*it] = move(group);
		} catch (...) {
			cerr << "s::exception(" << *it << ")" << endl;
		}
	}
	return out;
}
/**
 * 
 */
map<string, list<string>> Merge(list<map<string, list<string>>>&& data, map<string, list<string>>&& out={}) {
	for (auto& d : data) {
		for(auto v : d) {
			auto search = out.find(v.first);
			if (search != out.end()) {
				set<string> tmp(search->second.begin(), search->second.end());
				tmp.insert(v.second.begin(), v.second.end());
				search->second = list<string>(tmp.begin(), tmp.end());
			} else {
				out[v.first] = move(v.second);
			}
		}
	}
	return out;
}
map<string,list<string>> Merge(map<string,list<string>>&& data,map<string, list<string>>&& out={}) {
	for(auto v : data) {
		auto search = out.find(v.first);
		if (search != out.end()) {
			set<string> tmp(search->second.begin(), search->second.end());
			tmp.insert(v.second.begin(), v.second.end());
			search->second = list<string>(tmp.begin(), tmp.end());
		} else {
			out[v.first] = move(v.second);
		}
	}
	return out;
}
/**
 *  Display
 */
map<string, list<string>> Display(map<string, list<string>>&& var) {p
	cout << "{" << endl;
	for (auto& a : var) {
		cout << "\t'" << a.first << "' : [" << endl;
		for (auto& b : a.second) {
			cout << "\t\t'" << b << "'," << endl;
		}
		cout << "\t]," << endl;
	}
	cout << "}" << endl;
	return var;
}
list<string> Display(list<string>&& var) {
	cout << "[" << endl;
	for (auto& a : var) {
		cout << "\t'" << a << "'," << endl;
	}
	cout << "]" << endl;
	return var;
}
/**
 * 
 */
int main(int argc, char** argv) {
	const char* fname = argc > 1 ? argv[1] : FILE_NAME;
	/**
	 * 
	 */
	map<string, list < string>> data; 
	auto n = 0;
	for (auto end = Load(fname), begin = Load(data); begin.size() != end.size(); end = Load(data)) {
		/**
		 * start
		 */
		begin = move(end);
		/**
		 * filter
		 */
		list<future < map<string, list < string>>>> tasks;
		for (auto& s : Split(begin, int(begin.size()/10))) {
			tasks.push_back(async(std::launch::async, Filter, move(s), int(n++>>1)));
		}
		/**
		 * wait
		 */
		list<map<string, list < string>>> tmp;
		for (auto&t : tasks) {
			tmp.push_back(move(t.get()));
		}
		/**
		 * merge
		 */
		data = Display(Merge(move(tmp)));
	}
	auto s = Load(data);
	cout << endl << "-------------------------- " << n << " ----------------------------------" << endl;
	Display(Merge(move(data), Filter(move(s), n)));
	cout << "----------------------------------------------------------------" << endl;
	return 0;
}


