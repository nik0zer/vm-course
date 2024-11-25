#include "emitter.hh"
#include "method.hh"

void Emitter::emit(Method::Method& method, Method::Instr inst) {
    method.addInstruction(inst);
}
