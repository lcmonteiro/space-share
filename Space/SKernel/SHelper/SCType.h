/**
 * ------------------------------------------------------------------------------------------------
 * File:   SCType.h
 * Author: Luis Monteiro
 *
 * Created on November 2, 2018, 10:34 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SCTYPE_H
#define SCTYPE_H
/**
 * std
 */
#include <vector>
#include <locale>
/**
 * ------------------------------------------------------------------------------------------------
 * CType
 * ------------------------------------------------------------------------------------------------
 */
class SCType : public std::ctype<char> {
    static mask* make_table(std::vector<char> spaces) {
        static std::vector<mask> table(
            std::ctype<char>::classic_table(),
            std::ctype<char>::classic_table() + std::ctype<char>::table_size
        );
        for(auto s :spaces) {
            table[s] ^= space;
        }
        return table.data();
    }
public:
    SCType(std::vector<char> s ) : std::ctype<char>(make_table(s)) {
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SCTYPE_H */
