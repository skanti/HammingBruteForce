#include <iostream>
#include <random>
#include "HamingBruteForce.h"
#include "Timer.h"

template<typename T, typename A = AlignedAllocator<T, 32>>
struct Matrix {
    Matrix(int n_rows_, int n_cols_) : n_rows(n_rows_), n_cols(n_cols_), data(n_rows * n_cols) {};

    inline T *memptr(int j = 0) { return data.data() + j * n_rows; }

    inline T &operator()(int i, int j) { return data[j * n_rows + i]; }

    int n_rows, n_cols;
    std::vector<T, A> data;
};

template<typename T>
void create_syntethic_data(Matrix<T> &a, int n_size_a, Matrix<T> &b, int n_size_b, int n_dim) {
    std::mt19937 mt(999);
    std::bernoulli_distribution dist_binary(0.5);
    for (int j = 0; j < n_size_a; j++)
        for (int i = 0; i < n_dim; i++)
            a(i, j) = dist_binary(mt);

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

int main() {
    typedef int haming_type;
    int n_dim = 256;
    int n_size_a = 500;
    int n_size_b = 500;
    Matrix<haming_type> a(n_dim, n_size_a);
    Matrix<haming_type> b(n_dim, n_size_b);
    HamingBruteForce<haming_type> hbf(2048, n_dim, 100);
    create_syntethic_data<haming_type>(a, n_size_a, b, n_size_b, n_dim);
    Timer::start();
    for (int i = 0; i < n_size_a; i++)
        for (int j = 0; j < n_size_b; j++)
            hbf.match(a.memptr(i), i, n_size_a, b.memptr(j), j, n_size_b);
    Timer::stop();
    std::cout << "timing (ms): " << Timer::get_timing_in_ms() << std::endl;
    /*
    for (int i = 0; i < n_size_a; i++)
        if (hbf.index_ab[i] != -1)
            std::cout << hbf.index_ab[i] << " " << hbf.distance_ab[i] << std::endl;
    */
}