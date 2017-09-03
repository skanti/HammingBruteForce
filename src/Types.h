#pragma once
#include <stdlib.h>
#include <cstdint>

template<typename T, int A = 16>
struct Matrix {
    Matrix(int n_rows_, int n_cols_) : n_rows(n_rows_), n_cols(n_cols_) {
        posix_memalign((void **) &data, A, n_rows * n_cols * sizeof(T));
    };

    Matrix() {
		data = 0;
	}

    ~Matrix() {
        if (data) free(data);
    }

    inline T *memptr(int j = 0) { return data + j * n_rows; }

    inline T &operator()(int i, int j) { return data[j * n_rows + i]; }

    int n_rows, n_cols;
    T *data;
};

template
class Matrix<int32_t>;

template
class Matrix<int64_t>;

template
class Matrix<uint32_t>;

template
class Matrix<uint64_t>;

