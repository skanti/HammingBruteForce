#include "HamingBruteForce.h"
template<typename T>
HamingBruteForce<T>::HamingBruteForce(int n_size_reserve_, int n_dim_, int threshold_)
        : n_size_reserve(n_size_reserve_), n_dim(n_dim_), threshold(threshold_), index_ab(n_size_reserve, -1),
          distance_ab(n_size_reserve, threshold) {
    assert(n_dim % SIZE_BITS_HAMING == 0);

}