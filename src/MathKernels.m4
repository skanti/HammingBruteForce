include(`./src/Unroll.m4')
#include "Types.h"
#include "HamingBruteForce.h"

define(intx_t,`ifelse(SIZE_BITS_HAMING,32, int32_t, int64_t)')
define(intx_suffix,`ifelse(SIZE_BITS_HAMING,32,,L)')
define(popcount_x,`ifelse(SIZE_BITS_HAMING,32,_popcnt32,_popcnt64)')


template<typename T>
void HamingBruteForce<T>::match_all(const T *a, int n_size_a, const T *b, int n_size_b) {
    int ld = n_dim / SIZE_BITS_HAMING;
    for (int i = 0; i < n_size_a; i++) {
        for (int j = 0; j < n_size_b; j++) {
            forloop(k, 0, eval(256/SIZE_BITS_HAMING),
                int `m4_var(d_ab,k)' = popcount_x (a[i * ld + `k'] ^ b[j * ld + `k']);
            )
            int d_ab = d_ab_0 + forloop(k, 0, eval(256/SIZE_BITS_HAMING), + `m4_var(d_ab,k)' );
            int is_closer = d_ab < distance_ab[i];
            index_ab[i] = is_closer ? j : index_ab[i];
            distance_ab[i] = is_closer ? d_ab : distance_ab[i];
        }
    }
}


template<typename T>
void create_syntethic_data(Matrix<T> &a, int n_size_a, Matrix<T> &b, int n_size_b, int n_dim) {

    std::mt19937 mt(999);
    std::bernoulli_distribution dist_binary(0.5);
    std::vector<T> tmp(n_dim);
    for (int j = 0; j < n_size_a; j++) {
        for (int i = 0; i < n_dim; i++) {
            tmp[i] = dist_binary(mt);
        }
        for (int i = 0; i < n_dim/`SIZE_BITS_HAMING'; i++)
            ints2bits(a(i,j), &tmp[i*`SIZE_BITS_HAMING']);
    }
    for (int j = 0; j < n_size_b; j++) {
        for (int i = 0; i < n_dim; i++) {
            tmp[i] = dist_binary(mt);
        }
        for (int i = 0; i < n_dim/`SIZE_BITS_HAMING'; i++)
            ints2bits(b(i,j), &tmp[i*`SIZE_BITS_HAMING']);
    }


    // -> make 'b' column 30 similiar as 'a' column 4
    //std::copy(a.memptr(4), a.memptr(4) + n_dim/SIZE_BITS_HAMING, b.memptr(30));
    memcpy(b.memptr(30), a.memptr(4), n_dim/8);
    b(0, 30) ^= a(0, 4);
}

static void ints2bits(intx_t &bits, intx_t *ints) {
    bits = ints[0]
    forloop(i, 1, eval(SIZE_BITS_HAMING-1),
         + (ints[i] << i)
    );
}


static void bits2ints(intx_t &bits, intx_t *ints) {
    forloop(i, 0, eval(SIZE_BITS_HAMING-1),
        ints[i] = (bits & (1intx_suffix <<i)) >> i;
    )
}


//template void (*create_syntethic_data)(Matrix<int> &, int , Matrix<int> &, int, int);
