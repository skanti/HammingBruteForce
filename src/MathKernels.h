

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
        for (int i = 0; i < n_dim/SIZE_BITS_HAMING; i++)
            ints2bits(a(i,j), &tmp[i*SIZE_BITS_HAMING]);
    }
    for (int j = 0; j < n_size_b; j++) {
        for (int i = 0; i < n_dim; i++) {
            tmp[i] = dist_binary(mt);
        }
        for (int i = 0; i < n_dim/SIZE_BITS_HAMING; i++)
            ints2bits(b(i,j), &tmp[i*SIZE_BITS_HAMING]);
    }


    // -> make 'b' column 30 similiar as 'a' column 4
    //std::copy(a.memptr(4), a.memptr(4) + n_dim/64, b.memptr(30));
    memcpy(b.memptr(30), a.memptr(4), n_dim/8);
    b(0, 30) ^= a(0, 4);
}

static void ints2bits(int64_t &bits, int64_t *ints) {
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
    + (ints[32] << 32)
    + (ints[33] << 33)
    + (ints[34] << 34)
    + (ints[35] << 35)
    + (ints[36] << 36)
    + (ints[37] << 37)
    + (ints[38] << 38)
    + (ints[39] << 39)
    + (ints[40] << 40)
    + (ints[41] << 41)
    + (ints[42] << 42)
    + (ints[43] << 43)
    + (ints[44] << 44)
    + (ints[45] << 45)
    + (ints[46] << 46)
    + (ints[47] << 47)
    + (ints[48] << 48)
    + (ints[49] << 49)
    + (ints[50] << 50)
    + (ints[51] << 51)
    + (ints[52] << 52)
    + (ints[53] << 53)
    + (ints[54] << 54)
    + (ints[55] << 55)
    + (ints[56] << 56)
    + (ints[57] << 57)
    + (ints[58] << 58)
    + (ints[59] << 59)
    + (ints[60] << 60)
    + (ints[61] << 61)
    + (ints[62] << 62)
    + (ints[63] << 63)
    ;
}


static void bits2ints(int64_t &bits, int64_t *ints) {
    ints[0] = (bits & (1L <<0)) >> 0;
    ints[1] = (bits & (1L <<1)) >> 1;
    ints[2] = (bits & (1L <<2)) >> 2;
    ints[3] = (bits & (1L <<3)) >> 3;
    ints[4] = (bits & (1L <<4)) >> 4;
    ints[5] = (bits & (1L <<5)) >> 5;
    ints[6] = (bits & (1L <<6)) >> 6;
    ints[7] = (bits & (1L <<7)) >> 7;
    ints[8] = (bits & (1L <<8)) >> 8;
    ints[9] = (bits & (1L <<9)) >> 9;
    ints[10] = (bits & (1L <<10)) >> 10;
    ints[11] = (bits & (1L <<11)) >> 11;
    ints[12] = (bits & (1L <<12)) >> 12;
    ints[13] = (bits & (1L <<13)) >> 13;
    ints[14] = (bits & (1L <<14)) >> 14;
    ints[15] = (bits & (1L <<15)) >> 15;
    ints[16] = (bits & (1L <<16)) >> 16;
    ints[17] = (bits & (1L <<17)) >> 17;
    ints[18] = (bits & (1L <<18)) >> 18;
    ints[19] = (bits & (1L <<19)) >> 19;
    ints[20] = (bits & (1L <<20)) >> 20;
    ints[21] = (bits & (1L <<21)) >> 21;
    ints[22] = (bits & (1L <<22)) >> 22;
    ints[23] = (bits & (1L <<23)) >> 23;
    ints[24] = (bits & (1L <<24)) >> 24;
    ints[25] = (bits & (1L <<25)) >> 25;
    ints[26] = (bits & (1L <<26)) >> 26;
    ints[27] = (bits & (1L <<27)) >> 27;
    ints[28] = (bits & (1L <<28)) >> 28;
    ints[29] = (bits & (1L <<29)) >> 29;
    ints[30] = (bits & (1L <<30)) >> 30;
    ints[31] = (bits & (1L <<31)) >> 31;
    ints[32] = (bits & (1L <<32)) >> 32;
    ints[33] = (bits & (1L <<33)) >> 33;
    ints[34] = (bits & (1L <<34)) >> 34;
    ints[35] = (bits & (1L <<35)) >> 35;
    ints[36] = (bits & (1L <<36)) >> 36;
    ints[37] = (bits & (1L <<37)) >> 37;
    ints[38] = (bits & (1L <<38)) >> 38;
    ints[39] = (bits & (1L <<39)) >> 39;
    ints[40] = (bits & (1L <<40)) >> 40;
    ints[41] = (bits & (1L <<41)) >> 41;
    ints[42] = (bits & (1L <<42)) >> 42;
    ints[43] = (bits & (1L <<43)) >> 43;
    ints[44] = (bits & (1L <<44)) >> 44;
    ints[45] = (bits & (1L <<45)) >> 45;
    ints[46] = (bits & (1L <<46)) >> 46;
    ints[47] = (bits & (1L <<47)) >> 47;
    ints[48] = (bits & (1L <<48)) >> 48;
    ints[49] = (bits & (1L <<49)) >> 49;
    ints[50] = (bits & (1L <<50)) >> 50;
    ints[51] = (bits & (1L <<51)) >> 51;
    ints[52] = (bits & (1L <<52)) >> 52;
    ints[53] = (bits & (1L <<53)) >> 53;
    ints[54] = (bits & (1L <<54)) >> 54;
    ints[55] = (bits & (1L <<55)) >> 55;
    ints[56] = (bits & (1L <<56)) >> 56;
    ints[57] = (bits & (1L <<57)) >> 57;
    ints[58] = (bits & (1L <<58)) >> 58;
    ints[59] = (bits & (1L <<59)) >> 59;
    ints[60] = (bits & (1L <<60)) >> 60;
    ints[61] = (bits & (1L <<61)) >> 61;
    ints[62] = (bits & (1L <<62)) >> 62;
    ints[63] = (bits & (1L <<63)) >> 63;
    
}


//template void (*create_syntethic_data)(Matrix<int> &, int , Matrix<int> &, int, int);
