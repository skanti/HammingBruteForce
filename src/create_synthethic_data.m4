include(`./src/Unroll.m4')
#include "Types.h"

template<typename T>
void create_syntethic_data(Matrix<T> &a, int n_size_a, Matrix<T> &b, int n_size_b, int n_dim) {

    std::mt19937 mt(999);
    std::bernoulli_distribution dist_binary(0.5);
    for (int j = 0; j < n_size_a; j++)
        for (int i = 0; i < n_dim / SIZE_BIT_HAMING; i++)
            a(i, j) = (dist_binary(mt) << 0) forloop(i, 1, eval(SIZE_BIT_HAMING-1), + ( dist_binary(mt) << i));

    for (int j = 0; j < n_size_b; j++)
        for (int i = 0; i < n_dim; i++)
            b(i, j) = dist_binary(mt);


    // -> make 'b' column 30 similiar as 'a' column 4
    std::copy(a.memptr(4), a.memptr(4) + n_dim, b.memptr(30));
    b(0, 30) = !a(0, 30);
    b(50, 30) = !a(50, 30);
    b(100, 30) = !a(100, 30);
    b(200, 30) = !a(200, 30);
}

void bits2ints(int &bits, int *ints) {
    forloop(i, 0, eval(SIZE_BIT_HAMING-1),
        ints[i] = (bits & (1<<i)) >> i;
    )
}


//template void (*create_syntethic_data)(Matrix<int> &, int , Matrix<int> &, int, int);
