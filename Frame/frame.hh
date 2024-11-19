#pragma once
#include "method.hh"
#include <memory>
#include <stdexcept>

namespace Frame
{

class Frame
{
  private:
    std::shared_ptr<Method> method;
    std::vector<RegValue> regFile_;
    RegValue PC {0};



  public:
    Frame(std::shared_ptr<Method> method) : method(method), regFile_(method->allRegisters()) {}

    inline const RegValue &getReg(const RegType &reg)
    {
        if(reg >= method->allRegisters())
        {
            throw std::runtime_error("REG NUM OUT OF BOUNDS");
        }
        return regFile_[reg];
    }

    inline void setReg(const RegType &reg, const RegValue &val)
    {
        if(reg >= method->allRegisters())
        {
            throw std::runtime_error("REG NUM OUT OF BOUNDS");
        }
        regFile_[reg] = val;
    }


    inline void setPC(const RegValue &pc)
    {
        PC = pc;
    }

    inline const RegValue &getPC()
    {
        return PC;
    }

    inline const Instr &getInstrPC()
    {
        return method->getInstr(PC);
    }

    inline const RegValue &getMark(const std::string &mark)
    {
        return method->getMark(mark);
    }


};

}