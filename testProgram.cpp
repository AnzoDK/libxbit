#include "xbitLib.h"
#include <iostream>
#include <chrono>
int main()
{
    long out = 11313131300;
    long in = 40131313000;
    auto start = std::chrono::high_resolution_clock::now();
    xBitInt xBit = xBitInt(in);
    xBitInt xOut = xBitInt(out);

    std::cout << xBit.ToString() << std::endl;
    std::cout << xBit.GetDebugInfo() << std::endl;

    std::cout << xOut.ToString() << std::endl;
    std::cout << xOut.GetDebugInfo() << std::endl;

    //xBit = (xBit << static_cast<uint64_t>(out));
    
    //xBit = xBit*2;
    //xBit+=xBitInt(out);
    //xBit = xBit + xBitInt((int)490000);
    //xBit = xBit << static_cast<uint64_t>(2);
    //xBit*=xOut;
    std::cout << (xOut > xBit) << std::endl;
    //xBit = xBit * xBitInt(100);

    std::cout << xBit.ToString() << std::endl;
    std::cout << xBit.GetDebugInfo() << std::endl;

    std::string s = "";
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Execution of " << in << "*" << std::to_string(out) <<  " took " << duration.count() << " microseconds or " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " milliseconds" << std::endl;
    //std::getline(std::cin,s);
    return 0;
}