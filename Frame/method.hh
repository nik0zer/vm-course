#pragma once

#include "instruction.hh"
#include "executor.hh"

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>

namespace Instruction
{
  class Instr;
}
namespace Frame
{
using RegValue = int64_t;
using RegType = uint64_t;

class Method
{
  private:
    RegType paramsSize_;
    RegType localRegisters_;
    RegType allRegisters_;
    std::vector<RegValue> regFile_;
    RegValue PC {0};
    std::unordered_map<std::string, RegValue> marks;

  public:
    std::vector<Instruction::Instr> instructionSet_;
    Method(const RegType &numOfParamenters, const RegType &numOfLocalRegisters) : paramsSize_(numOfParamenters), 
    localRegisters_(numOfLocalRegisters), allRegisters_(paramsSize_ + numOfLocalRegisters), 
    regFile_(allRegisters_), marks() {}

    std::shared_ptr<Method> getCleanCopy() const;

    void addInstruction(std::string opcode, Frame::RegType rd, Frame::RegType rs1, Frame::RegType rs2, Frame::Imm immedeate);

    const RegValue &getReg(const RegType &reg);
    void setReg(const RegType &reg, const RegValue &val);
    const RegValue &getAccumulator (Executor& exec);
    void setAccumulator(Executor& exec, const RegValue &val);
};

}