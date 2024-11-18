#pragma once
// #include "method.hh"
#include <string>
#include <variant>

namespace Frame
{
using RegType = uint64_t;
using Imm = std::variant<RegType, std::string>;
// using OpcodeType = uint8_t;
};
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