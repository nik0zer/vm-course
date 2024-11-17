#pragma once
#include "method.h"
#include "instruction.h"
#include "emitter.hh"

#include <functional>


class Executor {
  private:
    Frame::RegType accumulator_;
    std::vector<Frame::Method> callStack_;
    std::unordered_map<std::string, std::function<int64_t>> functionList_;


    //через switch-case либо через диспатч
    void handleInstruction(const Instruction::Instr& instr, Frame::Method& frame);

    //
    void handleCall();

  public:
    Executor () 
    {
        accumulator_ = 0;
    };
};
  