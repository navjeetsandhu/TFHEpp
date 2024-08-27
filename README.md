[![Test](https://github.com/virtualsecureplatform/TFHEpp/actions/workflows/test.yml/badge.svg)](https://github.com/virtualsecureplatform/TFHEpp/actions/workflows/test.yml)
# TFHEpp
TFHEpp is full Scracthed pure C++ Ver. of TFHE. TFHEpp is slightly(about 10%) faster than original [TFHE implementation](https://github.com/tfhe/tfhe). In addition to that, THFEpp supports Circuit Bootstrapping and [Private Boootstrapping many LUT](https://eprint.iacr.org/2021/729).
TFHEpp depends on AVX2 because we use SPQLIOS FMA. If you want run TFHEpp without AVX2, see spqlios++ branch. It include pure C++ implementation of SPQLIOS as header only library, but slow.

# Supported Compiler

GCC9.1 later are primarily supported compilers.
The following features of C++20 are modified to compile using gcc-9.1.0

### UTF-8 Identifiers
In C++, it's possible to use UTF-8 identifiers to name variables, functions, classes, etc., in your code. For example, you could declare a variable like int α = 5. Using non-ASCII identifiers is not portable and may not be correctly handled by all compilers.

### make_unique_for_overwrite
make_unique_for_overwrite is a function introduced in C++20. It is used to allocate dynamic memory for an object and initialize it. The main difference between make_unique and make_unique_for_overwrite is that the make_unique value initializes the created object, while make_unique_for_overwrite leaves the object in a partially formed, non-value-initialized state, which means the object's fields or elements are not initialized to a default value. This optimization is useful when we know that we will overwrite every field or element of a large object. It allows us to skip unnecessary initialization and save time when creating large objects or arrays.

### concept
The concept keyword is a feature introduced in C++20 that enables a form of compile-time polymorphism that's different from templates. It is a way to express template constraints more clearly than was possible in previous versions of C++. A concept represents a set of requirements (such as functions or operators that must be present in a type).

### span
In C++20, the span was introduced as a new kind of lightweight, non-owning reference to a sequence (array, part of an array, or range of a container) that provides easy access to individual elements or the sequence. The main idea behind span is to offer an approach that can be a safer alternative to traditional pairs of pointers and sizes for passed arrays and will work for all data types. Instead of wrestling with pointer arithmetic and worrying about out-of-bounds errors, developers can use span to automatically retain a sequence's size and access data in a range-checked way. It's a non-owning view over a contiguous sequence of items represented with a pointer to the first element and a size. It does not manage the lifetime of the memory it refers to.

### bits/stdint-uintn.h header file
The #include <bits/stdint-uintn.h> is a non-standard way to include definitions for integer types with a fixed width but isn't present on all platforms or with all compilers. This file is typically used internally by other standard libraries and is not meant to be included directly in the code.

# Parameter
The default parameter is 128-bit security. Please add -DUSE_80BIT_SECURITY=ON to use a faster but less secure parameter.

# FFTW3 Support
Some environments which do not support AVX2 cannot use spqlios. Instead of spqlios, TFHEpp can use fftw3.
To use fftw3,  install `libfftw3-dev` and add `-DUSE_FFTW3=ON` to the compile option.

# Third party libraries
Codes under thirdparties directory contain third-party libraries, Randen, Cereal, and SPQLIOS. See the corresponding directory to check the licenses.

## Randen
TFHEpp uses this as a Cryptographically Secure Pseudo-Random Number Generator (CSPRNG). Original repository is [here](https://github.com/google/randen).
I just removed some unnecessary codes, with no modification.

## Cereal
cereal is a header-only C++11 serialization library. TFHEpp uses this to export ciphertexts and keys. Cereal is treated by the git submodule.

## SPQLIOS
SPQLIOS is the FFT library using AVX2 that is dedicated to the ring R\[X\]/(X^N+1) for N a power of 2. These codes come from [experimental-tfhe](https://github.com/tfhe/experimental-tfhe/tree/master/circuit-bootstrapping/src/spqlios). We just renamed instances to adapt to our codes.

## SPQLIOS-AVX512
This is the AVX512 version of SPQLIOS developed in [MOSFHET](https://github.com/antoniocgj/MOSFHET). I confirmed that this is faster than SPQLIOS on Intel i5-11400.

## FFTW3
[FFTW](https://www.fftw.org/) is one of the most famous FFT libraries. 

**CAUTION**: REDISTRIBUTING BINARY WHICH DEPENDS ON FFTW3 MEANS YOU AGREED WITH GPLv3 OR LATER.

## MKL
Intel MKL is the library provided by Intel and including FFTW compatible interface for FFT.
We assume to install MKL by [this procedure](https://www.intel.com/content/www/us/en/developer/articles/guide/installing-free-libraries-and-python-apt-repo.html) and already ran `source /opt/intel/mkl/bin/mklvars.sh`.

Add `-DUSE_MKL` to the CMake option to use MKL

### FFTW3 API
To use this, you have to also add `-DUSE_FFTW3`.

### Native API
Instead of FFTW3 API, I also added native API version. This will be enabled if `-DUSE_FFTW3` is not specified with `-DUSE_MKL`.

## concrete-fft
concrete-fft is the pure rust FFT library developed by Zama.ai. This can be enabled by `-DUSE_CONCRETE_FFT`.

## spqliox_aarch64
spqliox_aarch64 is the FFT library for aarch64 forked from SPQLIOS.
This is slightly faster than FFTW3(average 1ms).
This library requires [xbyak_aarch64](https://github.com/fujitsu/xbyak_aarch64), and
to use this library, add `-DUSE_SPQLIOX_AARCH64=on` to the CMake option.

<center>

| FFTW3    | spqliox_aarch64 |
| :------: | :-------------: |
| 15.801ms | 14.368ms        |

</center>

## HEXL

[HEXL](https://github.com/intel/hexl.git) is the NTT library optimized for AVX512. 
To use this library, add `-DUSE_HEXL=on` to the CMake option.

TFHEpp uses the following HEXL limited functionalities in certain scenarios:
1.	Forward NTT: ComputeForward()
2.	Inverse NTT: ComputeInverse()
3.	Elementwise vector multiplication with modular reduction: EltwiseMultMod()
4.	Elementwise vector addition with modular reduction: EltwiseAddMod()
 

# Speed Test

Following Code measure how many time homomorphic NAND takes on your computer with TFHEpp. 
```
git clonehttps://github.com/navjeetsandhu/TFHEpp.git
cd TFHEpp
mkdir build
cd build
cmake .. -DENABLE_TEST=ON
make
ulimit -s unlimited
./test/nand 
```

If you want to run semantically equivalent test on original TFHE, run below code.
```
git clone https://github.com/tfhe/tfhe.git --recursive
cd tfhe
mkdir build
cd build
cmake ../src -DENABLE_TESTS=on -DENABLE_NAYUKI_PORTABLE=off -DENABLE_NAYUKI_AVX=off -DENABLE_SPQLIOS_AVX=off -DENABLE_SPQLIOS_FMA=on -DCMAKE_BUILD_TYPE=optim
make
./test/test-gate-bootstrapping-spqlios-fma
```

If you have Docker on your system, this will do above on docker.

```
git clone https://github.com/virtualsecureplatform/TFHEpp
cd TFHEpp
docker build -t tfheppbench .
```

This is for TFHE-10ms. Because TFHE-10ms only supports 80-bit security parameter, this is not included in Dockerfile
```
git clone https://github.com/virtualsecureplatform/tfhe-10ms.git --recursive
cd tfhe-10ms
mkdir build
cd build
cmake ../src -DENABLE_TESTS=on -DENABLE_NAYUKI_PORTABLE=off -DENABLE_NAYUKI_AVX=off -DENABLE_SPQLIOS_AVX=off -DENABLE_SPQLIOS_FMA=on -DCMAKE_BUILD_TYPE=optim
make
./test/test-bootstrapping-fft-spqlios-fma 
```

# Theory

Here is the slides (in japanese).
https://nindanaoto.github.io/

# Citation

For the people who want to cite this library directly (may be in addition to [VSP paper](https://www.usenix.org/conference/usenixsecurity21/presentation/matsuoka)), I give a below example of bibtex citation.

```
@misc{TFHEpp,
	author = {Kotaro Matsuoka},
	title = {{TFHEpp: pure C++ implementation of TFHE cryptosystem}},
  	year = {2020},
	howpublished = {\url{https://github.com/virtualsecureplatform/TFHEpp}}
}
```
