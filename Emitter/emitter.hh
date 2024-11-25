#pragma once
#include "method.hh"
#include "executor.hh"
#include <vector>
#include <map>

namespace Executor
{
class Executor;
} // namespace Executor


namespace Emitter
{

struct emitterInstr
{
  Method::OpcodeType opcode;
  Method::OffsetType offset;
  Method::ImmType imm;
  Method::RegType rs1, rs2, rd;
  std::string mark;
  uint8_t instrSize;
};


class Emitter {
  private:
    std::vector<emitterInstr> EmittedInstrs {};
    std::string currName;
    Method::RegType params {0};
    Method::RegType localVars {0};

    std::vector<std::string> methods {};
    std::map<std::string, uint32_t> marks {};

  public:
    Emitter() {};
    void startEmitMethod(const std::string &name);
    void endEmitMethod(Executor::Executor &executor, Method::RegType params, Method::RegType localVars);
    void CreateMark(const std::string &markName);

    // реализовать create меотды которые кладут инструкции в EmittedInstrs

};

}