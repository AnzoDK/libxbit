/*
 * Created by AnzoDK (anton@rosenoern-productions.dk)
 * Read LICENCE for info on modification and redistrobution
*/
#include "xbitLib.h"


//Contructors
xBitInt::xBitInt()
{
    m_buffer = 0x0;
    Init(0);
}
xBitInt::xBitInt(const xBitInt& xBit)
{
    m_length = xBit.m_length;
    m_cpuSize = xBit.m_cpuSize;
    m_buffer = new byte[m_length];
    for(uint64_t i = 0; i < m_length;i++)
    {
        m_buffer[i] = xBit.m_buffer[i];
    }
}
xBitInt::xBitInt(byte* byteArr, uint64_t byteArrLen)
{
    m_length = byteArrLen;
    Init(0);
    if(!BufferWrite(0,byteArrLen,byteArr,1))
    {
        throw ExpectedOverflowException("Internal Write Attempts to write out of bounds");
    }
}
/*xBitInt::xBitInt(int initialValue)
{
    Init(initialValue);
}*/
xBitInt::xBitInt(long initialValue)
{
    m_buffer = 0x0;
    Init(initialValue);
}
xBitInt::xBitInt(const std::string &strNr) //WHY AM I CODING THIS AGAIN?????
{
    m_buffer = 0x0;
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
bool xBitInt::BufferWrite(uint64_t offset, uint64_t bytesToWrite, byte* buffer, bool allowResize) //Assume buffer is little-endian
{
    if(bytesToWrite+offset > m_length)
    {
        if(allowResize)
        {
            m_Resize(bytesToWrite+offset);
        }
        else
        {
            return 0;
        }
        
    }
    for(uint64_t i = 0; i < bytesToWrite; i++)
    {
        m_buffer[offset+i] = buffer[/*bytesToWrite-i-1*/i];
        //std::cout << "Wrote '" << std::to_string(buffer[i/*bytesToWrite-i-1*/]) << "' to index: " << std::to_string(offset+i) << std::endl;
    }
    return 1;
}
void xBitInt::m_Resize(int64_t change)
{
    std::cout << "Resize from: " << std::to_string(m_length) << " to " << std::to_string(m_length+change) << std::endl;
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
std::string xBitInt::m_UcharToHex(uchar u)
{

    std::stringstream stream;
    stream << std::hex << (uint)u;
    std::string result(stream.str());
    return result;
}
std::string xBitInt::ToString()
{
    //TODO fix this (print a decimal string) //TEMP just calls ToHexString()
    return ToHexString();



    /*std::string out = "";
    for(uint64_t i = 0; i < m_length;i+=m_cpuSize)
    {
        size_t tmp = 0;
        for(uint64_t u = 0; u < static_cast<uint64_t>(m_cpuSize); u++)
        {
            if((i*m_cpuSize)+u >= m_length)
            {
                break;
            }
            //tmp = (tmp | m_buffer[((i*m_cpuSize)+m_cpuSize)-u]) << (u == m_cpuSize-1 ? 0: 8);
            ((byte*)&tmp)[u] = m_buffer[(i*m_cpuSize)+u];
            //std::cout << "tmp Index: " << std::to_string(u) << " -> bufferIndex: " << std::to_string((i*m_cpuSize)+(m_cpuSize > m_length ? m_length : m_cpuSize)-1-u) << std::endl;
            //std::cout << "tmp Index: " << std::to_string(u) << " -> bufferIndex: " << std::to_string((i*m_cpuSize)+u) << std::endl;

        }
        out+=std::to_string(tmp);
    }*/
    /*byte carry = 0;
    for(uint64_t i = 0; i < m_length;i++)
    {
        byte tmp = (m_buffer[i] & 0b00001111);
        if(tmp > 9)
        {
            tmp = tmp-10;
            carry = 1;
        }
        out = std::to_string(tmp) + out;
        byte tmp = (m_buffer[i] & 0b11110000);
        if(carry)
        {

        }
        else
        {

        }
    }*/
    //return out;
}
std::string xBitInt::ToHexString()
{
    std::string out = "0x";
    for(uint64_t i = 0; i < m_length; i++)
    {
        out += m_UcharToHex(m_buffer[i]);
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
        out += " (0x";
        out += m_UcharToHex(m_buffer[i]);
        out += ")";
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
xBitInt& xBitInt::operator=(xBitInt const& xBit)
{
    m_length = xBit.m_length;
    m_cpuSize = xBit.m_cpuSize;
    m_buffer = new byte[m_length];
    for(uint64_t i = 0; i < m_length;i++)
    {
        m_buffer[i] = xBit.m_buffer[i];
    }
    return *this;
}
xBitInt xBitInt::operator+(const xBitInt &xBitX)
{
    xBitInt tmpBit = xBitInt(*this);
    xBitInt xBit = xBitInt(xBitX);
    //uint64_t tmpLength = (xBit.m_length < this->m_length ? xBit.m_length : this->m_length);
    byte carry = 0;
    for(uint64_t i = 0; i < tmpBit.m_length;i++)
    {
        if(carry != 0 && i == tmpBit.m_length-1)
        {
            tmpBit.m_Resize(1);
        }
        uint64_t c = 0;
        while(carry != 0)
        {
            if((int)tmpBit.m_buffer[i+c]+carry > 255)
            {
                tmpBit.m_buffer[i+c]= 0x0;
                carry = ((int)tmpBit.m_buffer[i+c]+carry)-256;
            }
            else
            {
                tmpBit.m_buffer[i+c]+=carry;
                carry = 0;
            }
            c++;
        }
        uint t = tmpBit.m_buffer[i] + xBit.m_buffer[i];
        if(t > 255)
        {
            carry = 1;
            tmpBit.m_buffer[i] = t-256;
        }
        else
        {
            tmpBit.m_buffer[i]+=xBit.m_buffer[i];
        }

    }
    return tmpBit;
}
xBitInt xBitInt::operator-(const xBitInt &xBit)
{
    xBitInt tmpBit = xBitInt(*this);
    //uint64_t tmpLength = (xBit.m_length < this->m_length ? xBit.m_length : this->m_length);
    byte carry = 0;
    for(uint64_t i = 0; i < tmpBit.m_length ;i++)
    {
        if(carry != 0 && i == tmpBit.m_length-1)
        {
            carry = 0; //Unsigned so no negative numbers
            tmpBit = xBitInt(0);
        }
        uint64_t c = 0;
        while(carry != 0)
        {
            if((int)tmpBit.m_buffer[i+c]-carry < 0)
            {
                tmpBit.m_buffer[i-c]+=256-carry;
                carry = 1;
            }
            else
            {
                tmpBit.m_buffer[i+c]-=carry;
                carry = 0;
            }
            c++;
        }
        int t = static_cast<int>(tmpBit.m_buffer[i]) - static_cast<int>(xBit.m_buffer[i]);
        //std::cout << std::to_string(tmpBit.m_buffer[i]) << "-" << std::to_string(xBit.m_buffer[i]) << std::endl;
        if(t < 0)
        {
            carry = 1;
            tmpBit.m_buffer[i] = (uint)(tmpBit.m_buffer[i]+256) - xBit.m_buffer[i];
        }
        else
        {
            tmpBit.m_buffer[i]-=xBit.m_buffer[i];
        }

    }
    return tmpBit;
}
xBitInt xBitInt::operator-=(const xBitInt &xBit)
{
    *this = *this-xBit;
    return *this;
}
xBitInt xBitInt::operator--(int sub)
{
    if(sub == 0)
    {
        sub = 1;
    }
    *this = *this-xBitInt(sub);
    return *this;
}
xBitInt xBitInt::operator+=(const xBitInt &xBit)
{
    *this = *this + xBit;
    return *this;
}
template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
xBitInt xBitInt::operator<<(T lsl)
{
    xBitInt tmp = xBitInt(*this);
    uint64_t oldStart = tmp.m_length;
    byte carry = 0;
    tmp.m_Resize(ceil(lsl/8));
    if(lsl%8 == 0)
    {
        //Locate the first in-use byte
        uint64_t start = 0xFFFFFFFFFFFFFFFF;
        for(uint64_t i = 0; i < tmp.m_length; i++)
        {
            if(tmp.m_buffer[tmp.m_length-1-i] != 0)
            {
                start = tmp.m_length-1-i;
                break;
            }
        }
        if(start == 0xFFFFFFFFFFFFFFFF)
        {
            //I'm too scared to start doing processing on 0x0 giant int O_O
            return tmp;
        }
        for(uint64_t i = 0; i < start+1; i++)
        {
            tmp.m_buffer[start+static_cast<uint64_t>(lsl/8)-i] = tmp.m_buffer[start-i]; 
        }
        for(uint64_t i = 0; i < static_cast<uint64_t>(lsl/8); i++)
        {
            //tmp.m_buffer[start-static_cast<uint64_t>(lsl/8)+i] = 0x0;
            tmp.m_buffer[i] = 0x0;
        }
    }
    else if(lsl < 8)
    {
        byte nCarry = 0;
        byte comp = 0;
        for(int i = 0; i < lsl; i++)
        {
            comp = (comp << 1) | 1;
        }
        comp = comp << (8-lsl);
        for(uint64_t i = 0; i < tmp.m_length; i++)
        {
            if(carry)
            {
                if((tmp.m_buffer[i] & comp) != 0)
                {
                    nCarry = (tmp.m_buffer[i] & comp) >> (8-lsl);
                }
                tmp.m_buffer[i] = (tmp.m_buffer[i] << lsl) | carry;
                carry = nCarry;
                nCarry = 0;
            }
            else
            {
                if((tmp.m_buffer[i] & comp) != 0)
                {
                    carry = (tmp.m_buffer[i] & comp) >> (8-lsl);
                }
                tmp.m_buffer[i] = (tmp.m_buffer[i] << lsl);
            }
        }
        /*for(uint64_t i = 0; i < floor(lsl/8); i++)
        {
            tmp.m_buffer[i] = 0x0;
        }*/
    }
    else
    {

        byte comp = 0;
        for(int i = 0; i < lsl%8; i++)
        {
            comp = (comp << 1) | 1;
        }
        comp = comp << (8-(lsl%8));

        for(uint64_t i = 0; i < tmp.m_length; i++)
        {
            byte nCarry = 0;
            if(carry)
            {
                if((tmp.m_buffer[i] & comp) != 0)
                {
                    nCarry = (tmp.m_buffer[i] & comp) >> (8-(lsl%8));
                }
                tmp.m_buffer[i] = (tmp.m_buffer[i] << (lsl%8)) | carry;
                carry = nCarry;
                nCarry = 0;
            }
            else
            {
                if((tmp.m_buffer[i] & comp) != 0)
                {
                    carry = (tmp.m_buffer[i] & comp) >> (8-(lsl%8));
                }
                tmp.m_buffer[i] = (tmp.m_buffer[i] << (lsl%8));
            }
        }
        //Locate the first in-use byte
        uint64_t start = 0xFFFFFFFFFFFFFFFF;
        for(uint64_t i = 0; i < tmp.m_length; i++)
        {
            if(tmp.m_buffer[tmp.m_length-1-i] != 0)
            {
                start = tmp.m_length-1-i;
                break;
            }
        }
        if(start == 0xFFFFFFFFFFFFFFFF)
        {
            return tmp;
        }
        for(uint64_t i = 0; i < start+1; i++)
        {
            tmp.m_buffer[start+static_cast<uint64_t>(floor(lsl/8))-i] = tmp.m_buffer[start-i]; 
        }
        for(uint64_t i = 0; i < floor(lsl/8); i++)
        {
            tmp.m_buffer[i] = 0x0;
        }

    }
    return tmp;
    
}
xBitInt xBitInt::operator*(const xBitInt &mulX)
{
    
    xBitInt tmpX = xBitInt(*this);

    xBitInt ttmpX = xBitInt(tmpX);
    xBitInt mul = xBitInt(mulX);
    uint64_t len = mul.GetBitLength();
    std::cout << "Mul = " << mul.ToString() << std::endl;
    /*while(mul.ToString() != "1")
    {
        tmpX+=ttmpX;
        mul--;
        //std::cout << "Mul = " << mul.ToString() << std::endl;
    }*/
    uint64_t c = 0;
    xBitInt temp = xBitInt(0);
    uint64_t push = 0;
    //for(uint64_t i = 0; i < ttmpX.m_length; i++)
    //{
        for(uint64_t byteC = 0; byteC < mul.m_length; byteC++)
        {
            xBitInt xx = xBitInt(tmpX);
            byte compare = 0b00000001;

            for(int z = 0; z < 8; z++)
            {
                if((compare & mul.m_buffer[byteC]) != 0)
                {
                    push = (byteC*8)+z;
                    xBitInt tmpXX = xBitInt(xx);
                    tmpXX = (tmpXX << static_cast<uint64_t>((byteC*8)+z)); //It's not really necessary to do this but whatever
                    temp+=tmpXX;
                }
                compare = compare << 1;
                
                //std::cout << temp.GetDebugInfo() << std::endl;
                
            }
        }
    //}
   
    return temp;
}
xBitInt xBitInt::operator*(int mul)
{
    xBitInt tmpX = xBitInt(*this);
    //Let's just check for a shortcut
    if(mul == 2)
    {
        
       uchar leftBit = 1;
       uchar prev = 0;
        for(uint64_t i = 0; i < tmpX.m_length; i+=tmpX.m_cpuSize)
        {
            if(leftBit == 0)
            {
                break;
            }
            if(i == tmpX.m_length-1 && leftBit == 128)
            {
                tmpX.m_Resize(1);
            }
            for(int u = 0; u < tmpX.m_cpuSize;u++)
            {
                if ((i*tmpX.m_cpuSize)+u >= tmpX.m_length && leftBit == 0)
                {
                    break;
                }
                prev = leftBit;
                leftBit = tmpX.m_buffer[(i*tmpX.m_cpuSize)+u] & 0b10000000;
                std::cout << "checking index: " << std::to_string((i*tmpX.m_cpuSize)+u) << std::endl;
                tmpX.m_buffer[(i*tmpX.m_cpuSize)+u] = tmpX.m_buffer[(i*tmpX.m_cpuSize)+u] << 1;
                if((i*tmpX.m_cpuSize)+u >= tmpX.m_length && leftBit == 128)
                {
                    tmpX.m_Resize(1);
                }
                if(prev == 128)
                {
                    tmpX.m_buffer[(i*tmpX.m_cpuSize)+u] = tmpX.m_buffer[(i*tmpX.m_cpuSize)+u] | 0b00000001;
                }
                
            }
        }
        
        return tmpX;
    }
    /*for(size_t i = 0; i < m_length;i+=m_cpuSize/2)
    {
        for(int u = 0; u < m_cpuSize/2;u++)
        {
            if(i*(m_cpuSize/2))+u >= m_length)
            {
                break;
            }
            size_t tmp = 0;
            (byte*)(&tmp)[0] = tmpX.m_buffer[(i*(m_cpuSize/2))+u];
        }
    }*/
    xBitInt ttmpX = xBitInt(tmpX);
    uint64_t* ttmpX_address = (uint64_t*)&ttmpX; //debug
    uint64_t* tmpX_address = (uint64_t*)&tmpX; //debug
    for(int i = 0; i < mul-1; i++)
    {
        tmpX+=ttmpX;
        //std::cout << "tmpX: " << tmpX.ToString() << std::endl;
    }
    return tmpX;
}
xBitInt xBitInt::operator*=(xBitInt &mulX)
{
    *this = *this*mulX;
    return *this;
}