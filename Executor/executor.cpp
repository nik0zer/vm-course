#include "executor.hh"
#include "method.hh"

constexpr uint8_t IMM_1_REG_1_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::ImmType)
+ sizeof(Method::RegType);
constexpr uint8_t REG_1_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::RegType);
constexpr uint8_t IMM_1_REG_1_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::ImmType)
+ sizeof(Method::RegType);
constexpr uint8_t IMM_1_REG_1_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::ImmType);
constexpr uint8_t REG_3_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::RegType) * 3U;


#define ALL_INSTR_LIST  \
    _(0, MV, IMM_1_REG_1_SIZE)          \
    _(1, STACC, REG_1_SIZE)       \
    _(2, LDACC, REG_1_SIZE)       \
    _()

#define DISPATCH_INSTR(opcode, name, frame) \
    case opcode: name(frame); break;

#define GENERATE_DISPATCH_SWITCH(frame) \
    switch (opcode) {                  \
        ALL_INSTR_LIST(DISPATCH_INSTR)   \
        default:                         \
            std::cerr << "Unknown opcode" << std::endl; \
            break;                     \
    }


#define SET_REG(reg, val)                                                   \
    method->setReg(reg, val) 

#define GET_REG(reg)                                                        \
    method->getReg(reg) 

#define MV(name)                                                            \
inline void name (Method::RegType rd, Method::RegType imm) {                \
    SET_REG(rd, imm);                                                       \
}

#define ARITHMETICAL(operator, name)                                        \
inline void name (RegType rd, RegType rs1, RegType rs2) {                   \
    SET_REG(rd, GET_REG(rs1) operator GET_REG(rs2));                        \
}

#define COMPARE(operator, name)                                             \
inline void name (RegType rs1, RegType rs2) {                               \
    accumulator_ = GET_REG(rs1) operator GET_REG(rs2) ;                     \
}
    
#define JUMP(conditional, name, offset)                                     \
inline void name (RegType offset) {                                         \
    if(conditional) {                                                       \
        method->setPC(method->getMark(offset) - 1);                         \
    }                                                                       \
}                                          

MV(handleMV)

// #define ARITHMETICAL(operator, name)                                        \
// case name:                                                                  \
// {                                                                           \
//     SET_REG(instr.rd, GET_REG(instr.rs1) operator GET_REG(instr.rs2));      \
//     break;                                                                  \
// }

// #define COMPARE(operator, name)                                             \
// case name:                                                                  \
// {                                                                           \
//     accumulator_ = GET_REG(instr.rs1) operator GET_REG(instr.rs2) ;         \
//     break;                                                                  \
// }

// #define JUMP(conditional, name, mark)                                       \
// case name:                                                                  \
// {                                                                           \
//     if(conditional) {                                                       \
//         method->setPC(method->getMark(mark) - 1);                           \
//     }                                                                       \
//     break;                                                                  \
// }

// #else

// #define PC_NEXT(method)                                                     \
//     method->setPC(method->getPC() + 1);

// #define RUN_NEXT_INST(method)                                               \
//     PC_NEXT(method)                                                         \
//     instr = method->getInstrPC();                                           \
//     goto *gotoLabels[static_cast<int>(instr.opcode)];                       \

// #define ARITHMETICAL(label, method, operator)                               \
//   label:                                                                    \
//     SET_REG(instr.rd, GET_REG(instr.rs1) operator GET_REG(instr.rs2));      \
//     RUN_NEXT_INST(method)                                                   \

// #define COMPARE(label, method, operator)                                    \
//   label:                                                                    \
//     accumulator_ = GET_REG(instr.rs1) operator GET_REG(instr.rs2) ;         \
//     RUN_NEXT_INST(method)                                                   \

// #define JUMP(label, method, conditional, mark)                              \
//   label:                                                                    \
//     if(conditional) {                                                       \
//         method->setPC(method->getMark(mark) - 1);                           \
//     }                                                                       \
//     RUN_NEXT_INST(method)                                                   \

// #endif

void Executor::handleCall(int callMethod)
{

}

void Executor::simpleInterpreterExecute(Method::Method *method, Frame::Frame *prevFrame)
{
    handleCall();
#ifndef COMPUTED_GOTO
    uint64_t numOfOperations = 0;
    while(true)
    {
        auto frame = stackPtr_;
        auto instr = frame->getInstrPC();
        GENERATE_DISPATCH_SWITCH(frame)
    }
#endif
}
//         numOfOperations++;
//         method->setPC(method->getPC() + 1);
//     }
//     std::cout << "[EXECUTED NUMBER OF OPERATIONS]: " << numOfOperations << std::endl;

// #else
//     const void* gotoLabels[] = {&&MV, &&STACC, &&LDACC, &&ADD, &&SUB, &&MUL, &&DIV, &&CMPEQ, 
//     &&CMPGT, &&CMPGE, &&JMP, &&CJMPT, &&CJMPF, &&CALL, &&RET, &&PRINT};
//     std::shared_ptr<Frame::Frame> method = callStack_.back();
//     Method::Instr instr = method->getInstrPC();
//   GETMETHOD:
//     method = callStack_.back();
//     instr = method->getInstrPC();
//     goto *gotoLabels[static_cast<int>(instr.opcode)];

//   MV:
//     SET_REG(instr.rd, instr.immedeate);
//     RUN_NEXT_INST(method)
    
//   STACC:
//     accumulator_ = GET_REG(instr.rs1);
//     RUN_NEXT_INST(method)

//   LDACC:
//     SET_REG(instr.rd, accumulator_);
//     RUN_NEXT_INST(method)

//     ARITHMETICAL(ADD, method, +)
//     ARITHMETICAL(SUB, method, -)
//     ARITHMETICAL(MUL, method, *)
//     ARITHMETICAL(DIV, method, /)

//     COMPARE(CMPEQ, method, ==)
//     COMPARE(CMPGT, method, >)
//     COMPARE(CMPGE, method, >=)

//     JUMP(JMP, method, true, instr.mark)
//     JUMP(CJMPT, method, accumulator_ == 1, instr.mark)
//     JUMP(CJMPF, method, accumulator_ != 1, instr.mark)

//   CALL:
//     PC_NEXT(method)
//     handleCall(instr.mark);
//     goto GETMETHOD;


//   RET:
//     callStack_.pop_back();
//     if(!callStack_.empty())
//     {
//         goto GETMETHOD;
//     }
//     goto END;
    

//   PRINT:
//     std::cout << instr.mark << GET_REG(instr.rs1) << std::endl;
//     RUN_NEXT_INST(method)

//   END:
//     return;

// #endif


// }