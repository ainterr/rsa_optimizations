###RSA Optimizations
This project comprises a number of different RSA optimizations along with an RSA key generator.

####Requirements
* [g++](https://gcc.gnu.org/onlinedocs/gcc-3.3.6/gcc/G_002b_002b-and-GCC.html) - The GNU C++ Compiler
* [gmplib](https://gmplib.org/) - The GNU Multiple Precision library allows arbitrary length key exponents to be used.

####Optimizations
* Fast Modular Exponentiation - For an explanation of this optimization, see [here](https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/fast-modular-exponentiation). To compile with this optimization, run `make fme`.
* Chinese Remainder Theorem - Coming Very Soon
* Montgomery Multiplication - Coming Soon

####Running The Code
Compiling will generate an `rsa` binary.
* To generate new keys, run `rsa keygen`.
* To run an encryption/decryption run `rsa mod [message] [exponent] [modulus] [first_prime] [second_prime]`.
* You can specify constant exponent, modulus, p, and q values by defining them in `rsa.cpp`. An example 4096 bit private key is included.
