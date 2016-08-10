include(`./src/Unroll.m4')
#include "Types.h"
#include "HamingBruteForce.h"

define(intx_t,`ifelse(SIZE_BITS_HAMING,32, int32_t, int64_t)')
define(intx_suffix,`ifelse(SIZE_BITS_HAMING,32,,L)')
define(popcount_x,`ifelse(SIZE_BITS_HAMING,32,_popcnt32,_popcnt64)')

template<typename T>
HamingBruteForce<T>::HamingBruteForce(int n_size_reserve_, int n_dim_, int threshold_)
    : n_size_reserve(n_size_reserve_), n_dim(n_dim_), threshold(threshold_),
    index_ab(n_size_reserve), distance_ab(n_size_reserve)  { }

template<typename T>
void HamingBruteForce<T>::match_all(const T *a, int n_size_a, const  T *b, int n_size_b) {
    int ld = n_dim / SIZE_BITS_HAMING;
    for (int i = 0; i < n_size_a; i++) {
        for (int j = 0; j < n_size_b; j++) {
            forloop(k, 0, eval(256/SIZE_BITS_HAMING - 1 ),
                int `m4_var(d_ab,k)' = popcount_x (a[i * ld + `k'] ^ b[j * ld + `k']);
            )
            int d_ab = d_ab_0 forloop(k, 0, eval(256/SIZE_BITS_HAMING - 1), + `m4_var(d_ab,k)' );
            int is_closer = d_ab < distance_ab[i];
            index_ab[i] = is_closer ? j : index_ab[i];
            distance_ab[i] = is_closer ? d_ab : distance_ab[i];
        }
    }
}
