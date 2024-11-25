#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

namespace Method
{

using RegValue = int64_t;
using RegType = uint16_t;
using ImmType = RegValue;
using OffsetType = int32_t;
using OpcodeType = uint8_t;

enum class OpcodeTable : OpcodeType
{
  MV = 0,
  STACC = 1,
  LDACC = 2,
  ADD = 3,
  SUB = 4,
  MUL = 5,
  DIV = 6,
  CMPEQ = 7,
  CMPGT = 8,
  CMPGE = 9,
  JMP = 10,
  CJMPT = 11,
  CJMPF = 12,
  CALL = 13,
  RET = 14,
  PRINT = 15,
};

struct Instr
{
  OpcodeTable opcode;
  RegType rd, rs1, rs2;
  ImmType imm;
  OffsetType offset;
};

class Method
{
  private:
    RegType paramsSize_;
    RegType localRegisters_;
    RegType allRegisters_;
    RegValue bytecodeSize_;
    const uint8_t *bytecode_;

  public:
    Method(const RegType &numOfParamenters, const RegType &numOfLocalRegisters, const RegValue &bytecodeSize,
    const uint8_t *bytecode) : 
    paramsSize_(numOfParamenters), bytecodeSize_(bytecodeSize), bytecode_(bytecode),
    localRegisters_(numOfLocalRegisters), allRegisters_(paramsSize_ + numOfLocalRegisters) {}
    ~Method() { delete bytecode_; }

    void addInstruction(Instr instr);

    inline const RegType &paramsSize() {return paramsSize_;}
    inline const RegType &localRegisters() {return localRegisters_;}
    inline const RegType &allRegisters() {return allRegisters_;}

    template <typename ValType>
    inline const ValType &getBytecode(RegValue pc) { return *(reinterpret_cast<ValType *>(bytecode_ + pc)); } 
};

// rs1: frame->getBytecode<RegType>(); frame->setPC(frame->getPC() + sizeof(RegType));

}