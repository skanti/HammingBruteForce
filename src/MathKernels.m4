include(`./src/Unroll.m4')
#include "Types.h"

define(intx_t,`ifelse(SIZE_BITS_HAMING,64, int64_t,)')
define(intx_suffix,`ifelse(SIZE_BITS_HAMING,64,L,)')

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


//template void (*create_synthetic_data)(Matrix<int> &, int , Matrix<int> &, int, int);
