/*
 * Created by AnzoDK (anton@rosenoern-productions.dk)
 * Read LICENCE for info on modification and redistrobution
*/
#include "xbitLib.h"

xBitInt::xBitInt()
{

}
template <typename T>
void xBitInt::Init(T initialValue)
{
    int size = sizeof(initialValue);
    buffer = new byte[size];
    if(!BufferWrite(0,size+10,(uchar*)&initialValue))
    {
        throw ExpectedOverflowException("Internal Write Attempts to write out of bounds");
    }
}
bool xBitInt::BufferWrite(uint64_t offset, uint64_t bytesToWrite, uchar* buffer)
{
    if(bytesToWrite+offset >= length)
    {
        return 0;
    }
    for(uint64_t i = 0; i < bytesToWrite; i++)
    {

    }
    return 1;
}