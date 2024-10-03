#include <tfhe++.hpp>
#include "my_assert.h"
#include <chrono>
#include <iostream>
using namespace TFHEpp;
using namespace std;

uint8_t AndCheck(const uint8_t in0, const uint8_t in1) { return in0 * in1; }


void RunTest()
{

    cout << "------ Testing of NTT AND gate for lvl1param ------" << endl;
    SecretKey* sk = new SecretKey();
    TFHEpp::EvalKey ek;
    ek.emplacebkntt<TFHEpp::lvl01param>(*sk);
    ek.emplaceiksk<TFHEpp::lvl10param>(*sk);
    vector<uint8_t> p(2, 1);
    vector<uint8_t> p2(2);
    vector<TLWE<lvl1param>> cres(1);
    vector<TLWE<lvl1param>> c(2);

    c = bootsSymEncrypt<lvl1param>(p, *sk);

    TFHEpp::HomAND_NTT<lvl10param, lvl01param, lvl1param::mu>(cres[0], c[0], c[1], ek);

    p2 = bootsSymDecrypt<lvl1param>(cres, *sk);

    _assert(1 == p2[0]);
    cout << "------ pass ------" << endl;

}

int main()
{
    RunTest();
    return 0;
}