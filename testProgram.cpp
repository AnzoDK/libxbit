#include "xbitLib.h"
#include <iostream>
#include <chrono>
int main()
{
    long out = 5000;
    long in = 400000;
    auto start = std::chrono::high_resolution_clock::now();
    xBitInt xBit = xBitInt(in);
    std::cout << xBit.ToString() << std::endl;
    std::cout << xBit.GetDebugInfo() << std::endl;
    //xBit = xBit << out;

    //xBit = xBit*2;
    //xBit+=xBitInt(out);
    //xBit = xBit + xBitInt((int)490000);
    uint64_t* xBit_address = (uint64_t*)&xBit;
    xBit = xBit*xBitInt(out);
    std::cout << xBit.ToString() << std::endl;
    std::cout << xBit.GetDebugInfo() << std::endl;
    std::string s = "";
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Execution of " << in << "*" << std::to_string(out) <<  " took " << duration.count() << " microseconds or " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " milliseconds" << std::endl;
    //std::getline(std::cin,s);
    return 0;
}