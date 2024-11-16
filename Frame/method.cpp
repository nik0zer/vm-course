#include "method.h"
#include <stdexcept>

namespace Frame
{

const RegValue &Method::getReg(const RegType &reg)
{
    if(reg >= allRegisters_)
    {
        throw std::runtime_error("REG NUM OUT OF BOUNDS");
    }
    return regFile_[reg];
}

void Method::setReg(const RegType &reg, const RegValue &val)
{
    if(reg >= allRegisters_)
    {
        throw std::runtime_error("REG NUM OUT OF BOUNDS");
    }
    regFile_[reg] = val;
}

}