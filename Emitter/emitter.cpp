#include "emitter.hh"
#include "method.hh"

void Emitter::emit(Frame::Method& method, Frame::Instr inst) {
    method.addInstruction(inst);
}
