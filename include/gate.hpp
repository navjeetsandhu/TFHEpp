#pragma once

#include "cloudkey.hpp"
#include "gatebootstrapping.hpp"
#include "keyswitch.hpp"

namespace TFHEpp {
template <class brP, typename brP::targetP::T mu, class iksP, int casign,
          int cbsign, std::make_signed_t<typename brP::domainP::T> offset>
inline void HomGate(TLWE<typename iksP::targetP> &res,
                    const TLWE<typename brP::domainP> &ca,
                    const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    for (int i = 0; i <= brP::domainP::k * brP::domainP::n; i++)
        res[i] = casign * ca[i] + cbsign * cb[i];
    res[brP::domainP::k * brP::domainP::n] += offset;
    GateBootstrapping<brP, mu, iksP>(res, res, ek);
}

template <class iksP, class brP, typename brP::targetP::T mu, int casign,
          int cbsign, std::make_signed_t<typename iksP::domainP::T> offset>
inline void HomGate(TLWE<typename brP::targetP> &res,
                    const TLWE<typename iksP::domainP> &ca,
                    const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    for (int i = 0; i <= iksP::domainP::k * iksP::domainP::n; i++)
        res[i] = casign * ca[i] + cbsign * cb[i];
    res[iksP::domainP::k * iksP::domainP::n] += offset;
    GateBootstrapping<iksP, brP, mu>(res, res, ek);
}

template <class brP, typename brP::targetP::T mu, class iksP, int casign,
            int cbsign, std::make_signed_t<typename brP::domainP::T> offset>
inline void HomGateNTT(TLWE<typename iksP::targetP> &res,
                        const TLWE<typename brP::domainP> &ca,
                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
        for (int i = 0; i <= brP::domainP::k * brP::domainP::n; i++)
            res[i] = casign * ca[i] + cbsign * cb[i];
        res[brP::domainP::k * brP::domainP::n] += offset;
        GateBootstrappingNTT<brP, mu, iksP>(res, res, ek);
}

template <class iksP, class brP, typename brP::targetP::T mu, int casign,
            int cbsign, std::make_signed_t<typename iksP::domainP::T> offset>
inline void HomGateNTT(TLWE<typename brP::targetP> &res,
                        const TLWE<typename iksP::domainP> &ca,
                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
        for (int i = 0; i <= iksP::domainP::k * iksP::domainP::n; i++)
            res[i] = casign * ca[i] + cbsign * cb[i];
        res[iksP::domainP::k * iksP::domainP::n] += offset;
        GateBootstrappingNTT<iksP, brP, mu>(res, res, ek);
}


// No input
template <class P = lvl1param>
void HomCONSTANTONE(TLWE<P> &res)
{
    res = {};
    res[P::k * P::n] = P::mu;
}

template <class P = lvl1param>
void HomCONSTANTZERO(TLWE<P> &res)
{
    res = {};
    res[P::k * P::n] = -P::mu;
}

// 1 input
template <class P = lvl1param>
void HomNOT(TLWE<P> &res, const TLWE<P> &ca)
{
    for (int i = 0; i <= P::k * P::n; i++) res[i] = -ca[i];
}

template <class P = lvl1param>
void HomCOPY(TLWE<P> &res, const TLWE<P> &ca)
{
    for (int i = 0; i <= P::k * P::n; i++) res[i] = ca[i];
}

template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
          class iksP = lvl10param>
void HomNAND(TLWE<typename iksP::targetP> &res,
             const TLWE<typename brP::domainP> &ca,
             const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGate<brP, mu, iksP, -1, -1, brP::domainP::mu>(res, ca, cb, ek);
}

template <class iksP = lvl10param, class brP = lvl01param,
          typename brP::targetP::T mu = lvl1param::mu>
void HomNAND(TLWE<typename brP::targetP> &res,
             const TLWE<typename iksP::domainP> &ca,
             const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGate<iksP, brP, mu, -1, -1, iksP::domainP::mu>(res, ca, cb, ek);
}

template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
            class iksP = lvl10param>
void HomNAND_NTT(TLWE<typename iksP::targetP> &res,
                 const TLWE<typename brP::domainP> &ca,
                 const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGateNTT<brP, mu, iksP, -1, -1, brP::domainP::mu>(res, ca, cb, ek);
}

template <class iksP = lvl10param, class brP = lvl01param,
            typename brP::targetP::T mu = lvl1param::mu>
void HomNAND_NTT(TLWE<typename brP::targetP> &res,
                 const TLWE<typename iksP::domainP> &ca,
                 const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGateNTT<iksP, brP, mu, -1, -1, iksP::domainP::mu>(res, ca, cb, ek);
}

template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
          class iksP = lvl10param>
void HomNOR(TLWE<typename iksP::targetP> &res,
            const TLWE<typename brP::domainP> &ca,
            const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGate<brP, mu, iksP, -1, -1, -brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
          typename brP::targetP::T mu = lvl1param::mu>
void HomNOR(TLWE<typename brP::targetP> &res,
            const TLWE<typename iksP::domainP> &ca,
            const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGate<iksP, brP, mu, -1, -1, -iksP::domainP::mu>(res, ca, cb, ek);
}

template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
            class iksP = lvl10param>
void HomNOR_NTT(TLWE<typename iksP::targetP> &res,
                const TLWE<typename brP::domainP> &ca,
                const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
     HomGateNTT<brP, mu, iksP, -1, -1, -brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
            typename brP::targetP::T mu = lvl1param::mu>
void HomNOR_NTT(TLWE<typename brP::targetP> &res,
                const TLWE<typename iksP::domainP> &ca,
                const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
     HomGateNTT<iksP, brP, mu, -1, -1, -iksP::domainP::mu>(res, ca, cb, ek);
}

template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
          class iksP = lvl10param>
void HomXNOR(TLWE<typename iksP::targetP> &res,
             const TLWE<typename brP::domainP> &ca,
             const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGate<brP, mu, iksP, -2, -2, -2 * brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
          typename brP::targetP::T mu = lvl1param::mu>
void HomXNOR(TLWE<typename brP::targetP> &res,
             const TLWE<typename iksP::domainP> &ca,
             const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGate<iksP, brP, mu, -2, -2, -2 * iksP::domainP::mu>(res, ca, cb, ek);
}


template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
            class iksP = lvl10param>
void HomXNOR_NTT(TLWE<typename iksP::targetP> &res,
                 const TLWE<typename brP::domainP> &ca,
                 const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
     HomGateNTT<brP, mu, iksP, -2, -2, -2 * brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
            typename brP::targetP::T mu = lvl1param::mu>
void HomXNOR_NTT(TLWE<typename brP::targetP> &res,
                 const TLWE<typename iksP::domainP> &ca,
                 const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
     HomGateNTT<iksP, brP, mu, -2, -2, -2 * iksP::domainP::mu>(res, ca, cb, ek);
}

template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
          class iksP = lvl10param>
void HomAND(TLWE<typename iksP::targetP> &res,
            const TLWE<typename brP::domainP> &ca,
            const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGate<brP, mu, iksP, 1, 1, -brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
          typename brP::targetP::T mu = lvl1param::mu>
void HomAND(TLWE<typename brP::targetP> &res,
            const TLWE<typename iksP::domainP> &ca,
            const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGate<iksP, brP, mu, 1, 1, -iksP::domainP::mu>(res, ca, cb, ek);
}

template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
            class iksP = lvl10param>
void HomAND_NTT(TLWE<typename iksP::targetP> &res,
                const TLWE<typename brP::domainP> &ca,
                const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGateNTT<brP, mu, iksP, 1, 1, -brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
            typename brP::targetP::T mu = lvl1param::mu>
void HomAND_NTT(TLWE<typename brP::targetP> &res,
                const TLWE<typename iksP::domainP> &ca,
                const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGateNTT<iksP, brP, mu, 1, 1, -iksP::domainP::mu>(res, ca, cb, ek);
}


template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
          class iksP = lvl10param>
void HomOR(TLWE<typename iksP::targetP> &res,
           const TLWE<typename brP::domainP> &ca,
           const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGate<brP, mu, iksP, 1, 1, brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
          typename brP::targetP::T mu = lvl1param::mu>
void HomOR(TLWE<typename brP::targetP> &res,
           const TLWE<typename iksP::domainP> &ca,
           const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGate<iksP, brP, mu, 1, 1, iksP::domainP::mu>(res, ca, cb, ek);
}


template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
            class iksP = lvl10param>
void HomOR_NTT(TLWE<typename iksP::targetP> &res,
               const TLWE<typename brP::domainP> &ca,
               const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
     HomGateNTT<brP, mu, iksP, 1, 1, brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
            typename brP::targetP::T mu = lvl1param::mu>
void HomOR_NTT(TLWE<typename brP::targetP> &res,
               const TLWE<typename iksP::domainP> &ca,
               const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGateNTT<iksP, brP, mu, 1, 1, iksP::domainP::mu>(res, ca, cb, ek);
}

template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
          class iksP = lvl10param>
void HomXOR(TLWE<typename iksP::targetP> &res,
            const TLWE<typename brP::domainP> &ca,
            const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGate<brP, mu, iksP, 2, 2, 2 * brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
          typename brP::targetP::T mu = lvl1param::mu>
void HomXOR(TLWE<typename brP::targetP> &res,
            const TLWE<typename iksP::domainP> &ca,
            const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGate<iksP, brP, mu, 2, 2, 2 * iksP::domainP::mu>(res, ca, cb, ek);
}

 template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
            class iksP = lvl10param>
void HomXOR_NTT(TLWE<typename iksP::targetP> &res,
                const TLWE<typename brP::domainP> &ca,
                const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
     HomGateNTT<brP, mu, iksP, 2, 2, 2 * brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
            typename brP::targetP::T mu = lvl1param::mu>
void HomXOR_NTT(TLWE<typename brP::targetP> &res,
                const TLWE<typename iksP::domainP> &ca,
                const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
     HomGateNTT<iksP, brP, mu, 2, 2, 2 * iksP::domainP::mu>(res, ca, cb, ek);
}


template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
          class iksP = lvl10param>
void HomANDNY(TLWE<typename iksP::targetP> &res,
              const TLWE<typename brP::domainP> &ca,
              const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGate<brP, mu, iksP, -1, 1, -brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
          typename brP::targetP::T mu = lvl1param::mu>
void HomANDNY(TLWE<typename brP::targetP> &res,
              const TLWE<typename iksP::domainP> &ca,
              const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGate<iksP, brP, mu, -1, 1, -iksP::domainP::mu>(res, ca, cb, ek);
}

template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
            class iksP = lvl10param>
void HomANDNY_NTT(TLWE<typename iksP::targetP> &res,
                  const TLWE<typename brP::domainP> &ca,
                  const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGateNTT<brP, mu, iksP, -1, 1, -brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
            typename brP::targetP::T mu = lvl1param::mu>
void HomANDNY_NTT(TLWE<typename brP::targetP> &res,
                  const TLWE<typename iksP::domainP> &ca,
                  const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGateNTT<iksP, brP, mu, -1, 1, -iksP::domainP::mu>(res, ca, cb, ek);
}


template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
          class iksP = lvl10param>
void HomANDYN(TLWE<typename iksP::targetP> &res,
              const TLWE<typename brP::domainP> &ca,
              const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGate<brP, mu, iksP, 1, -1, -brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
          typename brP::targetP::T mu = lvl1param::mu>
void HomANDYN(TLWE<typename brP::targetP> &res,
              const TLWE<typename iksP::domainP> &ca,
              const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGate<iksP, brP, mu, 1, -1, -iksP::domainP::mu>(res, ca, cb, ek);
}

template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
            class iksP = lvl10param>
void HomANDYN_NTT(TLWE<typename iksP::targetP> &res,
                  const TLWE<typename brP::domainP> &ca,
                  const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
     HomGateNTT<brP, mu, iksP, 1, -1, -brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
            typename brP::targetP::T mu = lvl1param::mu>
void HomANDYN_NTT(TLWE<typename brP::targetP> &res,
                  const TLWE<typename iksP::domainP> &ca,
                  const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGateNTT<iksP, brP, mu, 1, -1, -iksP::domainP::mu>(res, ca, cb, ek);
}


template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
          class iksP = lvl10param>
void HomORNY(TLWE<typename iksP::targetP> &res,
             const TLWE<typename brP::domainP> &ca,
             const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGate<brP, mu, iksP, -1, 1, brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
          typename brP::targetP::T mu = lvl1param::mu>
void HomORNY(TLWE<typename brP::targetP> &res,
             const TLWE<typename iksP::domainP> &ca,
             const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGate<iksP, brP, mu, -1, 1, iksP::domainP::mu>(res, ca, cb, ek);
}

template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
            class iksP = lvl10param>
void HomORNY_NTT(TLWE<typename iksP::targetP> &res,
                 const TLWE<typename brP::domainP> &ca,
                 const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
     HomGateNTT<brP, mu, iksP, -1, 1, brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
            typename brP::targetP::T mu = lvl1param::mu>
void HomORNY_NTT(TLWE<typename brP::targetP> &res,
                 const TLWE<typename iksP::domainP> &ca,
                 const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGateNTT<iksP, brP, mu, -1, 1, iksP::domainP::mu>(res, ca, cb, ek);
}


template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
          class iksP = lvl10param>
void HomORYN(TLWE<typename iksP::targetP> &res,
             const TLWE<typename brP::domainP> &ca,
             const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGate<brP, mu, iksP, 1, -1, brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
          typename brP::targetP::T mu = lvl1param::mu>
void HomORYN(TLWE<typename brP::targetP> &res,
             const TLWE<typename iksP::domainP> &ca,
             const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGate<iksP, brP, mu, 1, -1, iksP::domainP::mu>(res, ca, cb, ek);
}


template <class brP = lvl01param, typename brP::targetP::T mu = lvl1param::mu,
            class iksP = lvl10param>
void HomORYN_NTT(TLWE<typename iksP::targetP> &res,
                 const TLWE<typename brP::domainP> &ca,
                 const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
{
    HomGateNTT<brP, mu, iksP, 1, -1, brP::domainP::mu>(res, ca, cb, ek);
}
template <class iksP = lvl10param, class brP = lvl01param,
            typename brP::targetP::T mu = lvl1param::mu>
void HomORYN_NTT(TLWE<typename brP::targetP> &res,
                 const TLWE<typename iksP::domainP> &ca,
                 const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
{
    HomGateNTT<iksP, brP, mu, 1, -1, iksP::domainP::mu>(res, ca, cb, ek);
}


// 3input
// cs?c1:c0
template <class P = lvl1param>
void HomMUX(TLWE<P> &res, const TLWE<P> &cs, const TLWE<P> &c1,
            const TLWE<P> &c0, const EvalKey &ek)
{
    TLWE<P> temp;
    for (int i = 0; i <= P::k * P::n; i++) temp[i] = cs[i] + c1[i];
    for (int i = 0; i <= P::k * P::n; i++) res[i] = -cs[i] + c0[i];
    temp[P::k * P::n] -= P::mu;
    res[P::k * P::n] -= P::mu;
    if constexpr (std::is_same_v<P, lvl1param>) {
        TLWE<lvl0param> and1, and0;
        IdentityKeySwitch<lvl10param>(and1, temp, *ek.iksklvl10);
        IdentityKeySwitch<lvl10param>(and0, res, *ek.iksklvl10);
        GateBootstrappingTLWE2TLWEFFT<lvl01param>(
            temp, and1, *ek.bkfftlvl01, mupolygen<lvl1param, lvl1param::mu>());
        GateBootstrappingTLWE2TLWEFFT<lvl01param>(
            res, and0, *ek.bkfftlvl01, mupolygen<lvl1param, lvl1param::mu>());
        for (int i = 0; i <= P::k * lvl1param::n; i++) res[i] += temp[i];
        res[P::k * P::n] += P::mu;
    }
    else if constexpr (std::is_same_v<P, lvl0param>) {
        TLWE<lvl1param> and1, and0;
        GateBootstrappingTLWE2TLWEFFT<lvl01param>(
            and1, temp, *ek.bkfftlvl01, mupolygen<lvl1param, lvl1param::mu>());
        GateBootstrappingTLWE2TLWEFFT<lvl01param>(
            and0, res, *ek.bkfftlvl01, mupolygen<lvl1param, lvl1param::mu>());
        for (int i = 0; i <= lvl1param::k * lvl1param::n; i++)
            and0[i] += and1[i];
        IdentityKeySwitch<lvl10param>(res, and0, *ek.iksklvl10);
        res[P::k * P::n] += P::mu;
    }
}


template <class P = lvl1param>
void HomMUX_NTT(TLWE<P> &res, const TLWE<P> &cs, const TLWE<P> &c1,
                const TLWE<P> &c0, const EvalKey &ek)
{
    TLWE<P> temp;
    for (int i = 0; i <= P::k * P::n; i++) temp[i] = cs[i] + c1[i];
    for (int i = 0; i <= P::k * P::n; i++) res[i] = -cs[i] + c0[i];
    temp[P::k * P::n] -= P::mu;
    res[P::k * P::n] -= P::mu;
    if constexpr (std::is_same_v<P, lvl1param>) {
        TLWE<lvl0param> and1, and0;
        IdentityKeySwitch<lvl10param>(and1, temp, *ek.iksklvl10);
        IdentityKeySwitch<lvl10param>(and0, res, *ek.iksklvl10);
        GateBootstrappingTLWE2TLWENTT<lvl01param>(
                temp, and1, *ek.bknttlvl01, mupolygen<lvl1param, lvl1param::mu>());
        GateBootstrappingTLWE2TLWENTT<lvl01param>(
                res, and0, *ek.bknttlvl01, mupolygen<lvl1param, lvl1param::mu>());
        for (int i = 0; i <= P::k * lvl1param::n; i++) res[i] += temp[i];
        res[P::k * P::n] += P::mu;
    }
    else if constexpr (std::is_same_v<P, lvl0param>) {
        TLWE<lvl1param> and1, and0;
        GateBootstrappingTLWE2TLWENTT<lvl01param>(
                and1, temp, *ek.bknttlvl01, mupolygen<lvl1param, lvl1param::mu>());
        GateBootstrappingTLWE2TLWENTT<lvl01param>(
                and0, res, *ek.bknttlvl01, mupolygen<lvl1param, lvl1param::mu>());
        for (int i = 0; i <= lvl1param::k * lvl1param::n; i++)
            and0[i] += and1[i];
        IdentityKeySwitch<lvl10param>(res, and0, *ek.iksklvl10);
        res[P::k * P::n] += P::mu;
    }
}

template <class P = lvl1param>
void HomNMUX(TLWE<P> &res, const TLWE<P> &cs, const TLWE<P> &c1,
             const TLWE<P> &c0, const EvalKey &ek)
{
    HomMUX<P>(res, cs, c1, c0, ek);
    for (int i = 0; i <= P::k * P::n; i++) res[i] = -res[i];
}

template <class P = lvl1param>
void HomNMUX_NTT(TLWE<P> &res, const TLWE<P> &cs, const TLWE<P> &c1,
           const TLWE<P> &c0, const EvalKey &ek)
{
    HomMUX_NTT<P>(res, cs, c1, c0, ek);
    for (int i = 0; i <= P::k * P::n; i++) res[i] = -res[i];
}

template <class bkP>
void HomMUXwoIKSandSE(TRLWE<typename bkP::targetP> &res,
                      const TLWE<typename bkP::domainP> &cs,
                      const TLWE<typename bkP::domainP> &c1,
                      const TLWE<typename bkP::domainP> &c0, const EvalKey &ek)
{
    TLWE<typename bkP::domainP> temp1;
    TLWE<typename bkP::domainP> temp0;
    for (int i = 0; i <= bkP::domainP::n; i++) temp1[i] = cs[i] + c1[i];
    for (int i = 0; i <= bkP::domainP::n; i++) temp0[i] = -cs[i] + c0[i];
    temp1[lvl0param::n] -= bkP::domainP::mu;
    temp0[lvl0param::n] -= bkP::domainP::mu;
    TRLWE<typename bkP::targetP> and0;
    BlindRotate<bkP>(res, temp1, ek.getbkfft<bkP>(),
                     mupolygen<typename bkP::targetP, bkP::targetP::mu>());
    BlindRotate<bkP>(and0, temp0, ek.getbkfft<bkP>(),
                     mupolygen<typename bkP::targetP, bkP::targetP::mu>());

    for (int i = 0; i < bkP::targetP::n; i++) {
        res[0][i] += and0[0][i];
        res[1][i] += and0[1][i];
    };
    res[1][0] += bkP::targetP::mu;
}

template <class bkP>
void HomMUXwoIKSandSE_NTT(TRLWE<typename bkP::targetP> &res,
                     const TLWE<typename bkP::domainP> &cs,
                     const TLWE<typename bkP::domainP> &c1,
                     const TLWE<typename bkP::domainP> &c0, const EvalKey &ek)
{
    TLWE<typename bkP::domainP> temp1;
    TLWE<typename bkP::domainP> temp0;
    for (int i = 0; i <= bkP::domainP::n; i++) temp1[i] = cs[i] + c1[i];
    for (int i = 0; i <= bkP::domainP::n; i++) temp0[i] = -cs[i] + c0[i];
    temp1[lvl0param::n] -= bkP::domainP::mu;
    temp0[lvl0param::n] -= bkP::domainP::mu;
    TRLWE<typename bkP::targetP> and0;
    BlindRotate<bkP>(res, temp1, ek.getbkntt<bkP>(),
                     mupolygen<typename bkP::targetP, bkP::targetP::mu>());
    BlindRotate<bkP>(and0, temp0, ek.getbkntt<bkP>(),
                     mupolygen<typename bkP::targetP, bkP::targetP::mu>());

    for (int i = 0; i < bkP::targetP::n; i++) {
        res[0][i] += and0[0][i];
        res[1][i] += and0[1][i];
    };
    res[1][0] += bkP::targetP::mu;
}


template <class brP, typename brP::targetP::T mu = brP::targetP::mu>
void HomMUXwoSE(TRLWE<typename brP::targetP> &res,
                const TLWE<typename brP::domainP> &cs,
                const TLWE<typename brP::domainP> &c1,
                const TLWE<typename brP::domainP> &c0, const EvalKey &ek)
{
    TLWE<typename brP::domainP> and1, and0;
    for (int i = 0; i <= brP::domainP::k * brP::domainP::n; i++)
        and1[i] = cs[i] + c1[i];
    for (int i = 0; i <= brP::domainP::k * brP::domainP::n; i++)
        and0[i] = -cs[i] + c0[i];
    and1[brP::domainP::k * brP::domainP::n] -= brP::domainP::mu;
    and0[brP::domainP::k * brP::domainP::n] -= brP::domainP::mu;
    TRLWE<typename brP::targetP> and0trlwe;
    BlindRotate<brP>(res, and1, ek.getbkfft<brP>(),
                     mupolygen<typename brP::targetP, brP::targetP::mu>());
    BlindRotate<brP>(and0trlwe, and0, ek.getbkfft<brP>(),
                     mupolygen<typename brP::targetP, brP::targetP::mu>());

    for (int i = 0; i < brP::targetP::k * brP::targetP::n; i++) {
        res[0][i] += and0trlwe[0][i];
        res[1][i] += and0trlwe[1][i];
    };
    res[1][0] += brP::targetP::mu;
}

template <class brP, typename brP::targetP::T mu = brP::targetP::mu>
    void HomMUXwoSE_NTT(TRLWE<typename brP::targetP> &res,
              const TLWE<typename brP::domainP> &cs,
              const TLWE<typename brP::domainP> &c1,
              const TLWE<typename brP::domainP> &c0, const EvalKey &ek)
{
    TLWE<typename brP::domainP> and1, and0;
    for (int i = 0; i <= brP::domainP::k * brP::domainP::n; i++)
        and1[i] = cs[i] + c1[i];
    for (int i = 0; i <= brP::domainP::k * brP::domainP::n; i++)
        and0[i] = -cs[i] + c0[i];
    and1[brP::domainP::k * brP::domainP::n] -= brP::domainP::mu;
    and0[brP::domainP::k * brP::domainP::n] -= brP::domainP::mu;
    TRLWE<typename brP::targetP> and0trlwe;
    BlindRotate<brP>(res, and1, ek.getbkntt<brP>(),
                     mupolygen<typename brP::targetP, brP::targetP::mu>());
    BlindRotate<brP>(and0trlwe, and0, ek.getbkntt<brP>(),
                     mupolygen<typename brP::targetP, brP::targetP::mu>());

    for (int i = 0; i < brP::targetP::k * brP::targetP::n; i++) {
        res[0][i] += and0trlwe[0][i];
        res[1][i] += and0trlwe[1][i];
    };
    res[1][0] += brP::targetP::mu;
}

template <class iksP, class brP, typename brP::targetP::T mu = brP::targetP::mu>
void HomMUXwoSE(TRLWE<typename brP::targetP> &res,
                const TLWE<typename iksP::domainP> &cs,
                const TLWE<typename iksP::domainP> &c1,
                const TLWE<typename iksP::domainP> &c0, const EvalKey &ek)
{
    TLWE<typename iksP::domainP> temp1, temp0;
    for (int i = 0; i <= iksP::domainP::k * iksP::domainP::n; i++)
        temp1[i] = cs[i] + c1[i];
    for (int i = 0; i <= iksP::domainP::k * iksP::domainP::n; i++)
        temp0[i] = -cs[i] + c0[i];
    temp1[iksP::domainP::k * iksP::domainP::n] -= iksP::domainP::mu;
    temp0[iksP::domainP::k * iksP::domainP::n] -= iksP::domainP::mu;
    TLWE<typename iksP::targetP> and1, and0;
    IdentityKeySwitch<iksP>(and1, temp1, ek.getiksk<iksP>());
    IdentityKeySwitch<iksP>(and0, temp0, ek.getiksk<iksP>());
    TRLWE<typename brP::targetP> and0trlwe;
    BlindRotate<brP>(res, and1, ek.getbkfft<brP>(),
                     mupolygen<typename brP::targetP, brP::targetP::mu>());
    BlindRotate<brP>(and0trlwe, and0, ek.getbkfft<brP>(),
                     mupolygen<typename brP::targetP, brP::targetP::mu>());

    for (int i = 0; i < brP::targetP::k * brP::targetP::n; i++) {
        res[0][i] += and0trlwe[0][i];
        res[1][i] += and0trlwe[1][i];
    };
    res[1][0] += brP::targetP::mu;
}

template <class iksP, class brP, typename brP::targetP::T mu = brP::targetP::mu>
    void HomMUXwoSE_NTT(TRLWE<typename brP::targetP> &res,
              const TLWE<typename iksP::domainP> &cs,
              const TLWE<typename iksP::domainP> &c1,
              const TLWE<typename iksP::domainP> &c0, const EvalKey &ek)
{
    TLWE<typename iksP::domainP> temp1, temp0;
    for (int i = 0; i <= iksP::domainP::k * iksP::domainP::n; i++)
        temp1[i] = cs[i] + c1[i];
    for (int i = 0; i <= iksP::domainP::k * iksP::domainP::n; i++)
        temp0[i] = -cs[i] + c0[i];
    temp1[iksP::domainP::k * iksP::domainP::n] -= iksP::domainP::mu;
    temp0[iksP::domainP::k * iksP::domainP::n] -= iksP::domainP::mu;
    TLWE<typename iksP::targetP> and1, and0;
    IdentityKeySwitch<iksP>(and1, temp1, ek.getiksk<iksP>());
    IdentityKeySwitch<iksP>(and0, temp0, ek.getiksk<iksP>());
    TRLWE<typename brP::targetP> and0trlwe;
    BlindRotate<brP>(res, and1, ek.getbkntt<brP>(),
                     mupolygen<typename brP::targetP, brP::targetP::mu>());
    BlindRotate<brP>(and0trlwe, and0, ek.getbkntt<brP>(),
                     mupolygen<typename brP::targetP, brP::targetP::mu>());

    for (int i = 0; i < brP::targetP::k * brP::targetP::n; i++) {
        res[0][i] += and0trlwe[0][i];
        res[1][i] += and0trlwe[1][i];
    };
    res[1][0] += brP::targetP::mu;
}


void ExtractSwitchAndHomMUX(TRLWE<lvl1param> &res, const TRLWE<lvl1param> &csr,
                            const TRLWE<lvl1param> &c1r,
                            const TRLWE<lvl1param> &c0r, const EvalKey &ek);

void ExtractSwitchAndHomMUX_NTT(TRLWE<lvl1param> &res, const TRLWE<lvl1param> &csr,
                            const TRLWE<lvl1param> &c1r,
                            const TRLWE<lvl1param> &c0r, const EvalKey &ek);
}  // namespace TFHEpp