/* 
 * File:   SCodecStamp.h
 * Author: Luis Monteiro
 *
 * Created on September 29, 2015, 5:48 PM
 */
#ifndef SCODECSTAMP_H
#define SCODECSTAMP_H
/**
 */
#include <cstdint>
/**
 */
#include <vector>
#include <map>
/**
 */
namespace v1 {
	/**
	 */
	using namespace std;
	/**
	 * 1º field size
	 * 2º sparsity
	 */
	typedef pair <uint8_t, uint8_t> Density;
	/**/
	typedef vector<Density> Stamp;
	/**
	 */
	class SCodecStamp {
	public:
		/**
		 * types
		 */
		typedef enum {
			NONE, SPARSE, STREAM, MESSAGE, FULL
		} Type;
		/** 
		 * get stamp by type
		 */
		static const Stamp& Get(const Type t) {
		      return __definitions.at(t);  
		} 
		/** 
		 * Generate stamp
		 */
		static Stamp Generate(Type t, const uint64_t seed = 0){
			return Generate(seed, __templates.at(t).first, __templates.at(t).second);
		}
		static Stamp Generate(
			const uint64_t seed = 0, const Density& min = {1, 1}, const Density& max = {255, 255}
		);  
	private:
		/**
		 * stamp definitions
		 */
		static const map<const int, const Stamp> __definitions;
		/** 
		 * stamp templates
		 */
		static const map<const int, pair<const Density, const Density>> __templates;
		
	};
};
#endif /* SCODECSTAMP_H */
