#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>

class Executor;
class Emitter;

namespace Frame
{

using RegValue = int64_t;
using RegType = uint64_t;
using ImmType = RegValue;
using MarkType = std::string;
using OpcodeType = uint8_t;

enum class OpcodeTable : OpcodeType 
{
  MV = 0,
  STACK = 1,
  LDACK = 2,
  ADD = 3,
  SUB = 4,
  MUL = 5,
  DIV = 6,
  CMPEQ = 7,
  CMPGT = 8,
  CMPGE = 9,
  JMP = 10,
  CJMPT = 11,
  CJMPF = 13,
  CALL = 14,
  RET = 15,
};

struct Instr
{
    Frame::OpcodeTable opcode;
    Frame::RegType rd, rs1, rs2;
    Frame::ImmType immedeate;
    Frame::MarkType mark;
};

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
    std::vector<Instr> instructionSet_;
    Method(const RegType &numOfParamenters, const RegType &numOfLocalRegisters) : paramsSize_(numOfParamenters), 
    localRegisters_(numOfLocalRegisters), allRegisters_(paramsSize_ + numOfLocalRegisters), 
    regFile_(allRegisters_), marks() {}

    std::shared_ptr<Method> getCleanCopy() const;

    void addInstruction(Instr instr);

    const RegValue &getReg(const RegType &reg);
    void setReg(const RegType &reg, const RegValue &val);
    const RegValue &getPC();
    void setPC(const RegValue &pc);


};

}