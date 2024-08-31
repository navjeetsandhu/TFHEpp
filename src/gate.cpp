#include <gate.hpp>

namespace TFHEpp {

void ExtractSwitchAndHomMUX(TRLWE<lvl1param> &res, const TRLWE<lvl1param> &csr,
                            const TRLWE<lvl1param> &c1r,
                            const TRLWE<lvl1param> &c0r, const EvalKey &ek)
{
    TLWE<lvl1param> templvl1;
    TLWE<lvl0param> cs, c1, c0;
    SampleExtractIndex<lvl1param>(templvl1, csr, 0);
    IdentityKeySwitch<lvl10param>(cs, templvl1, *ek.iksklvl10);
    SampleExtractIndex<lvl1param>(templvl1, c1r, 0);
    IdentityKeySwitch<lvl10param>(c1, templvl1, *ek.iksklvl10);
    SampleExtractIndex<lvl1param>(templvl1, c0r, 0);
    IdentityKeySwitch<lvl10param>(c0, templvl1, *ek.iksklvl10);

    for (int i = 0; i <= lvl0param::n; i++) c1[i] += cs[i];
    for (int i = 0; i <= lvl0param::n; i++) c0[i] -= cs[i];
    c1[lvl0param::n] -= lvl0param::mu;
    c0[lvl0param::n] -= lvl0param::mu;
    TRLWE<lvl1param> and0;
    BlindRotate<lvl01param>(res, c1, *ek.bkfftlvl01,
                            mupolygen<lvl1param, lvl1param::mu>());
    BlindRotate<lvl01param>(and0, c0, *ek.bkfftlvl01,
                            mupolygen<lvl1param, lvl1param::mu>());

    for (int i = 0; i < lvl1param::n; i++) {
        res[0][i] += and0[0][i];
        res[1][i] += and0[1][i];
    };
    res[1][0] += lvl1param::n;
}

void ExtractSwitchAndHomMUX_NTT(TRLWE<lvl1param> &res, const TRLWE<lvl1param> &csr,
                                const TRLWE<lvl1param> &c1r,
                                const TRLWE<lvl1param> &c0r, const EvalKey &ek)
{
    TLWE<lvl1param> templvl1;
    TLWE<lvl0param> cs, c1, c0;
    SampleExtractIndex<lvl1param>(templvl1, csr, 0);
    IdentityKeySwitch<lvl10param>(cs, templvl1, *ek.iksklvl10);
    SampleExtractIndex<lvl1param>(templvl1, c1r, 0);
    IdentityKeySwitch<lvl10param>(c1, templvl1, *ek.iksklvl10);
    SampleExtractIndex<lvl1param>(templvl1, c0r, 0);
    IdentityKeySwitch<lvl10param>(c0, templvl1, *ek.iksklvl10);

    for (int i = 0; i <= lvl0param::n; i++) c1[i] += cs[i];
    for (int i = 0; i <= lvl0param::n; i++) c0[i] -= cs[i];
    c1[lvl0param::n] -= lvl0param::mu;
    c0[lvl0param::n] -= lvl0param::mu;
    TRLWE<lvl1param> and0;
    BlindRotate<lvl01param>(res, c1, *ek.bknttlvl01,
                            mupolygen<lvl1param, lvl1param::mu>());
    BlindRotate<lvl01param>(and0, c0, *ek.bknttlvl01,
                            mupolygen<lvl1param, lvl1param::mu>());

    for (int i = 0; i < lvl1param::n; i++) {
        res[0][i] += and0[0][i];
        res[1][i] += and0[1][i];
    };
    res[1][0] += lvl1param::n;
}


#define INST(P) template void HomCONSTANTONE<P>(TLWE<P> & res)
INST(lvl1param);
INST(lvl0param);
#undef INST

#define INST(P) template void HomCONSTANTZERO<P>(TLWE<P> & res)
INST(lvl1param);
INST(lvl0param);
#undef INST

#define INST(P) template void HomNOT<P>(TLWE<P> & res, const TLWE<P> &ca)
INST(lvl1param);
INST(lvl0param);
#undef INST

#define INST(P) template void HomCOPY<P>(TLWE<P> & res, const TLWE<P> &ca)
INST(lvl1param);
INST(lvl0param);
#undef INST

#define INST(iksP, brP, mu)                      \
    template void HomNAND<iksP, brP, mu>(        \
        TLWE<typename brP::targetP> & res,      \
        const TLWE<typename iksP::domainP> &ca, \
        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                     \
    template void HomNAND<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, \
                                        const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                      \
    template void HomNAND_NTT<iksP, brP, mu>(        \
        TLWE<typename brP::targetP> & res,      \
        const TLWE<typename iksP::domainP> &ca, \
        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                     \
    template void HomNAND_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, \
                                        const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                     \
    template void HomNOR<iksP, brP, mu>(TLWE<typename brP::targetP> & res,      \
                                       const TLWE<typename iksP::domainP> &ca, \
                                       const TLWE<typename iksP::domainP> &cb, \
                                       const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                    \
    template void HomNOR<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                       const TLWE<typename brP::domainP> &ca, \
                                       const TLWE<typename brP::domainP> &cb, \
                                       const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                     \
    template void HomNOR_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> & res,      \
                                       const TLWE<typename iksP::domainP> &ca, \
                                       const TLWE<typename iksP::domainP> &cb, \
                                       const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                    \
    template void HomNOR_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                       const TLWE<typename brP::domainP> &ca, \
                                       const TLWE<typename brP::domainP> &cb, \
                                       const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                      \
    template void HomXNOR<iksP, brP, mu>(        \
        TLWE<typename brP::targetP> & res,      \
        const TLWE<typename iksP::domainP> &ca, \
        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                     \
    template void HomXNOR<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, \
                                        const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                      \
    template void HomXNOR_NTT<iksP, brP, mu>(        \
        TLWE<typename brP::targetP> & res,      \
        const TLWE<typename iksP::domainP> &ca, \
        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                     \
    template void HomXNOR_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, \
                                        const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                                                     \
    template void HomAND<iksP, brP, mu>(TLWE<typename brP::targetP> & res,      \
                                       const TLWE<typename iksP::domainP> &ca, \
                                       const TLWE<typename iksP::domainP> &cb, \
                                       const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                    \
    template void HomAND<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                       const TLWE<typename brP::domainP> &ca, \
                                       const TLWE<typename brP::domainP> &cb, \
                                       const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                                                     \
    template void HomAND_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> & res,      \
                                       const TLWE<typename iksP::domainP> &ca, \
                                       const TLWE<typename iksP::domainP> &cb, \
                                       const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                    \
    template void HomAND_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                       const TLWE<typename brP::domainP> &ca, \
                                       const TLWE<typename brP::domainP> &cb, \
                                       const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                                                    \
    template void HomOR<iksP, brP, mu>(TLWE<typename brP::targetP> & res,      \
                                      const TLWE<typename iksP::domainP> &ca, \
                                      const TLWE<typename iksP::domainP> &cb, \
                                      const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                   \
    template void HomOR<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                      const TLWE<typename brP::domainP> &ca, \
                                      const TLWE<typename brP::domainP> &cb, \
                                      const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                                                    \
    template void HomOR_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> & res,      \
                                      const TLWE<typename iksP::domainP> &ca, \
                                      const TLWE<typename iksP::domainP> &cb, \
                                      const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                   \
    template void HomOR_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                      const TLWE<typename brP::domainP> &ca, \
                                      const TLWE<typename brP::domainP> &cb, \
                                      const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                                                     \
    template void HomXOR<iksP, brP, mu>(TLWE<typename brP::targetP> & res,      \
                                       const TLWE<typename iksP::domainP> &ca, \
                                       const TLWE<typename iksP::domainP> &cb, \
                                       const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                    \
    template void HomXOR<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                       const TLWE<typename brP::domainP> &ca, \
                                       const TLWE<typename brP::domainP> &cb, \
                                       const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                                                     \
    template void HomXOR_NTT<iksP, brP, mu>(TLWE<typename brP::targetP> & res,      \
                                       const TLWE<typename iksP::domainP> &ca, \
                                       const TLWE<typename iksP::domainP> &cb, \
                                       const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                    \
    template void HomXOR_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                       const TLWE<typename brP::domainP> &ca, \
                                       const TLWE<typename brP::domainP> &cb, \
                                       const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST

#define INST(iksP, brP, mu)                      \
    template void HomANDNY<iksP, brP, mu>(       \
        TLWE<typename brP::targetP> & res,      \
        const TLWE<typename iksP::domainP> &ca, \
        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                     \
    template void HomANDNY<brP, mu, iksP>(      \
        TLWE<typename iksP::targetP> & res,    \
        const TLWE<typename brP::domainP> &ca, \
        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                      \
    template void HomANDNY_NTT<iksP, brP, mu>(       \
        TLWE<typename brP::targetP> & res,      \
        const TLWE<typename iksP::domainP> &ca, \
        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                     \
    template void HomANDNY_NTT<brP, mu, iksP>(      \
        TLWE<typename iksP::targetP> & res,    \
        const TLWE<typename brP::domainP> &ca, \
        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                      \
    template void HomANDYN<iksP, brP, mu>(       \
        TLWE<typename brP::targetP> & res,      \
        const TLWE<typename iksP::domainP> &ca, \
        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                     \
    template void HomANDYN<brP, mu, iksP>(      \
        TLWE<typename iksP::targetP> & res,    \
        const TLWE<typename brP::domainP> &ca, \
        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                      \
    template void HomANDYN_NTT<iksP, brP, mu>(       \
        TLWE<typename brP::targetP> & res,      \
        const TLWE<typename iksP::domainP> &ca, \
        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                     \
    template void HomANDYN_NTT<brP, mu, iksP>(      \
        TLWE<typename iksP::targetP> & res,    \
        const TLWE<typename brP::domainP> &ca, \
        const TLWE<typename brP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                      \
    template void HomORNY<iksP, brP, mu>(        \
        TLWE<typename brP::targetP> & res,      \
        const TLWE<typename iksP::domainP> &ca, \
        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                     \
    template void HomORNY<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, \
                                        const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                      \
    template void HomORNY_NTT<iksP, brP, mu>(        \
        TLWE<typename brP::targetP> & res,      \
        const TLWE<typename iksP::domainP> &ca, \
        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                     \
    template void HomORNY_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, \
                                        const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                      \
    template void HomORYN<iksP, brP, mu>(        \
        TLWE<typename brP::targetP> & res,      \
        const TLWE<typename iksP::domainP> &ca, \
        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                     \
    template void HomORYN<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, \
                                        const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(iksP, brP, mu)                      \
    template void HomORYN_NTT<iksP, brP, mu>(        \
        TLWE<typename brP::targetP> & res,      \
        const TLWE<typename iksP::domainP> &ca, \
        const TLWE<typename iksP::domainP> &cb, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_IKSBR(INST)
#undef INST
#define INST(brP, mu, iksP)                                                     \
    template void HomORYN_NTT<brP, mu, iksP>(TLWE<typename iksP::targetP> & res,    \
                                        const TLWE<typename brP::domainP> &ca, \
                                        const TLWE<typename brP::domainP> &cb, \
                                        const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE_BRIKS(INST)
#undef INST


#define INST(P)                                                   \
    template void HomMUX<P>(TLWE<P> & res, const TLWE<P> &cs,     \
                            const TLWE<P> &c1, const TLWE<P> &c0, \
                            const EvalKey &ek)
INST(lvl1param);
INST(lvl0param);
#undef INST


#define INST(P)                                                   \
    template void HomMUX_NTT<P>(TLWE<P> & res, const TLWE<P> &cs,     \
                            const TLWE<P> &c1, const TLWE<P> &c0, \
                            const EvalKey &ek)
    INST(lvl1param);
    INST(lvl0param);
#undef INST


#define INST(P)                                                    \
    template void HomNMUX<P>(TLWE<P> & res, const TLWE<P> &cs,     \
                             const TLWE<P> &c1, const TLWE<P> &c0, \
                             const EvalKey &ek)
INST(lvl1param);
INST(lvl0param);
#undef INST

#define INST(P)                                                    \
    template void HomNMUX_NTT<P>(TLWE<P> & res, const TLWE<P> &cs,     \
                             const TLWE<P> &c1, const TLWE<P> &c0, \
                             const EvalKey &ek)
    INST(lvl1param);
    INST(lvl0param);
#undef INST

#define INST(bkP)                                                              \
    template void HomMUXwoIKSandSE<bkP>(TRLWE<typename bkP::targetP> & res,    \
                                        const TLWE<typename bkP::domainP> &cs, \
                                        const TLWE<typename bkP::domainP> &c1, \
                                        const TLWE<typename bkP::domainP> &c0, \
                                        const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_BLIND_ROTATE(INST)
#undef INST

#define INST(bkP)                                                              \
    template void HomMUXwoIKSandSE_NTT<bkP>(TRLWE<typename bkP::targetP> & res,    \
                                        const TLWE<typename bkP::domainP> &cs, \
                                        const TLWE<typename bkP::domainP> &c1, \
                                        const TLWE<typename bkP::domainP> &c0, \
                                        const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_BLIND_ROTATE(INST)
#undef INST

#define INST(iksP, bkP)                         \
    template void HomMUXwoSE<iksP, bkP>(        \
        TRLWE<typename bkP::targetP> & res,     \
        const TLWE<typename iksP::domainP> &cs, \
        const TLWE<typename iksP::domainP> &c1, \
        const TLWE<typename iksP::domainP> &c0, const EvalKey &ek)
TFHEPP_EXPLICIT_INSTANTIATION_GATE(INST)
#undef INST


#define INST(iksP, bkP)                         \
    template void HomMUXwoSE_NTT<iksP, bkP>(        \
        TRLWE<typename bkP::targetP> & res,     \
        const TLWE<typename iksP::domainP> &cs, \
        const TLWE<typename iksP::domainP> &c1, \
        const TLWE<typename iksP::domainP> &c0, const EvalKey &ek)
    TFHEPP_EXPLICIT_INSTANTIATION_GATE(INST)
#undef INST

}  // namespace TFHEpp