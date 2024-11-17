#include "method.h"
// #include "instruction.h"

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

const RegValue &Method::getAccumulator() 
{

}

void Method::setAccumulator(const RegValue &val) 
{

}

void Method::addInstruction(std::string opcode, Frame::RegType rd, Frame::RegType rs1, Frame::RegType rs2, Frame::Imm immedeate) {
    instructionSet_.push_back({opcode, rd, rs1, rs2, immedeate}); 
}
}