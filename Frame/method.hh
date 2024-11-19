#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

namespace Frame
{

using RegValue = int64_t;
using RegType = uint64_t;
using ImmType = RegValue;
using MarkType = std::string;
using OpcodeType = uint8_t;

class Frame;

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
  ImmType immedeate;
  MarkType mark;
};

class Method
{
    RegType paramsSize_;
    RegType localRegisters_;
    RegType allRegisters_;
    std::unordered_map<std::string, RegValue> marks;
    std::vector<Instr> instructionSet_;
  public:
    Method(const RegType &numOfParamenters, const RegType &numOfLocalRegisters) : paramsSize_(numOfParamenters),
    localRegisters_(numOfLocalRegisters), allRegisters_(paramsSize_ + numOfLocalRegisters), marks() {}

    std::shared_ptr<Method> getCleanCopy() const;

    void addInstruction(Instr instr);

    inline const RegType &paramsSize() {return paramsSize_;}
    inline const RegType &localRegisters() {return localRegisters_;}
    inline const RegType &allRegisters() {return allRegisters_;}
    inline const Instr &getInstr(const RegValue &pc) {return instructionSet_[pc];}
    inline const RegValue &getMark(const std::string mark) {return marks[mark];}

    void createMark(const MarkType mark);
};

}