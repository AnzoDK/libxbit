#include "xbitLib.h"
#include <iostream>
int main()
{
    xBitInt xBit = xBitInt((long)4294967296);
    std::cout << xBit.ToString() << std::endl;
    //xBit = xBit*2;
    //xBit+=xBitInt((int)2500);
    xBit = xBit + xBitInt((int)256);
    std::cout << xBit.ToString() << std::endl;
    std::cout << xBit.GetDebugInfo() << std::endl;
    return 0;
}