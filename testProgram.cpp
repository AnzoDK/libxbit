#include "xbitLib.h"
#include <iostream>
int main()
{
    xBitInt xBit = xBitInt((long)400000);
    std::cout << xBit.ToString() << std::endl;
    //xBit = xBit*2;
    //xBit+=xBitInt((int)2500);
    xBit = xBit + xBitInt((int)490000);
    std::cout << xBit.ToString() << std::endl;
    std::cout << xBit.GetDebugInfo() << std::endl;
    std::string s = "";
    std::getline(std::cin,s);
    return 0;
}