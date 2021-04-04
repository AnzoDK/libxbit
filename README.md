# LibXbit
## The C++ version of BigInteger from Java

This lib aims to implement most of the features of the BigInteger from Java.

## Building
1. Download the repo or clone it with:
`git clone https://github.com/AnzoDK/libxbit`
2. Enter the directory
3. Build the `.so (lib)` with:
`make buildLib`
or make the testprogram with:
`make`
4. Move the created ´.so´ file into either the root folder of your project or into `/usr/lib/xbit/`
5. Move the `xBitLib.h` into either the root folder of your project or into `/usr/include/xbit/`
6. Link your program to the lib with `-lxbit`
7. Profit

