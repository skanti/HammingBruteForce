#include <iostream>
#include <random>
#include "HamingBruteForce.h"
#include "Timer.h"
#include "Types.h"
#include "MathKernels.h"
#include <stdlib.h>

#define PI 3.14159265359

struct Corners {
    int x, y;
    float angle;
};

void create_synthetic_corners(Corners *corners, int n_features, int seed) {
    std::mt19937 mt(seed);
    std::uniform_real_distribution<float> u_dist(0, 1);
    for (int i = 0; i < n_features; i++) {
        corners[i].x = (int) (u_dist(mt) * 640);
        corners[i].y = (int) (u_dist(mt) * 480);
        corners[i].angle = (float) (u_dist(mt) * PI);
    }
}

void create_synthetic_data(Matrix<int64_t> &a, int n_size_a, Matrix<int64_t> &b, int n_size_b) {
    std::mt19937 mt(999);
    std::bernoulli_distribution dist_binary(0.5);
    std::vector<int64_t> tmp(256);
    for (int j = 0; j < n_size_a; j++) {
        for (int i = 0; i < 256; i++) {
            tmp[i] = dist_binary(mt);
        }
        for (int i = 0; i < 4; i++)
            ints2bits(a(i, j), &tmp[i * SIZE_BITS_HAMING]);
    }
    for (int j = 0; j < n_size_b; j++) {
        for (int i = 0; i < 256; i++) {
            tmp[i] = dist_binary(mt);
        }
        for (int i = 0; i < 4; i++)
            ints2bits(b(i, j), &tmp[i * SIZE_BITS_HAMING]);
    }

    // -> make 'b' column 30 similiar as 'a' column 4
    //std::copy(a.memptr(4), a.memptr(4) + n_dim/64, b.memptr(30));
    memcpy(b.memptr(30), a.memptr(4), 256 / 8);
    b(0, 30) = ~a(0, 4);
}


int main() {
    // -> setup
    int n_size_a = 500;
    int n_size_b = 500;
    // <-

    // -> root arrays
    Matrix<int64_t> a(4, n_size_a);
    Matrix<int64_t> b(4, n_size_b);
    std::vector<Corners> corners_a(n_size_a);
    std::vector<Corners> corners_b(n_size_b);
    // <-

    create_synthetic_data(a, n_size_a, b, n_size_b); // <- fill with made up values
    create_synthetic_corners(corners_a.data(), n_size_a, 999); // <- fill with made up values
    create_synthetic_corners(corners_b.data(), n_size_b, 42); // <- fill with made up values

    HamingBruteForce hbf(512, 100);
    // -> start actual haming brute forcing
    Timer::start();
    hbf.match_all(a.memptr(), n_size_a, b.memptr(), n_size_b);
    Timer::stop();
    std::cout << "match_all: timing (ms): " << Timer::get_timing_in_ms() << std::endl;

    Timer::start();
    hbf.refine_distance(corners_a.data(), corners_b.data(), n_size_a, 40, PI / 4);
    Timer::stop();
    std::cout << "refine: timing (ms): " << Timer::get_timing_in_ms() << std::endl;

    // <-

    // -> print
    for (int i = 0; i < n_size_a; i++) {
        if (hbf.distance_ab[i] < 90)
            std::cout << "i: " << i << " j: " << hbf.index_ab[i] << " d: " << hbf.distance_ab[i] << std::endl;
    }
    // <-
}