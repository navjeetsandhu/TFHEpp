#pragma once
#include"../gate.hpp"

namespace TFHEpp{
#define INST(P) extern template void HomCONSTANTONE<P>(TLWE<P> & res)
INST(lvl1param);
INST(lvl0param);
#undef INST

#define INST(P) extern template void HomCONSTANTZERO<P>(TLWE<P> & res)
INST(lvl1param);
INST(lvl0param);
#undef INST

#define INST(P) extern template void HomNOT<P>(TLWE<P> & res, const TLWE<P> &ca)
INST(lvl1param);
INST(lvl0param);
#undef INST

#define INST(P) extern template void HomCOPY<P>(TLWE<P> & res, const TLWE<P> &ca)
INST(lvl1param);
INST(lvl0param);
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomNAND<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomNAND<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomNAND_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomNAND_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomNOR<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomNOR<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomNOR_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomNOR_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                                                \
    extern template void HomXNOR<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomXNOR<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                                                \
    extern template void HomXNOR_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomXNOR_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                                                \
    extern template void HomAND<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomAND<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                                                \
    extern template void HomAND_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomAND_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                                                \
    extern template void HomOR<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomOR<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomOR_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomOR_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomXOR<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomXOR<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomXOR_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomXOR_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                                                \
    extern template void HomANDNY<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomANDNY<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomANDNY_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomANDNY_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                                                \
    extern template void HomANDYN<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomANDYN<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomANDYN_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomANDYN_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomORNY<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomORNY<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomORNY_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomORNY_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomORYN<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomORYN<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                \
    extern template void HomORYN_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> &res, \
                                        const TLWE<typename iksP::domainP> &ca, \
                                        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                \
    extern template void HomORYN_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> &res, \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(P)                                                   \
    extern template void HomMUX<P>(TLWE<P> & res, const TLWE<P> &cs,     \
                            const TLWE<P> &c1, const TLWE<P> &c0, \
                            const EvalKey &ek)
INST(lvl1param);
INST(lvl0param);
#undef INST

#define INST(P)                                                   \
    extern template void HomMUX_NTT<P>(TLWE<P> & res, const TLWE<P> &cs,     \
                            const TLWE<P> &c1, const TLWE<P> &c0, \
                            const EvalKey &ek)
    INST(lvl1param);
    INST(lvl0param);
#undef INST


#define INST(P)                                                    \
    extern template void HomNMUX<P>(TLWE<P> & res, const TLWE<P> &cs,     \
                             const TLWE<P> &c1, const TLWE<P> &c0, \
                             const EvalKey &ek)
INST(lvl1param);
INST(lvl0param);
#undef INST

#define INST(P)                                                    \
    extern template void HomNMUX_NTT<P>(TLWE<P> & res, const TLWE<P> &cs,     \
                             const TLWE<P> &c1, const TLWE<P> &c0, \
                             const EvalKey &ek)
    INST(lvl1param);
    INST(lvl0param);
#undef INST

#define INST(bkP)                                                              \
    extern template void HomMUXwoIKSandSE<bkP>(TRLWE<typename bkP::targetP> & res,    \
                                        const TLWE<typename bkP::domainP> &cs, \
                                        const TLWE<typename bkP::domainP> &c1, \
                                        const TLWE<typename bkP::domainP> &c0, \
                                        const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_BLIND_ROTATE(INST)
#undef INST


#define INST(bkP)                                                              \
    extern template void HomMUXwoIKSandSE_NTT<bkP>(TRLWE<typename bkP::targetP> & res,    \
                                        const TLWE<typename bkP::domainP> &cs, \
                                        const TLWE<typename bkP::domainP> &c1, \
                                        const TLWE<typename bkP::domainP> &c0, \
                                        const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_BLIND_ROTATE(INST)
#undef INST


#define INST(iksP, bkP)                         \
    extern template void HomMUXwoSE<iksP, bkP>(        \
        TRLWE<typename bkP::targetP> & res,     \
        const TLWE<typename iksP::domainP> &cs, \
        const TLWE<typename iksP::domainP> &c1, \
        const TLWE<typename iksP::domainP> &c0, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE(INST)
#undef INST

#define INST(iksP, bkP)                         \
    extern template void HomMUXwoSE_NTT<iksP, bkP>(        \
        TRLWE<typename bkP::targetP> & res,     \
        const TLWE<typename iksP::domainP> &cs, \
        const TLWE<typename iksP::domainP> &c1, \
        const TLWE<typename iksP::domainP> &c0, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE(INST)
#undef INST

}