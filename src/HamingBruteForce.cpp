#include "Types.h"
#include "HamingBruteForce.h"


HamingBruteForce::HamingBruteForce(int n_size_reserve_, int threshold_)
        : n_size_reserve(n_size_reserve_), threshold(threshold_),
          index_ab(n_size_reserve, -1), distance_ab(n_size_reserve, threshold) {}

void HamingBruteForce::match_all(const int64_t *a, int n_size_a, const int64_t *b, int n_size_b) {
    for (int i = 0; i < n_size_a; i++) {
        for (int j = 0; j < n_size_b; j++) {
            int d_ab_0 = _popcnt64(a[i * 4] ^ b[j * 4]);
            int d_ab_1 = _popcnt64(a[i * 4 + 1] ^ b[j * 4 + 1]);
            int d_ab_2 = _popcnt64(a[i * 4 + 2] ^ b[j * 4 + 2]);
            int d_ab_3 = _popcnt64(a[i * 4 + 3] ^ b[j * 4 + 3]);

            int d_ab = d_ab_0 + d_ab_1 + d_ab_2 + d_ab_3;
            int is_closer = d_ab < distance_ab[i];
            index_ab[i] = is_closer ? j : index_ab[i];
            distance_ab[i] = is_closer ? d_ab : distance_ab[i];
        }
    }
}
