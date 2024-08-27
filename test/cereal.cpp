#include <cassert>
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
            assert(sk.key.lvl0[i] == ski.key.lvl0[i]);
        for (int i = 0; i < TFHEpp::lvl1param::n; i++)
            assert(sk.key.lvl1[i] == ski.key.lvl1[i]);
        for (int i = 0; i < TFHEpp::lvl2param::n; i++)
            assert(sk.key.lvl2[i] == ski.key.lvl2[i]);
        std::cout << "n" << ":" << ski.params.lvl0.n << std::endl;
        assert(sk.params == ski.params);
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