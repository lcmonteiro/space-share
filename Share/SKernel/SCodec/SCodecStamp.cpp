/**
 * ------------------------------------------------------------------------------------------------
 * File:   SCodecStamp.cpp
 * Author: Luis Monteiro
 *
 * Created on November 30, 2015, 5:48 PM
 * ------------------------------------------------------------------------------------------------
 ** 
 * std
 */
#include <random>
/**
 * local
 */
#include "SCodecStamp.h"
/**
 */
namespace v1 {
	using namespace std;
	/**
	 * ------------------------------------------------------------------------
	 * definitions
	 * ------------------------------------------------------------------------
	 */	
	const map<const int, const SharedStamp> SCodecStamp::__definitions {
		{SCodecStamp::NONE, make_shared<const Stamp>(256, Density{  0,   0})},
		{SCodecStamp::FULL, make_shared<const Stamp>(256, Density{255, 255})}
	};
	/**
	 * ------------------------------------------------------------------------
	 * templates
	 * ------------------------------------------------------------------------
	 */
	const map<const int, pair<const Density, const Density>> SCodecStamp::__templates {
		{SCodecStamp::NONE, {
			{0, 0}, {0, 0}
		}}, {SCodecStamp::SPARSE, {
			{1, 4}, {255, 255}
		}}, {SCodecStamp::STREAM, {
			{1, 8}, {3, 127}
		}}, {SCodecStamp::MESSAGE, {
			{7, 16}, {255, 255}
		}}, {SCodecStamp::FULL, {
			{255, 255}, {255, 255}
		}}
	};
	/**
	 * ------------------------------------------------------------------------
	 * Generate
	 * ------------------------------------------------------------------------
	 */
	SharedStamp SCodecStamp::Generate(const uint64_t seed, const Density& min, const Density& max) {
		//  generator -------------------------------------
		mt19937_64 c(seed);
		
		// init stamp -------------------------------------
		Stamp out(256);
		
		// build stamp ------------------------------------
		for (auto& v : out) {
			v.first = uint8_t(c());
			v.first |= min.first;
			v.first &= max.first;
			v.second = uint8_t(c());
			v.second |= min.second;
			v.second &= max.second;
		}
		// return shared stamp ----------------------------
		return make_shared<const Stamp>(move(out));
	}
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */