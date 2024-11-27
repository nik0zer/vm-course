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

    // std::shared_ptr<Method::Method> Fibs(new Method::Method(1, 5));

    // emit.createMv(*Fibs, 5, 2);
    // emit.createCmpgt(*Fibs, 0, 5);
    // emit.createCjmpt(*Fibs, "recursion");
    // emit.createMv(*Fibs, 5, 1);
    // emit.createStacc(*Fibs, 5);
    // emit.createRet(*Fibs);

    // emit.createMark(*Fibs, "recursion");
    // emit.createMv(*Fibs, 5, 1);
    // emit.createSub(*Fibs, 0, 0, 5);
    // emit.createCall(*Fibs, "Fibs");
    // emit.createLdacc(*Fibs, 1);
    // emit.createSub(*Fibs, 0, 0, 5);
    // emit.createCall(*Fibs, "Fibs");
    // emit.createLdacc(*Fibs, 2);
    // emit.createAdd(*Fibs, 3, 2, 1);
    // emit.createStacc(*Fibs, 3);
    // emit.createRet(*Fibs);

    // std::shared_ptr<Method::Method> pMain(new Method::Method(0, 5));

    // emit.createMv(0, n);
    // emit.createCall("Fibs");
    // emit.createLdacc(2);
    // emit.createPrint("fib: ", 2);
    // emit.createRet(*pMain);

    // std::unordered_map<std::string, std::shared_ptr<Method::Method>> methods {};
    // methods["main"] = pMain;
    // methods["Fibs"] = Fibs;
    // Executor exec(methods);
    // exec.simpleInterpreter("main");

};

int main()
{
    FibsCycle(11);
    return 0;
}