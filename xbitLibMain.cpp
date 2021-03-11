/*
 * Created by AnzoDK (anton@rosenoern-productions.dk)
 * Read LICENCE for info on modification and redistrobution
*/
#include "xbitLib.h"


//Contructors
xBitInt::xBitInt()
{
    Init(0);
}
xBitInt::xBitInt(const xBitInt& xBit)
{
    m_length = xBit.m_length;
    m_buffer = new byte[m_length];
    for(uint64_t i = 0; i < m_length;i++)
    {
        m_buffer[i] = xBit.m_buffer[i];
    }
}
xBitInt::xBitInt(int initialValue)
{
    Init(initialValue);
}

//Functions
template <typename T>
void xBitInt::Init(T initialValue)
{
    m_cpuSize = sizeof(size_t);
    int size = sizeof(initialValue);
    m_buffer = new byte[size];
    m_length = size;
    if(!BufferWrite(0,size,(byte*)&initialValue)) //This would actually never be true - But sets a standard, that all calls to BufferWrite should be checked
    {
        throw ExpectedOverflowException("Internal Write Attempts to write out of bounds");
    }
}
bool xBitInt::BufferWrite(uint64_t offset, uint64_t bytesToWrite, byte* buffer) //Assume buffer is little-endian
{
    if(bytesToWrite+offset > m_length)
    {
        return 0;
    }
    for(uint64_t i = 0; i < bytesToWrite; i++)
    {
        m_buffer[offset+i] = buffer[bytesToWrite-i-1];
        std::cout << "Wrote '" << std::to_string(buffer[bytesToWrite-i-1]) << "' to index: " << std::to_string(offset+i) << std::endl;
    }
    return 1;
}
void xBitInt::m_Resize(int64_t change)
{
    if(change < 0)
    {
        if((int64_t)sqrt((change*change)) > m_length)
        {
            //Invalid Resize;
            return;
        }
    }
    
    byte* tmpB = new byte[m_length+change];
    for(uint64_t i = 0; i < m_length;i++)
    {
        if(i == m_length+change-1)
        {
            break;
        }
        tmpB[i] = m_buffer[i];
    }
    m_length+=change;
    delete[] m_buffer;
    m_buffer = tmpB;
}
std::string xBitInt::ToString()
{
    std::string out = "";
    for(uint64_t i = 0; i < m_length;i+=m_cpuSize)
    {
        size_t tmp = 0;
        for(uint64_t u = 0; u < m_cpuSize; u++)
        {
            if((i*m_cpuSize)+u >= m_length)
            {
                break;
            }
            //tmp = (tmp | m_buffer[((i*m_cpuSize)+m_cpuSize)-u]) << (u == m_cpuSize-1 ? 0: 8);
            ((byte*)&tmp)[u] = m_buffer[(i*m_cpuSize)+(m_cpuSize > m_length ? m_length : m_cpuSize)-1-u];
            //std::cout << "tmp Index: " << std::to_string(u) << " -> bufferIndex: " << std::to_string((i*m_cpuSize)+(m_cpuSize > m_length ? m_length : m_cpuSize)-1-u) << std::endl;

        }
        out+=std::to_string(tmp);
    }
    return out;
}
//Debug functions
std::string xBitInt::GetDebugInfo()
{
    std::string out = "";
    out+= "DEBUG:\n";
    out+= "CPU_SIZE: " + std::to_string(m_cpuSize) + std::string(" Bytes / ") + std::to_string(m_cpuSize*8) + std::string(" bits") + std::string("\n");
    out+= "Represents: " + ToString() + std::string("\n"); 
    out+= "Internal Buffer (size: " + std::to_string(m_length) + std::string(") ") + std::string("{\n");
    for(uint64_t i = 0; i < m_length; i++)
    {
        out+= std::string("[") + std::to_string(i) + std::string("]: ") + std::to_string(m_buffer[i]);
        if(i != m_length-1)
        {
            out+=",";
        }
        out+="\n";
    }
    out+= std::string("}\n");
    return out;
}

//Operators
xBitInt xBitInt::operator*(const xBitInt mul)
{
    for(int i = 0; i < 0; i++)
    {

    }
}
xBitInt xBitInt::operator*(int mul)
{
    size_t cpu_max = (sizeof(size_t) == 8 ? 0xFFFFFFFFFFFFFFFF : 0xFFFFFFFF); //Use of size_t is meant to not be slower on 32bit systems I guess
    //Let's just check for a shortcut
    if(mul == 2)
    {
        m_Resize(1);
        bool leftBit = 0;
        for(uint64_t i = 0; i < m_length;i++)
        {
            if(i == m_length-1)
            {
                m_buffer[i] = (leftBit ? 0b00000001 : 0);
                break;
            }
            if(leftBit)
            {
                leftBit = (m_buffer[i] & 0b10000000);
                m_buffer[i] = m_buffer[i] << 1;
                m_buffer[i] = m_buffer[i] | 0b00000001;
            }
            else
            {
                leftBit = (m_buffer[i] & 0b10000000);
                m_buffer[i] = m_buffer[i] << 1;
            }
            
        }
        return *this;
    }
    for(size_t i = 0; i < cpu_max;i++)
    {

    }
    return *this;
}