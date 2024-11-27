#include "emitter.hh"
#include "executor.hh"
#include "frame.hh"
#include "method.hh"
#include <iostream>

void napiPrint(Frame::Frame *frame)
{
    std::cout << "---------------" << std::endl;
    for(size_t i = 0; i < frame->getAllRegs(); i++) {
        std::cout << "reg " << i << ": " << frame->getReg(i) << std::endl;
    }
    std::cout << "---------------" << std::endl;
}

void napiPrintAA(Frame::Frame *frame)
{
    std::cout << "AAAA" << std::endl;
}
void napiPrintBB(Frame::Frame *frame)
{
    std::cout << "BBB" << std::endl;
}

void FibsCycle(uint64_t n) {
    auto exec = new Executor::Executor();
    auto emitter = new Emitter::Emitter();
    emitter->startEmitMethod("main");
    emitter->CreateMV(0, 1);
    emitter->CreateMV(1, 1);
    emitter->CreateMV(2, 1);
    emitter->CreateMV(3, n);
    emitter->CreateMark("Cicle");
    emitter->CreateSTACC(2);
    emitter->CreateADD(2, 1, 2);
    emitter->CreateLDACC(1);
    emitter->CreateSUB(3, 3, 0);
    emitter->CreateCMPGT(3, 0);
    emitter->CreateCJMPT("Cicle");
    emitter->CreateCALLNAPI(reinterpret_cast<uint8_t *>(&napiPrint));
    emitter->CreateRET();
    emitter->endEmitMethod(*exec, 0, 5);

    exec->Run(0);
};

void FibsRecursion(uint64_t n)
{
    Emitter::Emitter emit;
    auto exec = new Executor::Executor();

    emit.startEmitMethod("Fibs");
    emit.CreateMV(5, 2);
    emit.CreateCMPGT(0, 5);
    emit.CreateCJMPT("recursion");
    emit.CreateMV(5, 1);
    emit.CreateSTACC(5);
    emit.CreateRET();

    emit.CreateMark("recursion");
    emit.CreateMV(5, 1);
    emit.CreateSUB(0, 0, 5);
    emit.CreateCALL("Fibs");
    emit.CreateLDACC(1);
    emit.CreateSUB(0, 0, 5);
    emit.CreateCALL("Fibs");
    emit.CreateLDACC(2);
    emit.CreateADD(3, 2, 1);
    emit.CreateSTACC(3);
    emit.CreateRET();
    emit.endEmitMethod(*exec, 1, 7);

    emit.startEmitMethod("main");
    emit.CreateMV(0, n);
    emit.CreateCALL("Fibs");
    emit.CreateLDACC(2);
    emit.CreateCALLNAPI(reinterpret_cast<uint8_t *>(&napiPrint));
    emit.CreateRET();
    emit.endEmitMethod(*exec, 0, 5);

    exec->Run(1);
};

int main()
{
    FibsRecursion(15);
    FibsCycle(14);
    return 0;
}