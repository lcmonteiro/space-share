/*
 * File:   SCodec.cpp
 * Author: Luis Monteiro
 *
 * Created on November 30, 2015, 5:48 PM
 */
#include <iostream>
#include <set>
/**
 * local
 */
#include "SCodec.h"
/**
 */
namespace v1 {
/**
 * constant
 */
static const int INT_MASK = ~int(sizeof(int)-1);
/**
 */
//    typedef mt19937 Generator;
typedef minstd_rand0 Generator;
/**
 * ------------------------------------------------------------------------------------------------
 *                    utils                                        
 * ------------------------------------------------------------------------------------------------
 **
 *  encode functions
 */
static inline uint32_t Combine(
        const Container& data, uint32_t seed, uint8_t field, uint8_t sparsity, Frame& out
);
/**
 * decode functions
 */
static inline void Organize(
        Frame& field, Container& coef, Container& data
);
static inline uint32_t Solve(
        uint32_t size, Container& coef, Container& data
);
/**
 * ------------------------------------------------------------------------------------------------
 *                    Codec                                        
 * ------------------------------------------------------------------------------------------------
 **
 * encode
 */
uint32_t SCodec::Encode(
    Container&   code, 
    uint32_t     size, 
    Container&   data, 
    Random&      rand, 
    uint32_t     high_density, 
    const Stamp& stamp
) {
    // ------------------------------------------------------------------------
#define ENCODE(MIN, FIELD, SPARSITY, FRAMESIZE) do{             \
    /* seed, field and sparsity */                              \
    uint32_t seed(0);                                           \
    uint8_t  field(0);                                          \
    uint8_t  sparsity(0);                                       \
    /* create combination */                                    \
    Frame comb;                                                 \
    comb.reserve(FRAMESIZE + HeaderSize() + sizeof(int));       \
    comb.assign(FRAMESIZE, 0);                                  \
    do{                                                         \
        seed=rand();                                            \
        field=FIELD;                                            \
        sparsity=SPARSITY;                                      \
    }while(Combine(data, seed, field, sparsity, comb)<MIN);     \
    /* add seed */                                              \
    comb.emplace_back(uint8_t(seed));                           \
    seed >>= 8;                                                 \
    comb.emplace_back(uint8_t(seed));                           \
    seed >>= 8;                                                 \
    comb.emplace_back(uint8_t(seed));                           \
    seed >>= 8;                                                 \
    comb.emplace_back(uint8_t(seed));                           \
    /* save combination */                                      \
    code.push_back(move(comb));                                 \
}while (0)
    // encode container -------------------------------------------------------
    code.reserve(size);
    // check if empty ---------------------------------------------------------
    if (data.empty()) {
        return 0;
    }
    // get frame size ---------------------------------------------------------
    const uint32_t FRAME_SIZE(data.front().size());
    // normal density ---------------------------------------------------------
    for (unsigned int i = high_density; i < size; i++) {
        ENCODE(1, 
            stamp[uint8_t(seed)].first, 
            stamp[uint8_t(seed)].second, 
            FRAME_SIZE
        );
    }
    // high density -----------------------------------------------------------
    for (unsigned int i = 0; i < high_density; i++) {
        ENCODE(1, UINT8_MAX, UINT8_MAX, FRAME_SIZE);
    }
    return size;
}
/**
 * decode
 */
uint32_t SCodec::Decode(
    Container&&  code, 
    uint32_t     capacity, 
    Container&   data, 
    Container&   coefs, 
    Frame&       fields, 
    const Stamp& stamp
) {
    for (auto it = code.begin(); it != code.end(); ++it) {
        // remove seed --------------------------------------------------------
        uint32_t seed = uint32_t(it->back());
        it->pop_back();
        seed <<= 8;
        seed |= uint32_t(it->back());
        it->pop_back();
        seed <<= 8;
        seed |= uint32_t(it->back());
        it->pop_back();
        seed <<= 8;
        seed |= uint32_t(it->back());
        it->pop_back();
        // find field and sparsity --------------------------------------------
        uint8_t field    = stamp[uint8_t(seed)].first;
        uint8_t sparsity = stamp[uint8_t(seed)].second;
        // coefficient generator ----------------------------------------------
        Generator c(seed);
        // --------------------------------------------------------------------
        Frame coef(capacity + sizeof (int), capacity, 0);
        // --------------------------------------------------------------------
        register uint8_t factor = 0;
        // --------------------------------------------------------------------
        for (auto it = coef.begin(), end = coef.end(); it != end; ++it) {
            factor = c();
            if (factor > sparsity) {
                continue;
            }
            *it = (factor & field);
        }
        // update state -------------------------------------------------------
        data.push_back(move(*it));
        // update coefficients ------------------------------------------------
        coefs.push_back(move(coef));
        // update fields ------------------------------------------------------
        fields.push_back(field);
    }
    // nframes organize -------------------------------------------------------
    Organize(fields, coefs, data);
    // try to solve -----------------------------------------------------------
    return Solve(capacity, coefs, data);
}
/**
 * ------------------------------------------------------------------------------------------------
 *                    GF8 operators                                    
 * ------------------------------------------------------------------------------------------------
 **
 * GF sequences
 */
