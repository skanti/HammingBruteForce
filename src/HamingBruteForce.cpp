

#include "Types.h"
#include "HamingBruteForce.h"





template<typename T>
HamingBruteForce<T>::HamingBruteForce(int n_size_reserve_, int n_dim_, int threshold_)
    : n_size_reserve(n_size_reserve_), n_dim(n_dim_), threshold(threshold_),
    index_ab(n_size_reserve), distance_ab(n_size_reserve)  { }

template<typename T>
void HamingBruteForce<T>::match_all(const T *a, int n_size_a, const  T *b, int n_size_b) {
    int ld = n_dim / 64;
    for (int i = 0; i < n_size_a; i++) {
        for (int j = 0; j < n_size_b; j++) {
            int d_ab_0 = _popcnt64 (a[i * ld + 0] ^ b[j * ld + 0]);
            int d_ab_1 = _popcnt64 (a[i * ld + 1] ^ b[j * ld + 1]);
            int d_ab_2 = _popcnt64 (a[i * ld + 2] ^ b[j * ld + 2]);
            int d_ab_3 = _popcnt64 (a[i * ld + 3] ^ b[j * ld + 3]);
            
            int d_ab = d_ab_0 + d_ab_0 + d_ab_1 + d_ab_2 + d_ab_3 ;
            int is_closer = d_ab < distance_ab[i];
            index_ab[i] = is_closer ? j : index_ab[i];
            distance_ab[i] = is_closer ? d_ab : distance_ab[i];
        }
    }
}
