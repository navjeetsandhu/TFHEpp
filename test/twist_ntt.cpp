#include <algorithm>
#include <cassert>
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


void  applyBitShifting(std::vector<uint32_t>& a, int count) {
    constexpr uint64_t lvl1P = 1073707009;
    //constexpr uint64_t lvl1P = 1073741783;
    //constexpr uint64_t lvl1P = 1073741789;
    static constexpr std::uint32_t nbit = 10;
    static constexpr std::uint32_t n = 1 << nbit;  // dimension
    std::cout << "Bit shift testing " << count << " Input: " << std::endl;
    std::cout << std::dec;
    int i;
    for (i = 0; i < count; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::hex;
    std::cout  << "Input in HEX: " << std::endl;
    for (i = 0; i < count; i++) {
        std::cout << std::hex << a[i] << " ";
    }
    std::cout << std::endl << std::endl;

    std::array<uint64_t, n> temp{};
    for (i = 0; i <n; i++)
            temp[i] = (lvl1P * static_cast<uint64_t>(a[i])) >> 32;


    std::cout << "After (lvl1P * static_cast<uint64_t>(a[i])) >> 32:" << std::endl;
    std::cout << std::dec;
    for (i = 0; i < count; i++) {
        std::cout << temp[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "After (lvl1P * static_cast<uint64_t>(a[i])) >> 32: in HEX:" << std::endl;
    std::cout << std::hex;
    for (i = 0; i < count; i++) {
        std::cout << temp[i] << " ";
    }
    std::cout << std::endl;

    std::array<uint64_t, n> res{};

    std::cout << std::endl;

    for (i = 0; i < n; i++) res[i] = (temp[i] << 32) / lvl1P;

    std::cout << "Result after (temp[i] << 32) / lvl1P: " << std::endl;
    std::cout << std::dec;
    for (i = 0; i < count; i++) {
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;


    std::cout << "Result after (temp[i] << 32) / lvl1P in HEX:" << std::endl;
    std::cout << std::hex;
    for (i = 0; i < count; i++) {
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;
}



int main(int argc, char *argv[]) {
    uint32_t num_print = TFHEpp::lvl1param::n;
    int test_case = -1;
    std::vector<uint32_t> data;


    printf("Example: ./twist_ntt 5 0  ./twist_ntt 5 1   ./twist_ntt 5 2\n");
    printf("Program name: %s: argc: %d ", argv[0], argc);

    if(argc > 1) {
        for(int i = 1; i < argc; i++) {
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

    TFHEpp::Polynomial<TFHEpp::lvl1param> a, res0, res1, res2;
    int j =0;
    for (typename TFHEpp::lvl1param::T &i : a) {
        i = data[j];
        j++;
    }
    std::array<cuHEpp::INTorus, TFHEpp::lvl1param::n> resntt, resntt1, resntt2;

    if( test_case == 0) {
        std::cout << std::endl << "\nStart HEXL test" << std::endl;
        TFHEpp::TwistINTT_lvl1param_test<TFHEpp::lvl1param>(resntt, a, 0, num_print);
        TFHEpp::TwistNTT_lvl1param_test<TFHEpp::lvl1param>(res0, resntt, 0, num_print);
    }
    if (test_case == 1) {
        std::cout << std::endl << "\nStart HEXL test without bit shifting" << std::endl;
        TFHEpp::TwistINTT_lvl1param_test<TFHEpp::lvl1param>(resntt, a, 1, num_print);
        TFHEpp::TwistNTT_lvl1param_test<TFHEpp::lvl1param>(res0, resntt, 1, num_print);
    }
    if (test_case == 2) {
        std::cout << std::endl << "\nStart test without HEXL" << std::endl;
        TFHEpp::TwistINTT_lvl1param_test<TFHEpp::lvl1param>(resntt, a, 2, num_print);
        TFHEpp::TwistNTT_lvl1param_test<TFHEpp::lvl1param>(res0, resntt, 2, num_print);
    }
    if(test_case == 3) {
        storeInFile();
    }
    if(test_case == 4) {
        readFromFile(data, true);
    }

    if (test_case == 5) {
        applyBitShifting(data, num_print);
    }


    //for (int i = 0; i < TFHEpp::lvl1param::n; i++) _assert(a[i] == res[i]);

    //std::cout << "NTT Passed" << std::endl;



    return 0;
}
