#pragma once
#include "method.hh"

#define CREATE_INSTR(method, opcode, rd, rs1, rs2, imm, mark)                                               \
emit(method, Method::Instr {opcode, rd, rs1, rs2, imm, mark});

#define CREATE_ARITHMETIC_INSTR(opcode, name)                                                               \
void create##name(Method::Method& method, Method::RegType rd, Method::RegType rs1, Method::RegType rs2)     \
{                                                                                                           \
  CREATE_INSTR(method, opcode, rd, rs1, rs2, 0, "")                                                         \
}

#define CREATE_COMPARE_INSTR(opcode, name)                                                                  \
void create##name(Method::Method& method, Method::RegType rs1, Method::RegType rs2)                         \
{                                                                                                           \
  CREATE_INSTR(method, opcode, 0, rs1, rs2, 0, "")                                                          \
}                                                                                                           

#define CREATE_JMP_INSTR(opcode, name)                                                                      \
void create##name(Method::Method& method, Method::MarkType mark)                                            \
{                                                                                                           \
  CREATE_INSTR(method, opcode, 0, 0, 0, 0, mark)                                                            \
}



class Emitter {
  private:
    void emit(Method::Method& method, Method::Instr inst);

  public:
    Emitter() {};
    void createMv(Method::Method& method, Method::RegType reg, Method::ImmType imm)
    {
      CREATE_INSTR(method, Method::OpcodeTable::MV, reg, 0, 0, imm, "")
    }

    void createStacc(Method::Method& method, Method::RegType reg) 
    {
      CREATE_INSTR(method, Method::OpcodeTable::STACC, 0, reg, 0, 0, "")
    }

    void createLdacc(Method::Method& method, Method::RegType reg) 
    {
      CREATE_INSTR(method, Method::OpcodeTable::LDACC, reg, 0, 0, 0, "")
    }

    CREATE_ARITHMETIC_INSTR(Method::OpcodeTable::ADD, Add)
    CREATE_ARITHMETIC_INSTR(Method::OpcodeTable::SUB, Sub)
    CREATE_ARITHMETIC_INSTR(Method::OpcodeTable::DIV, Div)
    CREATE_ARITHMETIC_INSTR(Method::OpcodeTable::MUL, Mul)

    CREATE_COMPARE_INSTR(Method::OpcodeTable::CMPEQ, Cmpeq)
    CREATE_COMPARE_INSTR(Method::OpcodeTable::CMPGT, Cmpgt)
    CREATE_COMPARE_INSTR(Method::OpcodeTable::CMPGE, Cmpge)
    
    CREATE_JMP_INSTR(Method::OpcodeTable::JMP, Jmp)
    CREATE_JMP_INSTR(Method::OpcodeTable::CJMPT, Cjmpt)
    CREATE_JMP_INSTR(Method::OpcodeTable::CJMPF, Cjmpf)

    void createCall(Method::Method& method, Method::MarkType mark)
    {
      CREATE_INSTR(method, Method::OpcodeTable::CALL, 0, 0, 0, 0, mark)
    }

    void createRet(Method::Method& method)
    {
      CREATE_INSTR(method, Method::OpcodeTable::RET, 0, 0, 0, 0, "")
    }   

    void createMark(Method::Method& method, Method::MarkType mark)
    {
      method.createMark(mark);
    }

    void createPrint(Method::Method& method, Method::MarkType description, Method::RegType reg)
    {
      CREATE_INSTR(method, Method::OpcodeTable::PRINT, 0, reg, 0, 0, description);
    }

};
