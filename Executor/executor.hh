#pragma once

#include "frame.hh"
#include "emitter.hh"
#include "method.hh"

#include <vector>
#include <iostream>

constexpr uint64_t STACK_MEM_SIZE = (uint64_t)(1024) * 1024 * 50;

#define COMPUTED_GOTO

namespace Emitter
{
class Emitter;
}

namespace Executor
{

class Executor {
  private:
    std::vector<Method::Method *> methodList_ {};

    void handleCall(int callMethod);
    uint8_t *stackPtr_;
    uint8_t *stackMem_;

  public:
    uint64_t numOfOperations {};

    Executor() {
      stackMem_ = new uint8_t[STACK_MEM_SIZE];
      stackPtr_ = stackMem_;
    };

    ~Executor() {
      delete[] stackMem_;
    }

    inline Method::Method *getMethod(Method::CallMarkType mark) {
      return methodList_[mark];
    }

    inline void Run(Method::CallMarkType callIndex)
    {
      simpleInterpreterExecute(getMethod(callIndex), nullptr);
      std::cout << "Interpreter end work, num of operations: " << numOfOperations << std::endl;
    }

    void simpleInterpreterExecute(Method::Method *method, Frame::Frame *prevFrame);

    void nativeExecute(void *nativeMethod, Frame::Frame *prevFrame);

    friend class Emitter::Emitter;
};

}