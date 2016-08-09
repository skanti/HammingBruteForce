

#include "Types.h"

template<typename T>
void create_syntethic_data(Matrix<T> &a, int n_size_a, Matrix<T> &b, int n_size_b, int n_dim) {

    std::mt19937 mt(999);
    std::bernoulli_distribution dist_binary(0.5);
    std::vector<T> tmp(n_dim);
    for (int j = 0; j < n_size_a; j++) {
        for (int i = 0; i < n_dim; i++) {
            tmp[i] = dist_binary(mt);
        }
        for (int i = 0; i < n_dim/32; i++)
            ints2bits(a(i,j), &tmp[i*32]);
    }
    for (int j = 0; j < n_size_b; j++) {
        for (int i = 0; i < n_dim; i++) {
                tmp[i] = dist_binary(mt);
        }
        for (int i = 0; i < n_dim/32; i++)
            ints2bits(b(i,j), &tmp[i*32]);
    }


    // -> make 'b' column 30 similiar as 'a' column 4
    std::copy(a.memptr(4), a.memptr(4) + n_dim/32, b.memptr(30));
    b(0, 30) = !a(0, 4);
}

static void ints2bits(int &bits, int *ints) {
    bits = ints[0]
    + (ints[1] << 1)
    + (ints[2] << 2)
    + (ints[3] << 3)
    + (ints[4] << 4)
    + (ints[5] << 5)
    + (ints[6] << 6)
    + (ints[7] << 7)
    + (ints[8] << 8)
    + (ints[9] << 9)
    + (ints[10] << 10)
    + (ints[11] << 11)
    + (ints[12] << 12)
    + (ints[13] << 13)
    + (ints[14] << 14)
    + (ints[15] << 15)
    + (ints[16] << 16)
    + (ints[17] << 17)
    + (ints[18] << 18)
    + (ints[19] << 19)
    + (ints[20] << 20)
    + (ints[21] << 21)
    + (ints[22] << 22)
    + (ints[23] << 23)
    + (ints[24] << 24)
    + (ints[25] << 25)
    + (ints[26] << 26)
    + (ints[27] << 27)
    + (ints[28] << 28)
    + (ints[29] << 29)
    + (ints[30] << 30)
    + (ints[31] << 31)
    ;
}


static void bits2ints(int &bits, int *ints) {
    ints[0] = (bits & (1<<0)) >> 0;
    ints[1] = (bits & (1<<1)) >> 1;
    ints[2] = (bits & (1<<2)) >> 2;
    ints[3] = (bits & (1<<3)) >> 3;
    ints[4] = (bits & (1<<4)) >> 4;
    ints[5] = (bits & (1<<5)) >> 5;
    ints[6] = (bits & (1<<6)) >> 6;
    ints[7] = (bits & (1<<7)) >> 7;
    ints[8] = (bits & (1<<8)) >> 8;
    ints[9] = (bits & (1<<9)) >> 9;
    ints[10] = (bits & (1<<10)) >> 10;
    ints[11] = (bits & (1<<11)) >> 11;
    ints[12] = (bits & (1<<12)) >> 12;
    ints[13] = (bits & (1<<13)) >> 13;
    ints[14] = (bits & (1<<14)) >> 14;
    ints[15] = (bits & (1<<15)) >> 15;
    ints[16] = (bits & (1<<16)) >> 16;
    ints[17] = (bits & (1<<17)) >> 17;
    ints[18] = (bits & (1<<18)) >> 18;
    ints[19] = (bits & (1<<19)) >> 19;
    ints[20] = (bits & (1<<20)) >> 20;
    ints[21] = (bits & (1<<21)) >> 21;
    ints[22] = (bits & (1<<22)) >> 22;
    ints[23] = (bits & (1<<23)) >> 23;
    ints[24] = (bits & (1<<24)) >> 24;
    ints[25] = (bits & (1<<25)) >> 25;
    ints[26] = (bits & (1<<26)) >> 26;
    ints[27] = (bits & (1<<27)) >> 27;
    ints[28] = (bits & (1<<28)) >> 28;
    ints[29] = (bits & (1<<29)) >> 29;
    ints[30] = (bits & (1<<30)) >> 30;
    ints[31] = (bits & (1<<31)) >> 31;
    
}


//template void (*create_syntethic_data)(Matrix<int> &, int , Matrix<int> &, int, int);
