# Tutorial

This directory contains the tutorial codes which demostrate how to use TFHEpp to resolve 2-party [Yao's Millionaires' problem](https://en.wikipedia.org/wiki/Yao%27s_Millionaires%27_problem). This is one of the simplest and most famous Secure Function Evaluation problem.

# How to build
When building TFHEpp, give `-DENABLE_TEST_NTT=ON` option to cmake.
mkdir build
cd build
cmake .. -DENABLE_TEST_NTT=ON
cmake .. -DENABLE_TEST_NTT=ON -DUSE_HEXL=on

# How to run
./test_ntt/encryptDecryptOne
