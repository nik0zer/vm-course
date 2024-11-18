#pragma once
#include "method.hh"

#define CREATE_INSTR(method, opcode, rd, rs1, rs2, imm, mark)                                               \
emit(method, Frame::Instr {opcode, rd, rs1, rs2, imm, mark});

#define CREATE_ARITHMETIC_INSTR(opcode, name)                                                               \
void create##name(Frame::Method& method, Frame::RegType rd, Frame::RegType rs1, Frame::RegType rs2)         \
{                                                                                                           \
  CREATE_INSTR(method, opcode, rd, rs1, rs2, 0, "")                                                         \
}

#define CREATE_COMPARE_INSTR(opcode, name)                                                                  \
void create##name(Frame::Method& method, Frame::RegType rs1, Frame::RegType rs2)                            \
{                                                                                                           \
  CREATE_INSTR(method, opcode, 0, rs1, rs2, 0, "")                                                          \
}                                                                                                           

#define CREATE_JMP_INSTR(opcode, name)                                                                      \
void create##name(Frame::Method& method, Frame::MarkType mark)                                              \
{                                                                                                           \
  CREATE_INSTR(method, opcode, 0, 0, 0, 0, mark)                                                            \
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

    void createStacc(Frame::Method& method, Frame::RegType reg) 
    {
      CREATE_INSTR(method, Frame::OpcodeTable::STACC, 0, reg, 0, 0, "")
    }

    void createLdacc(Frame::Method& method, Frame::RegType reg) 
    {
      CREATE_INSTR(method, Frame::OpcodeTable::LDACC, reg, 0, 0, 0, "")
    }

    CREATE_ARITHMETIC_INSTR(Frame::OpcodeTable::ADD, Add)
    CREATE_ARITHMETIC_INSTR(Frame::OpcodeTable::SUB, Sub)
    CREATE_ARITHMETIC_INSTR(Frame::OpcodeTable::DIV, Div)
    CREATE_ARITHMETIC_INSTR(Frame::OpcodeTable::MUL, Mul)

    CREATE_COMPARE_INSTR(Frame::OpcodeTable::CMPEQ, Cmpeq)
    CREATE_COMPARE_INSTR(Frame::OpcodeTable::CMPGT, Cmpgt)
    CREATE_COMPARE_INSTR(Frame::OpcodeTable::CMPGE, Cmpge)
    
    CREATE_JMP_INSTR(Frame::OpcodeTable::JMP, Jmp)
    CREATE_JMP_INSTR(Frame::OpcodeTable::CJMPT, Cjmpt)
    CREATE_JMP_INSTR(Frame::OpcodeTable::CJMPF, Cjmpf)

    void createCall(Frame::Method& method, Frame::MarkType mark)
    {
      CREATE_INSTR(method, Frame::OpcodeTable::CALL, 0, 0, 0, 0, mark)
    }

    void createRet(Frame::Method& method)
    {
      CREATE_INSTR(method, Frame::OpcodeTable::RET, 0, 0, 0, 0, 0)
    }   

    void createMark(Frame::Method& method, Frame::MarkType mark)
    {
      method.createMark(mark);
    }

};
