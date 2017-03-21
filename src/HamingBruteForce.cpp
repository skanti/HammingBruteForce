#include "Types.h"
#include "HamingBruteForce.h"
#include <nmmintrin.h>


HamingBruteForce::HamingBruteForce(int32_t n_size_reserve_, int32_t threshold_) {
            
            n_size_reserve = n_size_reserve_;
            threshold = threshold_;
            index_ab = nullptr;
            int h1 = posix_memalign((void**)&index_ab, 16, sizeof(int32_t)*n_size_reserve);
            std::fill(index_ab, index_ab + n_size_reserve, -1);

            distance_ab = nullptr;
            int h2 = posix_memalign((void**)&distance_ab, 16, sizeof(int32_t)*n_size_reserve);
            std::fill(distance_ab, distance_ab + n_size_reserve, threshold_);
}


HamingBruteForce::~HamingBruteForce() {
    if (index_ab != nullptr) free(index_ab);
    if (distance_ab != nullptr) free(distance_ab);
}

void HamingBruteForce::match_all(const int64_t *a, int n_size_a, const int64_t *b, int n_size_b) {
    for (int i = 0; i < n_size_a; i++) {
        for (int j = 0; j < n_size_b; j++) {
            int d_ab0 = _mm_popcnt_u64(a[i*4 + 0] ^ b[j*4 + 0]);
            int d_ab1 = _mm_popcnt_u64(a[i*4 + 1] ^ b[j*4 + 1]);
            int d_ab2 = _mm_popcnt_u64(a[i*4 + 2] ^ b[j*4 + 2]);
            int d_ab3 = _mm_popcnt_u64(a[i*4 + 3] ^ b[j*4 + 3]);
            int d_ab = d_ab0 + d_ab1 + d_ab2 + d_ab3;

            int is_closer = d_ab < distance_ab[i];
            index_ab[i] = is_closer ? j : index_ab[i];
            distance_ab[i] = is_closer ? d_ab : distance_ab[i];
        }
    }
}
