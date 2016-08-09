#ifndef HAMINGBRUTEFORCE_TYPES_H
#define HAMINGBRUTEFORCE_TYPES_H

#include "AlignedAllocator.h"
#include <vector>

template<typename T, typename A = AlignedAllocator<T, 32>>
struct Matrix {
    Matrix(int n_rows_, int n_cols_) : n_rows(n_rows_), n_cols(n_cols_), data(n_rows * n_cols) {};

    inline T *memptr(int j = 0) { return data.data() + j * n_rows; }

    inline T &operator()(int i, int j) { return data[j * n_rows + i]; }

    int n_rows, n_cols;
    std::vector<T, A> data;
};

template class Matrix<int>;
template class Matrix<unsigned char>;
#endif //HAMINGBRUTEFORCE_TYPES_H
