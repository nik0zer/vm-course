#pragma once

#include <string>
#include <vector>
#include <memory>
#include "method.hh"
#include <unordered_map>

// #define DISPATCH_TABLE

class Executor {
  private:
    Frame::RegValue accumulator_;
    std::vector<std::shared_ptr<Frame::Method>> callStack_;
    std::unordered_map<std::string, std::shared_ptr<Frame::Method>> cleanMethodList_;
    
    void handleCall(const std::string& callMethod);

  public:
    Executor () 
    {
      accumulator_ = 0;
    };
    void simpleInterpreter(const std::string &EntryPoint);
    const Frame::RegValue& getAccumulator();
    void setAccumulator(const Frame::RegValue& val) 
    {
      accumulator_ = val;
    }
};