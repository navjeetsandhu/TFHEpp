[![Test](https://github.com/virtualsecureplatform/TFHEpp/actions/workflows/test.yml/badge.svg)](https://github.com/virtualsecureplatform/TFHEpp/actions/workflows/test.yml)
# TFHEpp
TFHEpp is full Scracthed pure C++ Ver. of TFHE. TFHEpp is slightly(about 10%) faster than original [TFHE implementation](https://github.com/tfhe/tfhe). In addition to that, THFEpp supports Circuit Bootstrapping and [Private Boootstrapping many LUT](https://eprint.iacr.org/2021/729).
TFHEpp depends on AVX2 because we use SPQLIOS FMA. If you want run TFHEpp without AVX2, see spqlios++ branch. It include pure C++ implementation of SPQLIOS as header only library, but slow.

# Supported Compiler

GCC9.1 later are primarily supported compilers. 

The following are code changes at TFHEpp to compile using gcc-9.1.0

UTF-8 Identifiers
In C++, it's possible to use UTF-8 identifiers to name variables, functions, classes, etc., in your code. For example, you could declare a variable like int α = 5. Using non-ASCII identifiers is not portable and may not be correctly handled by all compilers.
So, the following non-ASCII identifiers were replaced

1.	μ with mu
2.	α with alpha
3.	Δ with delta
4.	η with eta
5.	ā with aLong
6.	b̄ with bLong

### make_unique_for_overwrite
make_unique_for_overwrite is a function introduced in C++20. It is used to allocate dynamic memory for an object and initialize it. The main difference between make_unique and make_unique_for_overwrite is that the make_unique value initializes the created object, while make_unique_for_overwrite leaves the object in a partially formed, non-value-initialized state, which means the object's fields or elements are not initialized to a default value. This optimization is useful when we know that we will overwrite every field or element of a large object. It allows us to skip unnecessary initialization and save time when creating large objects or arrays.

GCC 9.1 compiler doesn't support make_unique_for_overwrite so I used
make_unique instead. However, this will value-initialize the object which won't be as efficient.



### concept
The concept keyword is a feature introduced in C++20 that enables a form of compile-time polymorphism that's different from templates. It is a way to express template constraints more clearly than was possible in previous versions of C++. A concept represents a set of requirements (such as functions or operators that must be present in a type).
Here is a basic example:

template<typename T>
concept Printable = requires(T a) {
{ std::cout << a };
};

void print(Printable auto const& value) {
std::cout << value << std::endl;
}


In this example, Printable is a concept that checks whether a type can be printed to cout. The print function is a constrained template that accepts any type that satisfies the Printable concept. If you try to call print with a type that isn't printable, you'll get a compile-time error. Concepts help to improve code safety and readability and provide better compile-time error messages. They also enable better tooling support and can make the code completion, refactoring, and static analysis more accurate.

Before the introduction of the concept keyword in C++20, similar functionality could be achieved using SFINAE (Substitution Failure Is Not an Error) techniques in C++17. Here's how you could rewrite the Printable concept from the example above using C++17:

By using SFINAE with std::enable_if:
template<typename T>
std::enable_if_t<std::is_convertible_v<T, std::string>, void> print(const T& value) {
std::cout << value << std::endl;
}
This method creates a function template that is only considered by the compiler if the T is convertible to string. If not, the function template is removed from the set of overloads, and if no other viable functions are available, a compiler error occurs.
It should be noted that these approaches are not as powerful or as flexible as C++20 concepts. They also might not provide as clear and readable error messages when a type doesn't meet the requirements.

I have replaced concept with SFINAE to compile using GCC 9.1 compiler.

### span
In C++20, the span was introduced as a new kind of lightweight, non-owning reference to a sequence (array, part of an array, or range of a container) that provides easy access to individual elements or the sequence. The main idea behind span is to offer an approach that can be a safer alternative to traditional pairs of pointers and sizes for passed arrays and will work for all data types. Instead of wrestling with pointer arithmetic and worrying about out-of-bounds errors, developers can use span to automatically retain a sequence's size and access data in a range-checked way. It's a non-owning view over a contiguous sequence of items represented with a pointer to the first element and a size. It does not manage the lifetime of the memory it refers to.
I have commented out all the code which was using span as I noticed that the functionality is not used at all.


### bits/stdint-uintn.h header file
The #include <bits/stdint-uintn.h> is a non-standard way to include definitions for integer types with a fixed width but isn't present on all platforms or with all compilers. This file is typically used internally by other standard libraries and is not meant to be included directly in the code.

The <cstdint> is a header file in C++ that provides a set of typedefs that specify exact-width integer types. You will have access to new data types when you include this header. These types are not original data types but typedefs for signed and unsigned integer types of different widths. Here are some of the types defined in <cstdint>:
int8_t, int16_t, int32_t, int64_t: These are signed integers with a width of precisely 8, 16, 32, or 64 bits. uint8_t, uint16_t, uint32_t, uint64_t: These are unsigned integers (i.e., non-negative integers) with a width of 8, 16, 32, or 64 bits.

I have replaced <bits/stdint-uintn.h> with <cstdint> header file.



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

TFHEpp uses the following HEXL functionalities:
1.	Forward NTT: ComputeForward()
2.	Inverse NTT: ComputeInverse()
3.	Elementwise vector multiplication with modular reduction: EltwiseMultMod()
4.	Elementwise vector addition with modular reduction: EltwiseAddMod()
      
### Forward NTT
The Number Theoretic Transform (NTT) is an alternative to the Fast Fourier Transform (FFT), which operates in the ring of integers modulo a number n instead of complex numbers. Its advantage is that all computations have integers, which is more suitable than FFT for many algebraic computation applications.
The forward NTT computes the NTT of a vector, effectively transforming the sequence from the time domain to the frequency domain.

### Inverse NTT
The Inverse Number Theoretic Transform (Inverse NTT) is used to revert the Number Theoretic Transform (NTT). The NTT is a specialized form of the Discrete Fourier Transform (DFT) that operates in rings of integers modulo some prime. It's used in areas dealing with large integer multiplications and polynomial multiplications.
NTT decomposes an overall polynomial into many smaller polynomials so that computations could be done more efficiently. After the operations on these smaller polynomials, the Inverse NTT converts these polynomials back to a combined form.

### Elementwise vector multiplication with modular reduction
Modular multiplication is an arithmetic operation in modular arithmetic, a system for integers where numbers wrap around after reaching a specific value. The multiplication process is the same as in ordinary arithmetic. Still, the result is 'taken modulo' a particular number, meaning that the remainder when the result is divided by that number is what's returned. Here's a general formula for modular multiplication:
(a * b) mod n
Where: a and b are the numbers being multiplied. n is the modulus.
If a = 10, b = 20 and n =5, then (10 * 20) mod 5 equals 0, because 200 divided by 5 has no remainder.
Modular reduction is the operation of finding the remainder of a division operation. Regarding modular arithmetic, reduction converts a number into its equivalent value within the modulo range.
For example, for a given integer a and a positive integer n, the modular reduction of a (mod n) is the remainder r when a is divided by n, where r lies in the range from 0 to n-1.
For instance, if a = 27 and n = 5, then 27 (mod 5) equals 2 because when 27 is divided by 5, the remainder is 2.
In multiplication, the term elementwise refers to performing the multiplication operation on each corresponding pair of elements from the two vectors.
For instance, if you have two vectors:
vec1 = [1, 2, 3] and vec2 = [4, 5, 6]
Multiplying them elementwise would result in a new vector where each element is the product of elements in the same position in the original vectors:
result = [1*4, 2*5, 3*6] = [4, 10, 18]
Now, let's look at the second part - modular reduction. The modulus operation finds the remainder after dividing one number by another (called the modulus of the operation). Each multiplication result is then reduced by locating the remainder of the division by a given modulus.
If the mod is the modulus, then the operation looks like this:
result_mod = [(1*4) mod mod, (2*5) mod mod, (3*6) mod mod]
For example, if mod = 7, then result_mod = [(1*4) mod 7, (2*5) mod 7, (3*6) mod 7] = [4 mod 7, 10 mod 7, 18 mod 7] = [4, 3, 4]
This vector result_mod is the itemwise product of vec1 and vec2 reduced by mod.
Montgomery's method is the most popular algorithm for modular multiplication. Montgomery's approach avoids the time-consuming trial division, which is the bottleneck. The idea behind Montgomery multiplication is to perform a non-standard representation of numbers to simplify the process of modular reduction. Here's a basic outline of the Montgomery multiplication algorithm:
You are given three integers A, B and N with N odd. The Montgomery product of A and B concerning N is computed as A * B * R^-1 (mod N), where R is a base b power greater than mod N and R^-1 is the multiplicative inverse of R modulo N.
For efficient implementation of modular multiplication, the crucial operation is modular reduction. The algorithm that is used for this purpose is Barrett reduction. Barrett Reduction is an algorithm used to compute A mod N where A is large (typically a product of some other calculations), and N is a fixed modulus. It uses multiplication and shifts instead of the traditional slow division approach. The actual speed comes from the fact that the most laborious computing needed to perform the Barrett reduction can be precalculated if the modulus N is known in advance.

### Elementwise vector addition with modular reduction
When you do an element-wise addition of two vectors with modular reduction, you perform this modulus operation on the sum of the corresponding elements. If the mod is the modulus, then the operation is as follows:
result_mod = [(1+4) mod mod, (2+5) mod mod, (3+6) mod mod]
For example, if mod = 7, then result mod = [(1+4) mod 7, (2+5) mod 7, (3+6) mod 7] = [5 mod 7, 7 mod 7, 9 mod 7] = [5, 0, 2]



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
