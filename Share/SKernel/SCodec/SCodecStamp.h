/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SCodecStamp.h
 * Author: Luis Monteiro
 *
 * Created on September 29, 2015, 5:48 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SCODECSTAMP_H
#define SCODECSTAMP_H
/**
 * std
 */
#include <cstdint>
#include <vector>
#include <map>
/**
 */
namespace v1 {
	/**
	 * 1º field size
	 * 2º sparsity
	 */
	typedef std::pair <uint8_t, uint8_t> Density;
	/**/
	typedef std::vector<Density> Stamp;
	/**
	 * --------------------------------------------------------------------------------------------
	 * Codec Stamp
	 * --------------------------------------------------------------------------------------------
	 */
	class SCodecStamp {
	public:
		/**
		 * --------------------------------------------------------------------
		 * types
		 * --------------------------------------------------------------------
		 */
		typedef enum {
			NONE, SPARSE, STREAM, MESSAGE, FULL
		} Type;
		/** 
		 * --------------------------------------------------------------------
		 * get stamp by type
		 * --------------------------------------------------------------------
		 */
		static const Stamp& Get(const Type t) {
		      return __definitions.at(t);  
		} 
		/** 
		 * --------------------------------------------------------------------
		 * Generate stamp
		 * --------------------------------------------------------------------
		 */
		static Stamp Generate(Type t, const uint64_t seed = 0){
			return Generate(seed, __templates.at(t).first, __templates.at(t).second);
		}
		static Stamp Generate(
			const uint64_t seed = 0, const Density& min = {1, 1}, const Density& max = {255, 255}
		);  
	private:
		/**
		 * --------------------------------------------------------------------
		 * variables
		 * --------------------------------------------------------------------
		 **
		 * stamp definitions
		 */
		static const std::map<
			const int, const Stamp
		> __definitions;
		/** 
		 * stamp templates
		 */
		static const std::map<
			const int, std::pair<
				const Density, const Density
			>
		> __templates;
		
	};
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */ 
#endif /* SCODECSTAMP_H */
