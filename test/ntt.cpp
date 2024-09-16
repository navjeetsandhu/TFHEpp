#include <algorithm>
#include "my_assert.h"
#include <iostream>
#include <random>
#include <tfhe++.hpp>
#include <fstream>


void storeInFile() {
    std::random_device seed_gen;
    std::default_random_engine engine(seed_gen());
    std::uniform_int_distribution<uint32_t> Torus32dist(
            0, std::numeric_limits<typename TFHEpp::lvl1param::T>::max());

    std::ofstream file("torus32dist.txt");
    TFHEpp::Polynomial<TFHEpp::lvl1param> a;
    std::cout << std::endl << "Storing to file torus32dist.txt " << std::endl;
    for (typename TFHEpp::lvl1param::T &i : a) {
        i = Torus32dist(engine);
        file << i << std::endl;
    }
    file.close();
}

int  readFromFile(std::vector<uint32_t>& data, bool flag = false) {
    std::random_device seed_gen;
    std::default_random_engine engine(seed_gen());
    std::uniform_int_distribution<uint32_t> Torus32dist(
            0, std::numeric_limits<typename TFHEpp::lvl1param::T>::max());

    if (flag) std::cout << std::endl << "Reading from file torus32dist.txt " << std::endl;

    std::ifstream file("../../test/torus32dist.txt");
    if (!file)
    {
        std::cerr << "Unable to open torus32dist.txt file" << std::endl;
        return -1;
    }

    uint32_t value;
    while (file >> value)
    {
        // Push each value into the vector
        data.push_back(value);
    }

    // print values
    if (flag)
        for (const auto &i : data)
            std::cout << i << " ";


    file.close();
    return 0;
}

void more_ntt_tests() {
    constexpr uint32_t num_test = 100;
    TFHEpp::random_device seed_gen;
    TFHEpp::default_random_engine engine(seed_gen());
    TFHEpp::uniform_int_distribution <uint32_t> Torus32dist(0, UINT32_MAX);


    std::cout << std::endl << "Start randoms test." << std::endl;
    for (int test = 0; test < num_test; test++) {
        TFHEpp::Polynomial <TFHEpp::lvl1param> a;
        for (typename TFHEpp::lvl1param::T &i: a) i = Torus32dist(engine);
        TFHEpp::PolynomialNTT <TFHEpp::lvl1param> resntt;
        TFHEpp::TwistINTT<TFHEpp::lvl1param>(resntt, a);
        TFHEpp::Polynomial <TFHEpp::lvl1param> res;
        TFHEpp::TwistNTT<TFHEpp::lvl1param>(res, resntt);
        for (int i = 0; i < TFHEpp::lvl1param::n; i++)
            _assert(a[i] == res[i]);
    }
    std::cout << "NTT Passed" << std::endl;
}

int main(int argc, char *argv[]) {
    uint32_t num_print = TFHEpp::lvl1param::n;
    uint32_t i, test_case = 0;
    std::vector<uint32_t> data;

    printf("Example: ./twist_ntt 5 0  \n");
    printf("Program name: %s: argc: %d ", argv[0], argc);

    if(argc > 1) {
        for(i = 1; i < argc; i++) {
            printf("Argument %d: %s ", i, argv[i]);

            if (i==1) {
                num_print = std::stoi(argv[i]);
                printf("num_print: %d ", num_print);
            }

            if (i==2) {
                test_case = std::stoi(argv[i]);
                printf("test_case: %d ", test_case );
            }
        }
    } else {
        printf("No command line arguments were passed. ");
    }
    std::cout << std::endl << std::endl;
    readFromFile(data);

    TFHEpp::Polynomial<TFHEpp::lvl1param> input, res;
    int j =0;
    for (typename TFHEpp::lvl1param::T &element : input) {
        element = data[j];
        j++;
    }
    std::array<cuHEpp::INTorus, TFHEpp::lvl1param::n> resntt;

    if( test_case == 0) {
        std::cout << std::endl << "\nStart HEXL test" << std::endl;
        TFHEpp::TwistINTT<TFHEpp::lvl1param>(resntt, input);
        TFHEpp::TwistNTT<TFHEpp::lvl1param>(res, resntt);
    }
    if(test_case == 1) {
        storeInFile();
    }
    if(test_case == 2) {
        readFromFile(data, true);
    }

    std::cout << "NTT input" << std::endl;
    std::cout << std::dec;
    for (i = 0; i < num_print; i++) {
        std::cout << input[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "TwistNTT_lvl1param_test input on HEX:" << std::endl;
    std::cout << std::hex;
    for (i = 0; i < num_print; i++) {
        std::cout << input[i] << " ";
    }

    for (i = 0; i < TFHEpp::lvl1param::n; i++) _assert(input[i] == res[i]);
    std::cout << std::endl << "First NTT Passed" << std::endl;


    more_ntt_tests();

    return 0;
}
