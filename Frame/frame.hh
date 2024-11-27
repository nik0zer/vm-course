#pragma once

#include "method.hh"
#include <algorithm>

namespace Frame
{

#define MAX_REG_FILE_SIZE 1024

class Frame
{
  private:
    Method::Method *method;
    Method::RegValue PC {0};
    Frame *prevFrame_;
    Method::RegValue accumulator_;
    Method::RegValue regFile_[];


  public:
    Frame(Method::Method *method, Frame* prevFrame, uint8_t** stackPtr) : method(method), prevFrame_(prevFrame)
    {
        new (&regFile_) Method::RegValue[method->allRegisters()];
        (*stackPtr) = reinterpret_cast<uint8_t *>(&(regFile_[method->allRegisters() + 1]));
    }

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

    inline void setAcc(const Method::RegValue &acc)
    {
        accumulator_ = acc;
    }

    inline const Method::RegValue &getAcc()
    {
        return accumulator_;
    }

    template <typename ValType>
    inline const ValType &getBytecodePC()
    {
        auto pc = PC;
        PC += sizeof(ValType);
        return method->getBytecode<ValType>(pc);
    }

    inline void copyParams(const Frame &otherFrame)
    {
        std::copy_n(otherFrame.regFile_, method->paramsSize(), regFile_);
    }

    inline Frame *getPrevFrame()
    {
        return prevFrame_;
    }

    inline const Method::RegType &getAllRegs()
    {
        return method->allRegisters();
    }


};

}