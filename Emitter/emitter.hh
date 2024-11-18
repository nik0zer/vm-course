#pragma once
#include "method.hh"

#define CREATE_INSTR(method, opcode, rd, rs1, rs2, imm, mark)                                               \
emit(method, Frame::Instr {opcode, rd, rs1, rs2, imm, mark});

#define CREATE_ARITHMETIC_INSTR(opcode, name)                                                               \
void create##name(Frame::Method& method, Frame::RegType rd, Frame::RegType rs1, Frame::RegType rs2)         \
{                                                                                                           \
  CREATE_INSTR(method, opcode, rd, rs1, rs2, 0, "")                                                         \
}

class Emitter {
  private:
    void emit(Frame::Method& method, Frame::Instr inst);

  public:
    Emitter() {};
    void createMv(Frame::Method& method, Frame::RegType reg, Frame::ImmType imm)
    {
      CREATE_INSTR(method, Frame::OpcodeTable::MV, reg, 0, 0, imm, "")
    }

    CREATE_ARITHMETIC_INSTR(Frame::OpcodeTable::ADD, Add)
    CREATE_ARITHMETIC_INSTR(Frame::OpcodeTable::SUB, sub)
    CREATE_ARITHMETIC_INSTR(Frame::OpcodeTable::DIV, Div)
    CREATE_ARITHMETIC_INSTR(Frame::OpcodeTable::MUL, Mul)

    

    

};
