#ifndef SIZE_BIT_HAMING
#define SIZE_BIT_HAMING 32
#endif

#include <iostream>
#include <random>
#include "HamingBruteForce.h"
#include "Timer.h"
#include "create_synthethic_data.h"
#include "Types.h"

typedef int type_haming;

extern "C" void match_all_ispc(const unsigned char *a, int n_size_a, const unsigned char *b, int n_size_b,
                               int n_dim, int *index_ab, int *distance_ab);

int main() {
    int n_dim = 256;
    int n_size_a = 500;
    int n_size_b = 500;
    Matrix<type_haming> a(n_dim / SIZE_BIT_HAMING, n_size_a);
    Matrix<type_haming> b(n_dim / SIZE_BIT_HAMING, n_size_b);
    HamingBruteForce<type_haming> hbf(1024, n_dim, 100);
    create_syntethic_data<type_haming>(a, n_size_a, b, n_size_b, n_dim);
    Timer::start();

    //match_all_ispc(a.memptr(), n_size_a, b.memptr(), n_size_b, n_dim, hbf.index_ab.data(), hbf.distance_ab.data());
    hbf.match_all(a.memptr(), n_size_a, b.memptr(), n_size_b);
    Timer::stop();
    std::cout << "timing (ms): " << Timer::get_timing_in_ms() << std::endl;
    for (int i = 0; i < n_size_a; i++) {
        if (hbf.distance_ab[i] < 100)
            std::cout << "i: " << i << " j: " << hbf.index_ab[i] << " d: " << hbf.distance_ab[i] << std::endl;
    }
}