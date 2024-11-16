#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

#ifndef METHOD_H
#define METHOD_H

namespace Frame
{
using RegValue = int64_t;
using RegType = uint64_t;
using OpcodeType = uint8_t;

class Method
{
private:
    RegType paramsSize_;
    RegType localRegisters_;
    RegType allRegisters_;
    std::vector<RegValue> regFile_;
    RegValue PC {0};
    std::unordered_map<std::string, RegValue> marks;

public:
    Method(const RegType &numOfParamenters, const RegType &numOfLocalRegisters) : paramsSize_(numOfParamenters), 
    localRegisters_(numOfLocalRegisters), allRegisters_(paramsSize_ + numOfLocalRegisters), 
    regFile_(allRegisters_), marks() {}

    const RegValue &getReg(const RegType &reg);
    void setReg(const RegType &reg, const RegValue &val);
};

}

#endif