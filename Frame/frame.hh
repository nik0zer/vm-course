#pragma once
#include "method.hh"
#include <memory>
#include <stdexcept>
#include <algorithm>

namespace Frame
{

class Frame
{
  private:
    Method::Method *method;
    Method::RegValue *regFile_;
    Method::RegValue PC {0};
    Frame *prevFrame_;

  public:
    Frame(Method::Method *method, Frame* prevFrame) : method(method), prevFrame_(prevFrame), 
    regFile_(new Method::RegValue[method->allRegisters()]) {}

    Frame() {}

    inline const Method::RegValue &getReg(const Method::RegType &reg)
    {
        return regFile_[reg];
    }

    inline void setReg(const Method::RegType &reg, const Method::RegValue &val)
    {
        regFile_[reg] = val;
    }


    inline void setPC(const Method::RegValue &pc)
    {
        PC = pc;
    }

    inline const Method::RegValue &getPC()
    {
        return PC;
    }

    inline const Method::Instr &getInstrPC()
    {
        return method->getInstr(PC);
    }

    inline const Method::RegValue &getMark(const std::string &mark)
    {
        return method->getMark(mark);
    }

    inline void copyParams(const Frame &otherFrame)
    {
        std::copy_n(otherFrame.regFile_, method->paramsSize(), regFile_);
    }

    inline const Frame *getPrevFrame()
    {
        return prevFrame_;
    }


};

}