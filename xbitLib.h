#pragma once
#include <iostream>
typedef unsigned char uchar;
typedef unsigned char byte;
class xBitInt
{
public:
    xBitInt();
    xBitInt(int initialValue);
    xBitInt(long long initialValue);
private:
    template<typename T>
    void Init(T initialValue);
    bool BufferWrite(uint64_t offset, uint64_t bytesToWrite, uchar* buffer);
    uchar* buffer;
    uint64_t length;
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