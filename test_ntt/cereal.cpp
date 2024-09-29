#include "my_assert.h"
#include <fstream>
#include <iostream>
#include <tfhe++.hpp>

int main()
{
    // create a secret key.  Fully homomorphic encryption (FHE) allows computation
    // on encrypted data (ciphertext) without needing to decrypt it first.
    // The results of this computation are then encrypted and can be later
    // decrypted with the respective secret key.
    TFHEpp::SecretKey sk;
    {
        {
            std::ofstream ofs{"./secret.key", std::ios::binary};
            cereal::PortableBinaryOutputArchive ar(ofs);
            sk.serialize(ar);
        }
        TFHEpp::SecretKey ski;
        {
            std::ifstream ifs{"./secret.key", std::ios::binary};
            cereal::PortableBinaryInputArchive ar(ifs);
            ski.serialize(ar);
        }
        for (int i = 0; i < TFHEpp::lvl0param::n; i++)
            _assert(sk.key.lvl0[i] == ski.key.lvl0[i]);
        for (int i = 0; i < TFHEpp::lvl1param::n; i++)
            _assert(sk.key.lvl1[i] == ski.key.lvl1[i]);
        for (int i = 0; i < TFHEpp::lvl2param::n; i++)
            _assert(sk.key.lvl2[i] == ski.key.lvl2[i]);

        for (int i = 0; i < 10; i++)
            std::cout << "sk.key.lvl0[" << i << "]"<< ": " << ski.key.lvl0[i] << std::endl;
        for (int i = 0; i < 10; i++)
            std::cout << "sk.key.lvl1[" << i << "]"<< ": " << ski.key.lvl1[i] << std::endl;
        for (int i = 0; i < 10; i++)
            std::cout << "sk.key.lvl2[" << i << "]"<< ": " << ski.key.lvl2[i] << std::endl;

        std::cout << "ski.params.lvl0.n" << ": " << ski.params.lvl0.n << std::endl;
        std::cout << "ski.params.lvl0.n" << ": " << ski.params.lvl0.n << std::endl;
        std::cout << "ski.params.lvl0.l" << ": " << ski.params.lvl0.approx_bit << std::endl;
        std::cout << "ski.params.lvl0.Bg" << ": " << ski.params.lvl0.alpha << std::endl;
        std::cout << "ski.params.lvl0.alpha" << ": " << ski.params.lvl1.alpha << std::endl;
        std::cout << "ski.params.lvl0.approx_bit" << ": " << ski.params.lvl1.approx_bit << std::endl;

        std::cout << "ski.params.lvl1.n" << ": " << ski.params.lvl1.n << std::endl;
        std::cout << "ski.params.lvl1.l" << ": " << ski.params.lvl1.l << std::endl;
        std::cout << "ski.params.lvl1.Bg" << ": " << ski.params.lvl1.Bg << std::endl;
        std::cout << "ski.params.lvl1.alpha" << ": " << ski.params.lvl1.alpha << std::endl;
        std::cout << "ski.params.lvl1.approx_bit" << ": " << ski.params.lvl1.approx_bit << std::endl;


        std::cout << "ski.params.lvl.l" << ": " << ski.params.lvl2.l << std::endl;
        std::cout << "ski.params.lvl1.Bg" << ": " << ski.params.lvl2.Bg << std::endl;
        std::cout << "ski.params.lvl2.approx_bit" << ": " << ski.params.lvl2.approx_bit << std::endl;
        std::cout << "ski.params.lvl1.approx_bit" << ": " << ski.params.lvl1.approx_bit << std::endl;
        std::cout << "ski.params.lvl2.n n" << ": " << ski.params.lvl2.n << std::endl;
    }

    {
        TFHEpp::IOpacket iopacket;
        iopacket.tlwelvl0ports["test"].resize(1);
        iopacket.tlwelvl0ports["test"][0] =
            TFHEpp::tlweSymEncrypt<TFHEpp::lvl0param>(
                TFHEpp::lvl0param::mu, TFHEpp::lvl0param::alpha, sk.key.lvl0);
        {
            std::ofstream ofs{"./iopacket.data", std::ios::binary};
            cereal::PortableBinaryOutputArchive ar(ofs);
            iopacket.serialize(ar);
        }
    }

    {
        //create an Evaluation Key, ek, using the Secret Key sk.
        TFHEpp::EvalKey ek(sk);
        // creates and sets values for a Bootstrapping Key FFT (Fast Fourier Transform)
        // inside our ek. It is based on the secret key sk and parameter set lvl01param.
        ek.emplacebkfft<TFHEpp::lvl01param>(sk);
        //create and set values for a Bootstrapping Key NTT (Number Theoretic Transform) in ek object.
        ek.emplacebkntt<TFHEpp::lvl01param>(sk);

        const TFHEpp::BootstrappingKeyNTT<TFHEpp::lvl01param>& bknttlvl01 = ek.getbkntt<TFHEpp::lvl01param>();
        const TFHEpp::TRGSWNTT<TFHEpp::lvl1param> trgswntt = bknttlvl01[0];
        const TFHEpp::TRLWENTT<TFHEpp::lvl1param> trlwentt = trgswntt[0];
        const TFHEpp::PolynomialNTT<TFHEpp::lvl1param> polynomialNTT = trlwentt[0];

        std::cout << "bknttlvl01.size()" << ": " << bknttlvl01.size() << std::endl;  //636
        std::cout << "trgswntt.size()" << ": " << trgswntt.size() << std::endl;  //6
        std::cout << "trlwentt.size()" << ": " << trlwentt.size() << std::endl;  //2
        std::cout << "polynomialNTT.size()" << ": " << polynomialNTT.size() << std::endl; //1024

        int bkn, trgsw, trlw, poly;
        for (bkn = 0; bkn <2; bkn++)
            for (trgsw = 0; trgsw <2; trgsw++)
                for (trlw = 0; trlw <2; trlw++)
                    for (poly = 0; poly <2; poly++)
                            std::cout << " " << ": " << bknttlvl01[bkn][trgsw][trlw][poly].value << std::endl;


        //use the secret key sk to create a Level-1 to Level-0 identity key switch key (IKS Key).
        //dentity Key Switching (IKS) are techniques used in homomorphic encryption to translate
        // between different encryption keys. In this case, it is creating a key that will translate
        // ciphertext encrypted with a Level-1 key into ciphertext encrypted with a Level-0 key.
        ek.emplaceiksk<TFHEpp::lvl10param>(sk);
        {
            std::ofstream ofs{"./gatekey.key", std::ios::binary};
            cereal::PortableBinaryOutputArchive ar(ofs);
            ek.serialize(ar);
        }
    }
    {
        TFHEpp::EvalKey ek;
        {
            std::ifstream ifs{"./gatekey.key", std::ios::binary};
            cereal::PortableBinaryInputArchive ar(ifs);
            ek.serialize(ar);
            std::cout << (ek.params.lvl0.n) << std::endl;
        }
    }
}