static const int V2P[] = {
    512, 
      0,   1,  25,   2,  50,  26, 198,   3, 223,  51, 238,  27, 104, 199,  75, 
      4, 100, 224,  14,  52, 141, 239, 129,  28, 193, 105, 248, 200,   8,  76,
    113,   5, 138, 101,  47, 225,  36,  15,  33,  53, 147, 142, 218, 240,  18,
    130,  69,  29, 181, 194, 125, 106,  39, 249, 185, 201, 154,   9, 120,  77, 
    228, 114, 166,   6, 191, 139,  98, 102, 221,  48, 253, 226, 152,  37, 179, 
     16, 145,  34, 136,  54, 208, 148, 206, 143, 150, 219, 189, 241, 210,  19, 
     92, 131,  56,  70,  64,  30,  66, 182, 163, 195,  72, 126, 110, 107,  58, 
     40,  84, 250, 133, 186,  61, 202,  94, 155, 159,  10,  21, 121,  43,  78, 
    212, 229, 172, 115, 243, 167,  87,   7, 112, 192, 247, 140, 128,  99,  13, 
    103,  74, 222, 237,  49, 197, 254,  24, 227, 165, 153, 119,  38, 184, 180, 
    124,  17,  68, 146, 217,  35,  32, 137,  46,  55,  63, 209,  91, 149, 188, 
    207, 205, 144, 135, 151, 178, 220, 252, 190,  97, 242,  86, 211, 171,  20, 
     42,  93, 158, 132,  60,  57,  83,  71, 109,  65, 162,  31,  45,  67, 216, 
    183, 123, 164, 118, 196,  23,  73, 236, 127,  12, 111, 246, 108, 161,  59, 
     82,  41, 157,  85, 170, 251,  96, 134, 177, 187, 204,  62,  90, 203,  89, 
     95, 176, 156, 169, 160,  81,  11, 245,  22, 235, 122, 117,  44, 215,  79, 
    174, 213, 233, 230, 231, 173, 232, 116, 214, 244, 234, 168,  80,  88, 175
};
static const int P2V[] = {
      1,   2,  4,    8,  16,  32,  64, 128,  29,  58, 116, 232, 205, 135,  19,
     38,  76, 152,  45,  90, 180, 117, 234, 201, 143,   3,   6,  12,  24,  48,
     96, 192, 157,  39,  78, 156,  37,  74, 148,  53, 106, 212, 181, 119, 238,
    193, 159,  35,  70, 140,   5,  10,  20,  40,  80, 160,  93, 186, 105, 210,
    185, 111, 222, 161,  95, 190,  97, 194, 153, 047,  94, 188, 101, 202, 137, 
     15,  30,  60, 120, 240, 253, 231, 211, 187, 107, 214, 177, 127, 254, 225, 
    223, 163,  91, 182, 113, 226, 217, 175,  67, 134,  17,  34,  68, 136,  13,
     26,  52, 104, 208, 189, 103, 206, 129,  31,  62, 124, 248, 237, 199, 147, 
     59, 118, 236, 197, 151,  51, 102, 204, 133,  23,  46,  92, 184, 109, 218, 
    169,  79, 158,  33,  66, 132,  21,  42,  84, 168,  77, 154,  41,  82, 164, 
     85, 170,  73, 146,  57, 114, 228, 213, 183, 115, 230, 209, 191,  99, 198, 
    145,  63, 126, 252, 229, 215, 179, 123, 246, 241, 255, 227, 219, 171,  75, 
    150,  49,  98, 196, 149,  55, 110, 220, 165,  87, 174,  65, 130,  25,  50, 
    100, 200, 141,   7,  14,  28,  56, 112, 224, 221, 167,  83, 166,  81, 162,
     89, 178, 121, 242, 249, 239, 195, 155,  43,  86, 172,  69, 138,   9,  18, 
     36,  72, 144,  61, 122, 244, 245, 247, 243, 251, 235, 203, 139,  11,  22, 
     44,  88, 176, 125, 250, 233, 207, 131,  27,  54, 108, 216, 173,  71, 142,
    // repeat
     1,   2,  4,    8,  16,  32,  64, 128,  29,  58, 116, 232, 205, 135,  19,
     38,  76, 152,  45,  90, 180, 117, 234, 201, 143,   3,   6,  12,  24,  48,
     96, 192, 157,  39,  78, 156,  37,  74, 148,  53, 106, 212, 181, 119, 238,
    193, 159,  35,  70, 140,   5,  10,  20,  40,  80, 160,  93, 186, 105, 210,
    185, 111, 222, 161,  95, 190,  97, 194, 153, 047,  94, 188, 101, 202, 137, 
     15,  30,  60, 120, 240, 253, 231, 211, 187, 107, 214, 177, 127, 254, 225, 
    223, 163,  91, 182, 113, 226, 217, 175,  67, 134,  17,  34,  68, 136,  13,
     26,  52, 104, 208, 189, 103, 206, 129,  31,  62, 124, 248, 237, 199, 147, 
     59, 118, 236, 197, 151,  51, 102, 204, 133,  23,  46,  92, 184, 109, 218, 
    169,  79, 158,  33,  66, 132,  21,  42,  84, 168,  77, 154,  41,  82, 164, 
     85, 170,  73, 146,  57, 114, 228, 213, 183, 115, 230, 209, 191,  99, 198, 
    145,  63, 126, 252, 229, 215, 179, 123, 246, 241, 255, 227, 219, 171,  75, 
    150,  49,  98, 196, 149,  55, 110, 220, 165,  87, 174,  65, 130,  25,  50, 
    100, 200, 141,   7,  14,  28,  56, 112, 224, 221, 167,  83, 166,  81, 162,
     89, 178, 121, 242, 249, 239, 195, 155,  43,  86, 172,  69, 138,   9,  18, 
     36,  72, 144,  61, 122, 244, 245, 247, 243, 251, 235, 203, 139,  11,  22, 
     44,  88, 176, 125, 250, 233, 207, 131,  27,  54, 108, 216, 173,  71, 142,
    // zeros
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,
    000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000
};

