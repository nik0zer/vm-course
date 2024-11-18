#include "emitter.hh"
#include "method.hh"
#include "instruction.hh"

void Emitter::emit(Frame::Method& method, Instruction::Instr& inst) {
    method.addInstruction(inst.opcode, inst.rd, inst.rs1, inst.rs2, inst.immedeate);
}
