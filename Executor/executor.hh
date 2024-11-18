#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Frame
{
  using RegValue = int64_t;
  class Method;
}; // namespace Frame

namespace Instruction
{
  class Instr;
}; // namespace Instruction

class Executor {
  private:
    Frame::RegValue accumulator_;
    std::vector<std::shared_ptr<Frame::Method>> callStack_;
    std::unordered_map<std::string, std::shared_ptr<Frame::Method>> cleanMethodList_;


    //через switch-case либо через диспатч
    void handleInstruction(Instruction::Instr& instr, Frame::Method& frame);

    //
    void handleCall(const std::string& callMethod);

    void simpleInterpreter();


  public:
    Executor () 
    {
      accumulator_ = 0;
    };
    // void SimpleInterpreter()
    const Frame::RegValue& getAccumulator();
    void setAccumulator(const Frame::RegValue& val) 
    {
      accumulator_ = val;
    }
};
  