static inline int Div(int a, int b) {
    // 0 / b = 0
    if (a == 0) {
        return 0;
    }
    // divide
    register int x = V2P[a] - V2P[b];
    // normalize
    if (x < 0) {
        x += 255;
    }
    return P2V[x];
}

static inline int Mul(int a, int b) {
    // b * 0 = 0
    if (a == 0 || b == 0) {
        return 0;
    }
    // multiple
    return P2V[V2P[a] + V2P[b]];
}

static inline Frame& Mul(Frame& b, register int m) {
    // [X] * 0 = [0]
    if (m == 0) {
        fill(b.begin(), b.end(), 0);
        return b;
    }
    // [X] * 1 = [X]
    if (m == 1) {
        return b;
    }
    // [X] * m = [X.m]
    register auto M = V2P[m];
    for (register auto p0 = b.data(), pe = p0 + b.size(); p0 < pe; ++p0) {
        *p0 = P2V[V2P[*p0] + M];
    }
    return b;
}

static inline Frame& Mul(Frame& b, register int m, register int i) {
    // [X] * 0 = [0]
    if (m == 0) {
        fill(b.begin() + i, b.end(), 0);
        return b;
    }
    // [X] * 1 = [X]
    if (m == 1) {
        return b;
    }
    // [X] * m = [X.m]
    register auto M = V2P[m];
    for (register auto p0 = b.data() + i, pe = b.data() + b.size(); p0 < pe; ++p0) {
        *p0 = P2V[V2P[*p0] + M];
    }
    return b;
}

static inline Frame& Merge(Frame& a, Frame& b) {
    register int* p0 = (int*) (a.data()), * p1 = (int*) (b.data());
    // merge a with b    
    for (register int*pe = (int*) (a.data() + a.size()); p0 < pe; ++p0, ++p1) {
        *p0 ^= *p1;
    }
    return a;
}

