#pragma once
#include <iostream>
#include <math.h>
typedef unsigned char uchar;
typedef unsigned char byte;
#ifdef WIN32
typedef unsigned int uint;
#endif
class xBitInt
{
public:
    xBitInt();
    xBitInt(int initialValue);
    xBitInt(long initialValue);
    xBitInt(const xBitInt &xBit);
    ~xBitInt()
    {
        //delete[] m_buffer;
    }
    xBitInt operator* (const xBitInt mul);
    xBitInt operator* (int mul);
    xBitInt operator+ (xBitInt add);
    xBitInt operator+= (xBitInt add);
    std::string ToString();
    uchar ReadAt(uint64_t index){return m_buffer[index];}
    uint64_t GetLength(){return m_length;}
    std::string GetDebugInfo();

private:
    template<typename T>
    void Init(T initialValue);
    bool BufferWrite(uint64_t offset, uint64_t bytesToWrite, uchar* buffer);
    void m_Resize(int64_t change);
    uchar* m_buffer;
    uint64_t m_length;
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