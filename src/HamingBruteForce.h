#ifndef HAMINGBRUTEFORCE_H
#define HAMINGBRUTEFORCE_H

#include <vector>
#include "AlignedAllocator.h"
#include <cassert>

#ifndef SIZE_BITS_HAMING
#error Define SIZE_BITS_HAMING a-priori
#endif


template<typename T>
class HamingBruteForce {
public:
    typedef std::vector<int, AlignedAllocator<int, 32>> ivec;

    HamingBruteForce(int n_size_reserve_, int n_dim_, int threshold_);

    void match_all(const T *a, int n_size_a, const T *b, int n_size_b);


    int n_size_reserve;
    int n_dim;
    int threshold;
    ivec index_ab;
    ivec distance_ab;
};

template
class HamingBruteForce<int32_t>;

template
class HamingBruteForce<int64_t>;

#endif
