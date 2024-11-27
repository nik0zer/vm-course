#pragma once
#include <cstdint>
#include <string>

namespace Method
{

using RegValue = int64_t;
using RegType = uint16_t;
using ImmType = RegValue;
using OffsetType = int32_t;
using AddressType = uint8_t *;
using OpcodeType = uint8_t;
using MarkType = std::string;

class Method
{
  private:
    RegType paramsSize_;
    RegType localRegisters_;
    RegType allRegisters_;
    RegValue bytecodeSize_;
    uint8_t *bytecode_;

  public:
    Method(const RegType &numOfParamenters, const RegType &numOfLocalRegisters, const RegValue &bytecodeSize,
    uint8_t *bytecode) :
    paramsSize_(numOfParamenters), bytecodeSize_(bytecodeSize), bytecode_(bytecode),
    localRegisters_(numOfLocalRegisters), allRegisters_(paramsSize_ + numOfLocalRegisters) {}
    ~Method() { delete bytecode_; }

    inline const RegType &paramsSize() {return paramsSize_;}
    inline const RegType &localRegisters() {return localRegisters_;}
    inline const RegType &allRegisters() {return allRegisters_;}

    template <typename ValType>
    inline ValType &getBytecode(RegValue pc) { return *(reinterpret_cast<ValType *>(bytecode_ + pc)); }
};

}