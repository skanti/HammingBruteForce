#include <iostream>
#include <random>
#include "HamingBruteForce.h"
#include "Timer.h"
#include "MathKernels.h"
#include "Types.h"

typedef std::conditional<SIZE_BITS_HAMING == 32, int32_t, int64_t>::type type_haming;

extern "C" void match_all_ispc(const unsigned char *a, int n_size_a, const unsigned char *b, int n_size_b,
                               int n_dim, int *index_ab, int *distance_ab);

int main() {
    // -> setup
    int n_dim = 256;
    int n_dim_vec = n_dim / SIZE_BITS_HAMING;
    int n_size_a = 500;
    int n_size_b = 500;
    assert(n_size_a % N_THREADS == 0 && n_size_b % N_THREADS == 0);
    // <-

    // -> root arrays
    Matrix<type_haming> a(n_dim_vec, n_size_a);
    Matrix<type_haming> b(n_dim_vec, n_size_b);
    // <-
    create_syntethic_data<type_haming>(a, n_size_a, b, n_size_b, n_dim); // <- fill with made up values

    // -> scatter thread data and schedule
    int n_size_a_ti = n_size_a / N_THREADS;
    int n_size_b_ti = n_size_b / N_THREADS;
    int ld_a = n_dim_vec * n_size_a_ti;
    int ld_b = n_dim_vec * n_size_a_ti;
    std::vector<Matrix<type_haming> *> ai(N_THREADS);
    std::vector<Matrix<type_haming> *> bi(N_THREADS);
    std::vector<HamingBruteForce<type_haming> *> hbf(N_THREADS);

    for (int i = 0; i < N_THREADS; i++) {
        ai[i] = new Matrix<type_haming>(n_dim_vec, n_size_a_ti);
        std::copy(a.memptr() + ld_a * i, a.memptr() + ld_a * (i + 1), ai[i]->memptr());
        bi[i] = new Matrix<type_haming>(n_dim_vec, n_size_b_ti);
        std::copy(b.memptr() + ld_b * i, b.memptr() + ld_b * (i + 1), bi[i]->memptr());
        hbf[i] = new HamingBruteForce<type_haming>(512, n_dim, 100);
    }
    // <-
    // -> start actual haming brute forcing
    Timer::start();
    for (int i = 0; i < N_THREADS; i++) {
        hbf[i]->match_all(ai[i]->memptr(), n_size_a_ti, bi[i]->memptr(), n_size_b_ti);
    }

    Timer::stop();
    std::cout << "timing (ms): " << Timer::get_timing_in_ms() << std::endl;
    // <-

    // -> gather thread data to single file
    std::vector<int> index_ab(512, -1);
    std::vector<int> distance_ab(512, 100);
    for (int i = 0; i < N_THREADS; i++) {
        for (int j = 0; j < n_size_a_ti; j++) {
            index_ab[i * n_size_a_ti + j] = hbf[i]->index_ab[j] + i * n_size_a_ti;
            distance_ab[i * n_size_a_ti + j] = hbf[i]->distance_ab[j];
        }
    }
    // <-
    // -> print
    for (int i = 0; i < n_size_a; i++) {
        if (distance_ab[i] < 90)
            std::cout << "i: " << i << " j: " << index_ab[i] << " d: " << distance_ab[i] << std::endl;
    }
    // <-

    for (int i = 0; i < N_THREADS; i++) {
        delete ai[i];
        delete bi[i];
        delete hbf[i];
    }
}