#include "emitter.hh"
#include "executor.hh"
#include <iostream>

void BootProgram() {
    Emitter emit;
    std::shared_ptr<Frame::Method> pMain(new Frame::Method(0, 4));
    emit.createMv(*pMain, 0, 5);
    emit.createMv(*pMain, 1, 1);
    emit.createMv(*pMain, 2, 1);
    emit.createMark(*pMain, "Cicle");
    emit.createSub(*pMain, 0, 0, 1);
    emit.createPrint(*pMain, "reg 0: ", 0);
    emit.createMul(*pMain, 2, 2, 0);
    emit.createCmpgt(*pMain, 0, 1);
    emit.createCjmpt(*pMain, "Cicle");
    emit.createPrint(*pMain, "factorial: ", 2);
    emit.createRet(*pMain);
    std::unordered_map<std::string, std::shared_ptr<Frame::Method>> methods {};
    methods["main"] = pMain;
    Executor exec(methods);
    exec.simpleInterpreter("main");
    
};

int main()
{
    BootProgram();
    return 0;
}