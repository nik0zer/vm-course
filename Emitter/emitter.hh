#pragma once
#include "instruction.h"
#include "method.h"


class Emitter {
  public:
    void emit(Frame::Method& method, Instruction::Instr& inst) {
      method.addInstruction(inst);
    };
};
