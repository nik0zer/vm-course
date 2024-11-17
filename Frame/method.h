#pragma once

#include "instruction.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>

namespace Frame
{
using RegValue = int64_t;
using RegType = uint64_t;
using OpcodeType = uint8_t;
using Imm = std::variant<Frame::RegType, std::string>;

class Method
{
  private:
    std::vector<Instruction::Instr&> instructionSet_;
    RegType paramsSize_;
    RegType localRegisters_;
    RegType allRegisters_;
    std::vector<RegValue> regFile_;
    RegValue PC {0};
    std::unordered_map<std::string, RegValue> marks;

  public:
    Method(const RegType &numOfParamenters, const RegType &numOfLocalRegisters) : paramsSize_(numOfParamenters), 
    localRegisters_(numOfLocalRegisters), allRegisters_(paramsSize_ + numOfLocalRegisters), 
    regFile_(allRegisters_), marks() {}

    void addInstruction(std::string opcode, Frame::RegType rd, Frame::RegType rs1, Frame::RegType rs2, Frame::Imm immedeate);

    const RegValue &getReg(const RegType &reg);
    void setReg(const RegType &reg, const RegValue &val);
    const RegValue &getAccumulator();
    void setAccumulator(const RegValue &val);
};

}