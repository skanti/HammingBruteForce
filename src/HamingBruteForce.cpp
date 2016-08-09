#include "HamingBruteForce.h"

template<typename T>
HamingBruteForce<T>::HamingBruteForce(int n_size_reserve_, int n_dim_, int threshold_)
        : n_size_reserve(n_size_reserve_), n_dim(n_dim_), threshold(threshold_), index_ab(n_size_reserve, -1),
          distance_ab(n_size_reserve, threshold) {
    assert(n_dim % SIZE_BITS_HAMING == 0);

}


template<typename T>
void HamingBruteForce<T>::match_all(const T *a, int n_size_a, const T *b, int n_size_b) {
    int ld = n_dim / SIZE_BITS_HAMING;
    for (int i = 0; i < n_size_a; i++) {
        for (int j = 0; j < n_size_b; j++) {
            int d_ab = 0;
            for (int k = 0; k < ld; k++)
                d_ab += __builtin_popcount(a[i * ld + k] ^ b[j * ld + k]);
            int is_closer = d_ab < distance_ab[i];
            index_ab[i] = is_closer ? j : index_ab[i];
            distance_ab[i] = is_closer ? d_ab : distance_ab[i];
        }
    }
}
