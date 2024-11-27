#include "emitter.hh"
#include "method.hh"
#include <sys/mman.h>

namespace Emitter
{

template<typename ValType>
static void PutDataToBuffer(uint8_t **ptr, ValType val) {
    *(reinterpret_cast<ValType *>(*ptr)) = val;
    (*ptr) += sizeof(val);
}

void Emitter::startEmitMethod(const std::string &name) {
    marks = std::map<std::string, uint32_t>();
    if(std::find(methods.begin(), methods.end(), name) == methods.end())
    {
        methods.push_back(name);
    }
    currName = name;
}

void Emitter::endEmitMethod(Executor::Executor &executor, Method::RegType params, Method::RegType localVars) {
    auto methodIter = std::find(methods.begin(), methods.end(), currName);
    auto index = std::distance(methods.begin(), methodIter);
    uint32_t methodSize = 0;
    for(auto i : EmittedInstrs)
    {
        methodSize += i.instrSize;
    }
    uint8_t *buffer = static_cast<uint8_t *>(mmap(nullptr, methodSize,
    PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
    auto currDataPtr = buffer;

    // загрузить инструкции в буффер (используй функцию PutDataToBuffer с нужным типом передавая туда &currDataPtr,
    // он положит и подвинет) пропатчив инструкции джампа (в джампе заменить марк на высчитанный офсет)
    // и кола (заменить марк функции на индекс функции найденный в векторе methods,
    // если его там нет то добавить его туда)

    #define PUT_TO_BUF_IMM_1_REG_1()                                    \
    PutDataToBuffer<Method::OpcodeType>(&currDataPtr, instr.opcode);    \
    PutDataToBuffer<Method::RegType>(&currDataPtr, instr.rd);           \
    PutDataToBuffer<Method::ImmType>(&currDataPtr, instr.imm);          \
    currPosition += instr.instrSize;

    #define PUT_TO_BUF_REG_1()                                          \
    PutDataToBuffer<Method::OpcodeType>(&currDataPtr, instr.opcode);    \
    PutDataToBuffer<Method::RegType>(&currDataPtr, instr.rs1);          \
    currPosition += instr.instrSize;

    #define PUT_TO_BUF_REG_3()                                          \
    PutDataToBuffer<Method::OpcodeType>(&currDataPtr, instr.opcode);    \
    PutDataToBuffer<Method::RegType>(&currDataPtr, instr.rd);           \
    PutDataToBuffer<Method::RegType>(&currDataPtr, instr.rs1);          \
    PutDataToBuffer<Method::RegType>(&currDataPtr, instr.rs2);          \
    currPosition += instr.instrSize;

    #define PUT_TO_BUF_REGIN_2()                                        \
    PutDataToBuffer<Method::OpcodeType>(&currDataPtr, instr.opcode);    \
    PutDataToBuffer<Method::RegType>(&currDataPtr, instr.rs1);          \
    PutDataToBuffer<Method::RegType>(&currDataPtr, instr.rs2);          \
    currPosition += instr.instrSize;


    #define PUT_TO_BUF_MARK()                                           \
    currPosition += instr.instrSize;                                    \
    PutDataToBuffer<Method::OpcodeType>(&currDataPtr, instr.opcode);    \
    PutDataToBuffer<Method::OffsetType>(&currDataPtr, static_cast<Method::OffsetType>(currPosition - marks[instr.mark]));

    #define PUT_TO_BUF_CALL_MARK()\
    currPosition += instr.instrSize; \
    PutDataToBuffer<Method::OpcodeType>(&currDataPtr, instr.opcode); \
    {\
    auto methodIter = std::find(methods.begin(), methods.end(), instr.mark); \
    if(methodIter == methods.end()) { \
        methodIter = methods.insert(methodIter, instr.mark); \
    } \
    }\
    PutDataToBuffer<Method::OffsetType>(&currDataPtr, static_cast<Method::OffsetType>(std::distance(methods.begin(), methodIter)));

    #define PUT_TO_BUF_CALL_NAPI() \
    PutDataToBuffer<Method::OpcodeType>(&currDataPtr, instr.opcode); \
    PutDataToBuffer<Method::AddressType>(&currDataPtr, instr.address); \
    currPosition += instr.instrSize;

    #define PUT_TO_BUF_OPCODE() \
    PutDataToBuffer<Method::OpcodeType>(&currDataPtr, instr.opcode); \
    currPosition += instr.instrSize;

    #define CASE_INSTR(opcode, mnemonic, format)  \
    case opcode:                                  \
        PUT_TO_BUF_##format()                     \
        break;

    for (auto instr: EmittedInstrs) {
        switch (instr.opcode) {
            ALL_INSTR_LIST(CASE_INSTR)
        }
    }


    Method::Method *method = new Method::Method(params, localVars, methodSize, buffer);
    if(executor.methodList_.size() <= index)
    {
        executor.methodList_.resize(index * 2);
    }
    executor.methodList_[index] = method;

}

void Emitter::CreateMark(const std::string &markName)
{
    uint32_t markAddress = 0;
    for(auto i : EmittedInstrs)
    {
        markAddress += i.instrSize;
    }
    marks[markName] = markAddress;
}


#define GEN_CREATE_IMM_1_REG_1(num_opcode, mnemonic, format)              \
void Emitter::Create##mnemonic(Method::RegType rd, Method::ImmType imm) { \
    emitterInstr instr{};                                                 \
    instr.opcode = num_opcode;                                            \
    instr.rd = rd;                                                        \
    instr.imm = imm;                                                      \
    instr.instrSize = SIZE_##format;                                      \
    EmittedInstrs.push_back(instr);                                       \
}

#define GEN_CREATE_REG_1(num_opcode, mnemonic, format) \
void Emitter::Create##mnemonic(Method::RegType rs1) {  \
    emitterInstr instr{};                              \
    instr.opcode = num_opcode;                         \
    instr.rs1 = rs1;                                   \
    instr.instrSize = SIZE_##format;                   \
    EmittedInstrs.push_back(instr);                    \
}

#define GEN_CREATE_REG_3(num_opcode, mnemonic, format)                                                              \
void Emitter::Create##mnemonic(Method::RegType rd, Method::RegType rs1, Method::RegType rs2) { \
    emitterInstr instr{};                                                                                           \
    instr.opcode = num_opcode;                                                                                      \
    instr.rd = rd;                                                                                                  \
    instr.rs1 = rs1;                                                                                                \
    instr.rs2 = rs2;                                                                                                \
    instr.instrSize = SIZE_##format;                                                                                \
    EmittedInstrs.push_back(instr);                                                                                 \
}

