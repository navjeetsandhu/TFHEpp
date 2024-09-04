#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <tfhe++.hpp>

void _assert(bool flag) {
    if(!flag) {
        std::cout << " Failed" << std::endl;
        throw std::runtime_error("Failed");
    }
    assert(flag);
}


namespace cuHEpp {
template <uint32_t Nbit, uint8_t radixbit>
void NTTdebug(
    std::array<INTorus, 1 << Nbit> &res,
    const std::array<INTorus, 1 << Nbit> &table,
    std::array<std::array<INTorus, 1 << Nbit>,
               Nbit / radixbit + ((Nbit % radixbit) > 0 ? 1 : 0)> &debug)
{
    constexpr uint8_t remainder = ((Nbit - 1) % radixbit) + 1;
    constexpr uint32_t size = 1U << remainder;
    constexpr uint32_t num_block = 1U << (Nbit - remainder);
    for (uint32_t block = 0; block < num_block; block++)
        NTTradixButterfly<remainder>(&res[size * block], size);
    debug[0] = res;
    int stage = 0;
    for (uint8_t sizebit = remainder + radixbit; sizebit <= Nbit;
         sizebit += radixbit) {
        const uint32_t size = 1U << sizebit;
        const uint32_t num_block = 1U << (Nbit - sizebit);
        for (uint32_t block = 0; block < num_block; block++)
            NTTradix<Nbit, radixbit>(&res[size * block], size, num_block,
                                     table);
        stage++;
        debug[stage] = res;
    }
}
}  // namespace cuHEpp

int main()
{
    constexpr uint32_t num_test = 1000;
    std::random_device seed_gen;
    std::default_random_engine engine(seed_gen());
    std::uniform_int_distribution<uint32_t> Bgdist(0, TFHEpp::lvl1param::Bg);
    std::uniform_int_distribution<uint32_t> Torus32dist(
        0, std::numeric_limits<typename TFHEpp::lvl1param::T>::max());

    const std::unique_ptr<
        const std::array<std::array<cuHEpp::INTorus, TFHEpp::lvl1param::n>, 2>>
        twistlvl1 = cuHEpp::TwistGen<TFHEpp::lvl1param::nbit>();
    const std::unique_ptr<
        const std::array<std::array<cuHEpp::INTorus, TFHEpp::lvl1param::n>, 2>>
        tablelvl1 = cuHEpp::TableGen<TFHEpp::lvl1param::nbit>();


    std::cout << "Start LVL1 test." << std::endl;
    for (int test = 0; test < num_test; test++) {
        // std::array<typename TFHEpp::lvl1param::T,TFHEpp::lvl1param::n> a,res;
        TFHEpp::Polynomial<TFHEpp::lvl1param> a, res;
        for (typename TFHEpp::lvl1param::T &i : a) i = Torus32dist(engine);
        std::array<cuHEpp::INTorus, TFHEpp::lvl1param::n> resntt;
        cuHEpp::TwistINTT<typename TFHEpp::lvl1param::T,
                          TFHEpp::lvl1param::nbit>(resntt, a, (*tablelvl1)[1],
                                                   (*twistlvl1)[1]);
        cuHEpp::TwistNTT<typename TFHEpp::lvl1param::T,
                         TFHEpp::lvl1param::nbit>(res, resntt, (*tablelvl1)[0],
                                                  (*twistlvl1)[0]);
        // for (int i = 0; i < TFHEpp::lvl1param::n; i++)
        // std::cout<<res[i]<<":"<<a[i]<<std::endl;
        for (int i = 0; i < TFHEpp::lvl1param::n; i++) _assert(a[i] == res[i]);
    }
    std::cout << "NTT Passed" << std::endl;



    return 0;
}
