#pragma once
#include "method.h"

namespace Frame
{

class Method;

}

namespace Instruction
{

class Instr
{
public:
    std::string opcode;
    Frame::RegType rd, rs1, rs2;
    Frame::Imm immedeate;
};


}