#define GEN_CREATE_REGIN_2(num_opcode, mnemonic, format)                   \
void Emitter::Create##mnemonic(Method::RegType rs1, Method::RegType rs2) { \
    emitterInstr instr{};                                                  \
    instr.opcode = num_opcode;                                             \
    instr.rs1 = rs1;                                                       \
    instr.rs2 = rs2;                                                       \
    instr.instrSize = SIZE_##format;                                       \
    EmittedInstrs.push_back(instr);                                        \
}

#define GEN_CREATE_MARK(num_opcode, mnemonic, format)           \
void Emitter::Create##mnemonic(Method::MarkType mark_name) {    \
    emitterInstr instr{};                                       \
    instr.opcode = num_opcode;                                  \
    instr.mark = mark_name;                                     \
    instr.instrSize = SIZE_##format;                            \
    EmittedInstrs.push_back(instr);                             \
}

#define GEN_CREATE_CALL_MARK(num_opcode, mnemonic, format)      \
void Emitter::Create##mnemonic(Method::MarkType call_name) {    \
    emitterInstr instr{};                                       \
    instr.opcode = num_opcode;                                  \
    instr.mark = call_name;                                     \
    instr.instrSize = SIZE_##format;                            \
    EmittedInstrs.push_back(instr);                             \
}

#define GEN_CREATE_CALL_NAPI(num_opcode, mnemonic, format)          \
void Emitter::Create##mnemonic(Method::AddressType address) {       \
    emitterInstr instr{};                                           \
    instr.opcode = num_opcode;                                      \
    instr.address = address;                                        \
    instr.instrSize = SIZE_##format;                                \
    EmittedInstrs.push_back(instr);                                 \
}

#define GEN_CREATE_OPCODE(num_opcode, mnemonic, format) \
void Emitter::Create##mnemonic() {                      \
    emitterInstr instr{};                               \
    instr.opcode = num_opcode;                          \
    instr.instrSize = SIZE_##format;                    \
    EmittedInstrs.push_back(instr);                     \
}

#define DEFINE_CREATE_METHOD_DEFINITION(num_opcode, mnemonic, format) \
    GEN_CREATE_##format(num_opcode, mnemonic, format)                 \

ALL_INSTR_LIST(DEFINE_CREATE_METHOD_DEFINITION)

#undef DEFINE_CREATE_METHOD_DEFINITION

}