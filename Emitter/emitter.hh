#pragma once

namespace Frame {
  class Method;
};// namespace Frame

namespace Instruction {
  class Instr;
}; // namespace Instruction


class Emitter {
  private:
    void emit(Frame::Method& method, Instruction::Instr& inst);

  public:
    Emitter() {};
    // createMvInstr();
    // int createArithmeticalInstr();
    // createCompareInstr();
    // createJumpInstr();
    // createCallInstr();

};