static inline Frame& Merge(Frame& a, Frame& b, register int i) {
    register int* p0 = (int*) (a.data()+(i & INT_MASK)), * p1 = (int*) (b.data()+(i & INT_MASK));
    // merge a with b
    for (register int*pe = (int*) (a.data() + a.size()); p0 < pe; ++p0, ++p1) {
        *p0 ^= *p1;
    }
    return a;
}
/**
 * ------------------------------------------------------------------------------------------------
 *                    combine                                     
 * ------------------------------------------------------------------------------------------------
 **/
static uint32_t Combine(
        const Container& data, uint32_t seed, uint8_t field, uint8_t sparsity, Frame& out
) {
    // coefficient generator ----------
    Generator c(seed);
    // container for process ----------
    Frame aux(out.capacity());
    // --------------------------------
    register uint8_t factor = 0;
    register uint32_t n = 0;
    // --------------------------------
    for (auto it = data.begin(), end = data.end(); it != end; ++it) {
        // Y += Xn*Cn
        factor = c();
        if (factor > sparsity) {
            continue;
        }
        factor &= field;
        if (factor == 0) {
            continue;
        }
        // save a copy
        aux.assign(it->begin(), it->end());
        // process
        Merge(out, Mul(aux, factor));
        // next
        ++n;
    }
    return n;
}
/**
 * ------------------------------------------------------------------------------------------------
 *                   Organize                                      *
 * ------------------------------------------------------------------------------------------------
 **/
static void Organize(Frame& field, Container& coef, Container& data) {
    // check if empty
    if (field.empty()) {
        return;
    }
    // process
    for (register auto i = size_t(0), ii = field.size() - 1; i < ii;) {
        if (field[i] == 1) {
            i++;
            if (field[ii] != 1) {
                ii--;
            }
        } else {
            if (field[ii] == 1) {
                std::swap(field[i], field[ii]);
                std::swap(coef[i], coef[ii]);
                std::swap(data[i], data[ii]);
                i++;
            }
            ii--;
        }
    }
}
/**
 * ------------------------------------------------------------------------------------------------
 *                    Gaussian Elimination                                 *
 * ------------------------------------------------------------------------------------------------
 **/
static inline void Elimination(Container& coef, Container& data, register int index) {
    for (register uint32_t i = index + 1; i < data.size(); ++i) {
        if (coef[i][index] == 0) {
            continue;
        }
        // ----------------------------
        register auto factor = Div(coef[index][index], coef[i][index]);
        // ----------------------------
        if (factor == 1) {
            Merge(coef[i], coef[index], index);
            Merge(data[i], data[index]);
            continue;
        }
        // ----------------------------
        Merge(Mul(coef[i], factor, index), coef[index], index);
        Merge(Mul(data[i], factor), data[index]);
    }
}

static inline bool Prepare(Container& coef, Container& data, register int index) {
    if (coef[index][index]) {
        return true;
    }
    for (register int i = index + 1, ii = int(data.size()); i < ii; ++i) {
        if (coef[i][index]) {
            std::swap(coef[index], coef[i]);
            std::swap(data[index], data[i]);
            return true;
        }
    }
    return false;
}

static inline void ReverseElimination(Container& coef, Container& data, register int index) {
    for (register int i = 0; i < index; ++i) {
        if (coef[i][index] == 0) {
            continue;
        }
        // ----------------------------
        register auto factor = Div(coef[i][index], coef[index][index]);
        // ----------------------------
        if (factor == 1) {
            Merge(coef[i], coef[index], index);
            Merge(data[i], data[index]);
            continue;
        }
        // ----------------------------
        Merge(coef[i], Mul(coef[index], factor, index), index);
        Merge(data[i], Mul(data[index], factor));
    }
}

static inline void Unification(Container& coef, Container& data, register int index) {
    register auto factor = Div(1, coef[index][index]);
    // check --------------------------
    if (factor == 0) {
        return;
    }
    if (factor == 1) {
        return;
    }
    // process ------------------------
    Mul(coef[index], factor, index);
    Mul(data[index], factor);
}

static uint32_t Solve(uint32_t size, Container& coef, Container& data) {
    // gaussian elimination -----------
    register unsigned int n = 0;
    for (; n < size && n < data.size(); ++n) {
        if (!Prepare(coef, data, n)) {
            break;
        }
        Elimination(coef, data, n);
    }
    // solve diagonal -----------------
    for (register unsigned int i = 0; i < n; ++i) {
        ReverseElimination(coef, data, i);
    }
    // diagonal unification -----------
    for (register unsigned int i = 0; i < n; ++i) {
        Unification(coef, data, i);
    }
    return n;
}

};
