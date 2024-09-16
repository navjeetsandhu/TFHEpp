#include <algorithm>
#include "my_assert.h"
#include <iostream>
#include <random>
#include <tfhe++.hpp>

using namespace std;
using namespace TFHEpp;

int main()
{
    constexpr uint32_t num_test = 1;
    random_device seed_gen;
    default_random_engine engine(seed_gen());
    uniform_int_distribution<uint32_t> Bgdist(0, lvl1param::Bg);
    uniform_int_distribution<uint32_t> Torus32dist(0, UINT32_MAX);

    cout << "Start LVL1 test." << endl;
    for (int test = 0; test < num_test; test++) {
        Polynomial<lvl1param> a;
        for (typename TFHEpp::lvl1param::T &i : a) i = Torus32dist(engine);
        PolynomialNTT<lvl1param> resntt;
        TFHEpp::TwistINTT<lvl1param>(resntt, a);
        Polynomial<lvl1param> res;
        TFHEpp::TwistNTT<lvl1param>(res, resntt);
        for (int i = 0; i < lvl1param::n; i++)
            _assert(abs(static_cast<int32_t>(a[i] - res[i])) <= 1);
    }
    cout << "NTT Passed" << endl;

    for (int test = 0; test < num_test; test++) {
        alignas(64) array<typename TFHEpp::lvl1param::T, lvl1param::n> a;
        for (int i = 0; i < lvl1param::n; i++)
            a[i] = Bgdist(engine) - lvl1param::Bg / 2;
        for (typename TFHEpp::lvl1param::T &i : a)
            i = Bgdist(engine) - lvl1param::Bg / 2;
        alignas(64) array<typename TFHEpp::lvl1param::T, lvl1param::n> b;
        for (typename TFHEpp::lvl1param::T &i : b) i = Torus32dist(engine);

        alignas(64) Polynomial<lvl1param> polymul;
        TFHEpp::PolyMulNtt<lvl1param>(polymul, a, b);
        Polynomial<lvl1param> naieve = {};
        for (int i = 0; i < lvl1param::n; i++) {
            for (int j = 0; j <= i; j++)
                naieve[i] += static_cast<int32_t>(a[j]) * b[i - j];
            for (int j = i + 1; j < lvl1param::n; j++)
                naieve[i] -=
                    static_cast<int32_t>(a[j]) * b[lvl1param::n + i - j];
        }
        for (int i = 0; i < lvl1param::n; i++)
            _assert(abs(static_cast<int32_t>(naieve[i] - polymul[i])) <= 1);
    }
    cout << "PolyMul NTT Passed" << endl;


    return 0;
}