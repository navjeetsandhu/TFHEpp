#include <memory>
#include <tfhe++.hpp>
#include <vector>

int main()
{
    // generate a random key
    std::unique_ptr<TFHEpp::SecretKey> sk =
        std::make_unique<TFHEpp::SecretKey>();
    TFHEpp::EvalKey ek;
    int size;
    TFHEpp::TLWE<TFHEpp::lvl1param> cipher;
    std::vector<TFHEpp::TLWE<TFHEpp::lvl1param>> ciphertext;
    std::vector<uint8_t> message_p;

    // encrypt the input
    std::vector<uint8_t> p(1);
    p[0] = 1;
    ciphertext = TFHEpp::bootsSymEncrypt(p, *sk);
    cipher = ciphertext[0];
    size = cipher.size();
    std::cout << "encrypting: 1 " << std::endl;
    std::cout << std::hex << "cipher[0] " << cipher[0] << " cipher[1024] " << cipher[size-1] << std::endl;
    std::cout << std::dec << "cipher[0] " << cipher[0] << " cipher[1024] " << cipher[size-1] << " size = " << size << std::endl;
    std::cout << "\n";

    // decrypt and print plaintext answer
    message_p = TFHEpp::bootsSymDecrypt<TFHEpp::lvl1param>(ciphertext, *sk);
    if (message_p[0])
        std::cout << "Pass" << std::endl;
    else {
        std::cout << "Fail" << std::endl;
    }


    p[0] = 0;
    ciphertext = TFHEpp::bootsSymEncrypt(p, *sk);
    cipher = ciphertext[0];
    size = cipher.size();
    std::cout << "encrypting: 0 " << std::endl;
    std::cout << std::hex << "cipher[0] " << cipher[0] << " cipher[1024] " << cipher[size-1] << std::endl;
    std::cout << std::dec << "cipher[0] " << cipher[0] << " cipher[1024] " << cipher[size-1] << " size = " << size << std::endl;
    std::cout << "\n";

    // decrypt and print plaintext answer
    message_p = TFHEpp::bootsSymDecrypt<TFHEpp::lvl1param>(ciphertext, *sk);
    if (!message_p[0])
        std::cout << "Pass" << std::endl;
    else {
        std::cout << "Fail" << std::endl;
    }

}