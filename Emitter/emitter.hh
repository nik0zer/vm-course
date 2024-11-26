#pragma once
#include "method.hh"
#include "executor.hh"
#include <vector>
#include <map>
#include "all_instrs.hh"

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

    #define DEFINE_CREATE_METHOD_DECLARATION(opcode, mnemonic, size) \
    void Create##mnemonic(Method::RegType rd = 0, Method::ImmType imm = 0, Method::RegType rs1 = 0, Method::RegType rs2 = 0);\
    void Create##mnemonic(Method::ImmType imm) { \
      Create##mnemonic(0, imm, 0, 0); \
    }
    ALL_INSTR_LIST(DEFINE_CREATE_METHOD_DECLARATION)

    #undef DEFINE_CREATE_METHOD_DECLARATION

};

}