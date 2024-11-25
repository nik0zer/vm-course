#pragma once

#include "frame.hh"
#include "emitter.hh"

#include <vector>

#define MAX_STACK_DEPTH 1024

// #define COMPUTED_GOTO

namespace Emitter
{
class Emitter;
}

namespace Executor
{

class Executor {
  private:
    Frame::Frame callStack_[MAX_STACK_DEPTH] {};
    std::vector<Method::Method *> methodList_ {};

    void handleCall(int callMethod);
    Frame::Frame *stackPtr_ { &callStack_[MAX_STACK_DEPTH - 1] };

  public:
    Executor() {};

    void simpleInterpreterExecute(Method::Method *method, Frame::Frame *prevFrame);

    friend class Emitter::Emitter;
};

}