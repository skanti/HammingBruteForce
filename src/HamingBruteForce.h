#ifndef HAMINGBRUTEFORCE_H
#define HAMINGBRUTEFORCE_H

#include <vector>
#include "AlignedAllocator.h"
#include <cassert>
#include <cmath>

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

#define PI 3.14159265359

class HamingBruteForce {
public:
    typedef std::vector<int, AlignedAllocator<int, 32>> ivec;

    HamingBruteForce(int n_size_reserve_, int threshold_);

    void match_all(const int64_t *a, int n_size_a, const int64_t *b, int n_size_b);

    template<class T>
    void refine_distance(T *AoS_a, T *AoS_b, int n_size_a,
                         float threshold_distance, float threshold_angle) {
        for (int i = 0; i < n_size_a; i++) {
            int j = index_ab[i];
            int dab_x = AoS_a[i].x - AoS_b[j].x;
            int dab_y = AoS_a[i].y - AoS_b[j].y;
            float dab = std::sqrt(dab_x * dab_x + dab_y * dab_y);
            float d_angle = std::abs(AoS_a[i].angle - AoS_b[j].angle);
            d_angle = d_angle >= PI / 2.0f ? d_angle - PI / 2.0f : d_angle;
            index_ab[i] = dab > threshold_distance ? -1 : index_ab[i];
            index_ab[i] = d_angle > threshold_angle ? -1 : index_ab[i];
            //distance_ab[i] = dab > threshold_distance ? distance_ab[i] + 32 : distance_ab[i];
            //distance_ab[i] = d_angle > threshold_angle ? distance_ab[i] + 32 : distance_ab[i];
        }
    }

    const int n_dim_vec = N_DIM_BINARYDESCRIPTOR / SIZE_BITS_HAMING; // <-- N_DIM_BINARYDESCRIPTOR/SIZE_BITS_HAMING = 4
    int n_size_reserve;
    int threshold;
    ivec index_ab;
    ivec distance_ab;
};

#endif
