#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
typedef unsigned char uchar;
typedef unsigned char byte;
#ifdef WIN32
typedef unsigned int uint;
#endif
class xBitInt
{
public:
    xBitInt();
    //xBitInt(int initialValue);
    xBitInt(long initialValue);
    xBitInt(byte* byteArr, uint64_t byteArrLen);
    xBitInt(const xBitInt &xBit);
    xBitInt(const std::string &strNr); //This is so fucking cursed - please, this is something stupid enough to be reserved for Java
    ~xBitInt()
    {
        delete[] m_buffer;
    }
    xBitInt& operator= (xBitInt const& xBit);
    xBitInt operator* (const xBitInt &mul);
    xBitInt operator* (int mul);
    xBitInt operator*= (xBitInt &mulX);
    xBitInt operator+ (const xBitInt &add);
    xBitInt operator+= (const xBitInt &add);
    xBitInt operator- (const xBitInt &sub);
    xBitInt operator-= (const xBitInt &sub);
    xBitInt operator-- (int sub);
    xBitInt operator>> (int lsr);
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    xBitInt operator<< (T lsl);

    std::string ToString();

    uchar ReadAt(uint64_t index){return m_buffer[index];}
    uint64_t GetLength(){return m_length;}
    uint64_t GetBitLength(){return m_length*8;}
    std::string GetDebugInfo();

private:
    template<typename T>
    void Init(T initialValue);
    bool BufferWrite(uint64_t offset, uint64_t bytesToWrite, uchar* buffer, bool allowResize=false);
    std::string m_UcharToHex(uchar u);
    void m_Resize(int64_t change);
    uchar* m_buffer;
    uint64_t m_length = 0;
    int m_cpuSize = 0;
};

class ExpectedOverflowException : public std::exception
{
public:
    ExpectedOverflowException(const std::string &errorMsg) noexcept
    {
        m_errorMsg = errorMsg;
    }
    virtual const char* what() const noexcept override
    {
        return m_errorMsg.c_str();
    }
private:
    std::string m_errorMsg = "";
};

class xBitFloating
{
public:
    xBitFloating(){}
};