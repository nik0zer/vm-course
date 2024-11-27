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
  Method::ImmType imm;
  Method::RegType rs1, rs2, rd;
  std::string mark;
  Method::AddressType address;
  uint8_t instrSize;
};


class Emitter {
  private:
    std::vector<emitterInstr> EmittedInstrs {};
    std::string currName;
    uint32_t currPosition = 0;
    Method::RegType params {0};
    Method::RegType localVars {0};

    std::vector<std::string> methods {};
    std::map<std::string, uint32_t> marks {};

  public:
    Emitter() {};
    void startEmitMethod(const std::string &name);
    void endEmitMethod(Executor::Executor &executor, Method::RegType params, Method::RegType localVars);
    void CreateMark(const std::string &markName);

    #define DECLARE_IMM_1_REG_1(num_opcode, mnemonic, format) void Create##mnemonic(Method::RegType rd, Method::ImmType imm);
    #define DECLARE_REG_1(num_opcode, mnemonic, format) void Create##mnemonic(Method::RegType rs1);
    #define DECLARE_REG_3(num_opcode, mnemonic, format) void Create##mnemonic(Method::RegType rd, Method::RegType rs1, Method::RegType rs2);
    #define DECLARE_REGIN_2(num_opcode, mnemonic, format) void Create##mnemonic(Method::RegType rs1, Method::RegType rs2);
    #define DECLARE_MARK(num_opcode, mnemonic, format) void Create##mnemonic(Method::MarkType mark_name);
    #define DECLARE_CALL_MARK(num_opcode, mnemonic, format) void Create##mnemonic(Method::MarkType call_name);
    #define DECLARE_CALL_NAPI(num_opcode, mnemonic, format) void Create##mnemonic(Method::AddressType address);
    #define DECLARE_OPCODE(num_opcode, mnemonic, format) void Create##mnemonic();

    #define DECLARE_CREATES(num_opcode, mnemonic, format)                   \
      DECLARE_##format(num_opcode, mnemonic, format)


    ALL_INSTR_LIST(DECLARE_CREATES)

    #undef DECLARE_CREATES
    #undef DECLARE_IMM_1_REG_1
    #undef DECLARE_REG_1
    #undef DECLARE_REG_3
    #undef DECLARE_REGIN_2
    #undef DECLARE_MARK
    #undef DECLARE_CALL_MARK
    #undef DECLARE_CALL_NAPI
    #undef DECLARE_OPCODE

};

}