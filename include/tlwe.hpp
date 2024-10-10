#pragma once

#include <array>
#include <cstdint>
#include <vector>

#include "key.hpp"
#include "params.hpp"
#include "utils.hpp"


//  p is input message:  which is  0xE0000000 or  0x20000000
//  for lvl1param p is 0xE0000000(3758096384) for encrypting 0
//  for lvl1param p is 536870912 (0x20000000) for encrypting 1
//  for lvl1param alpha = (1/(2^25)) for adding some Gaussian noise
namespace TFHEpp {
template <class P>
TLWE<P> tlweSymEncrypt(const typename P::T p, const double alpha, const Key<P> &key)
{
    TLWE<P> res = {};
                                   //  for lvl1param k = 1 and n = 1024 ,
    int last_index = P::k * P::n;  //  for lvl1param last_index = 1024
    int k, i, j;
    constexpr auto numeric_limits = std::numeric_limits<typename P::T>::max();

    //This is for mask coefficients
    std::uniform_int_distribution<typename P::T> Torusdist(0,numeric_limits);

    // add some noise i.e. for message (p) 536870912 add some noise and make it 536870870
    res[last_index] = ModularGaussian<P>(p, alpha);

    for (k = 0; k < P::k; k++)
        for (i = 0; i < P::n; i++) {
            j = k * P::n + i;
            res[j] = Torusdist(generator);
            res[last_index] += res[j] * key[j];
        }
    // for lvl1param k = 1 and n = 1024, res.size is 1025,
    // first 1024 are coefficients of masks and
    // last one is message which is masked with mask*key and noise
    return res;
}

template <class P>
TLWE<P> tlweSymEncrypt(const typename P::T p, const uint eta, const Key<P> &key)
{
    std::uniform_int_distribution<typename P::T> Torusdist(0, P::q - 1);
    TLWE<P> res = {};
    res[P::k * P::n] =
        p + CenteredBinomial<P>(eta)
        << (std::numeric_limits<typename P::T>::digits - P::qbit);
    for (int k = 0; k < P::k; k++)
        for (int i = 0; i < P::n; i++) {
            res[k * P::n + i] =
                Torusdist(generator)
                << (std::numeric_limits<typename P::T>::digits - P::qbit);
            res[P::k * P::n] += res[k * P::n + i] * key[k * P::n + i];
        }
    return res;
}

template <class P>
TLWE<P> tlweSymEncrypt(const typename P::T p, const Key<P> &key)
{
    if constexpr (P::errordist == ErrorDistribution::ModularGaussian)
        return tlweSymEncrypt<P>(p, P::alpha, key);
    else
        return tlweSymEncrypt<P>(p, P::eta, key);
}

template <class P>
TLWE<P> tlweSymIntEncrypt(const typename P::T p, const double alpha,
                          const Key<P> &key)
{
    return tlweSymEncrypt<P>(static_cast<typename P::T>(p * P::delta), alpha, key);
}

template <class P>
TLWE<P> tlweSymIntEncrypt(const typename P::T p, const uint eta,
                          const Key<P> &key)
{
    return tlweSymEncrypt<P>(static_cast<typename P::T>(p * P::delta), eta, key);
}

template <class P>
TLWE<P> tlweSymIntEncrypt(const typename P::T p, const Key<P> &key)
{
    if constexpr (P::errordist == ErrorDistribution::ModularGaussian)
        return tlweSymIntEncrypt<P>(p, P::alpha, key); // P::alpha = (1/(2^25)) for lvl1param
    else
        return tlweSymIntEncrypt<P>(p, P::eta, key);
}

template <class P>
typename P::T tlweSymPhase(const TLWE<P> &c, const Key<P> &key)
{
    typename P::T phase = c[P::k * P::n];
    // remove the mask from the message
    for (int k = 0; k < P::k; k++)
        for (int i = 0; i < P::n; i++)
            phase -= c[k * P::n + i] * key[k * P::n + i];
    return phase;
}

// Decrypt the message
template <class P>
bool tlweSymDecrypt(const TLWE<P> &c, const Key<P> &key)
{
    // remove the mask from the message
    typename P::T phase = tlweSymPhase<P>(c, key);
    // phase has only message plus error
    // if MSB bit is set than text message is zero or else it is 1.
    bool res =
        static_cast<typename std::make_signed<typename P::T>::type>(phase) > 0;
    return res;
}

template <class P, const uint plain_modulus>
typename P::T tlweSymIntDecrypt(const TLWE<P> &c, const Key<P> &key)
{
    constexpr double delta =
        2 *
        static_cast<double>(
            1ULL << (std::numeric_limits<typename P::T>::digits - 1)) /
        plain_modulus;
    const typename P::T phase = tlweSymPhase<P>(c, key);
    typename P::T res = static_cast<typename P::T>(std::round(phase / delta));
    return res >= plain_modulus / 2 ? res - plain_modulus : res;
}

template <class P>
typename P::T tlweSymIntDecrypt(const TLWE<P> &c, const Key<P> &key)
{
    return tlweSymIntDecrypt<P, P::plain_modulus>(c, key);
}


//encrypt the vector of binary (1 or 0)
// For lvl1param  P::mu = 1 << 29 = 536870912 =  0x2000000
// lvl1param  -P::mu = -536870912 =  0xE000000
template <class P>
std::vector<TLWE<P>> bootsSymEncrypt(const std::vector<uint8_t> &p,
                                     const Key<P> &key)
{
    vector<TLWE<P>> c(p.size());
#pragma omp parallel for
    for (int i = 0; i < p.size(); i++)
        c[i] = tlweSymEncrypt<P>(p[i] ? P::mu : -P::mu, key);

    return c;
}

template <class P = lvl1param>
std::vector<TLWE<P>> bootsSymEncrypt(const std::vector<uint8_t> &p,
                                     const SecretKey &sk)
{
    return bootsSymEncrypt<P>(p, sk.key.get<P>());
}

template <class P>
std::vector<uint8_t> bootsSymDecrypt(const std::vector<TLWE<P>> &c,
                                     const Key<P> &key)
{
    vector<uint8_t> p(c.size());
#pragma omp parallel for
    for (int i = 0; i < c.size(); i++) p[i] = tlweSymDecrypt<P>(c[i], key);
    return p;
}

template <class P = lvl1param>
std::vector<uint8_t> bootsSymDecrypt(const std::vector<TLWE<P>> &c,
                                     const SecretKey &sk)
{
    return bootsSymDecrypt<P>(c, sk.key.get<P>());
}

}  // namespace TFHEpp