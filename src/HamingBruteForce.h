#ifndef HAMINGBRUTEFORCE_H
#define HAMINGBRUTEFORCE_H

#include <vector>
#include "AlignedAllocator.h"
#include <cassert>

#ifndef N_DIM_BINARYDESCRIPTOR
#define N_DIM_BINARYDESCRIPTOR 256
#elif (N_DIM_BINARYDESCRIPTOR != 256)
#error N_DIM_BINARYDESCRIPTOR has unsupported value (256 supported only).
#endif

#ifndef SIZE_BITS_HAMING
#define SIZE_BITS_HAMING 64
#elif (SIZE_BITS_HAMING != 64)
#error SIZE_BITS_HAMING has unsupported value (64 supported only).
#endif

class HamingBruteForce {
public:
    typedef std::vector<int, AlignedAllocator<int, 32>> ivec;

    HamingBruteForce(int n_size_reserve_, int threshold_);

    void match_all(const int64_t *a, int n_size_a, const int64_t *b, int n_size_b);

    const int n_dim_vec = N_DIM_BINARYDESCRIPTOR/SIZE_BITS_HAMING; // <-- N_DIM_BINARYDESCRIPTOR/SIZE_BITS_HAMING = 4
    int n_size_reserve;
    int threshold;
    ivec index_ab;
    ivec distance_ab;
};

#endif
