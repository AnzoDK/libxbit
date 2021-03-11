#include "xbitLib.h"
#include <iostream>
int main()
{
    xBitInt xBit = xBitInt((int)2);
    std::cout << xBit.ToString() << std::endl;
    //xBit = xBit*2; Locks up
    //std::cout << xBit.ToString() << std::endl;
    std::cout << xBit.GetDebugInfo() << std::endl;
    return 0;
}