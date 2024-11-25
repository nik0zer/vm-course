#pragma once

#include <string>
#include <vector>
#include <memory>
#include "frame.hh"
#include <unordered_map>

#define MAX_STACK_DEPTH 1024

#define COMPUTED_GOTO

class Executor {
  private:
    Frame::Frame callStack_[MAX_STACK_DEPTH] {};
    Method::Method *cleanMethodList_;

    void handleCall(const std::string& callMethod);

    Frame::Frame *stackPtr_ { &callStack_[MAX_STACK_DEPTH - 1] };

  public:
    Executor(Method::Method *methods) : cleanMethodList_(methods) {};
    void simpleInterpreterExecute(Method::Method *method, Frame::Frame *prevFrame);
};