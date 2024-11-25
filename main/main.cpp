#include "emitter.hh"
#include "executor.hh"
#include <iostream>

void FibsCycle(uint64_t n) {
    Emitter emit;
    std::shared_ptr<Method::Method> pMain(new Method::Method(0, 5));
    emit.createMv(*pMain, 0, 1);
    emit.createMv(*pMain, 1, 1);
    emit.createMv(*pMain, 2, 1);
    emit.createMv(*pMain, 3, n);
    emit.createMark(*pMain, "Cicle");
    // emit.createPrint(*pMain, "reg 2: ", 2);
    emit.createStacc(*pMain, 2);
    emit.createAdd(*pMain, 2, 1, 2);
    emit.createLdacc(*pMain, 1);
    emit.createSub(*pMain, 3, 3, 0);
    emit.createCmpgt(*pMain, 3, 0);
    emit.createCjmpt(*pMain, "Cicle");
    emit.createPrint(*pMain, "fibonachi: ", 2);
    emit.createRet(*pMain);
    std::unordered_map<std::string, std::shared_ptr<Method::Method>> methods {};
    methods["main"] = pMain;
    Executor exec(methods);
    exec.simpleInterpreter("main");

};

void FibsRecursion(uint64_t n)
{
    Emitter emit;

    std::shared_ptr<Method::Method> Fibs(new Method::Method(1, 5));
    
    emit.createMv(*Fibs, 5, 2);
    emit.createCmpgt(*Fibs, 0, 5);
    emit.createCjmpt(*Fibs, "recursion");
    emit.createMv(*Fibs, 5, 1);
    emit.createStacc(*Fibs, 5);
    emit.createRet(*Fibs);

    emit.createMark(*Fibs, "recursion");
    emit.createMv(*Fibs, 5, 1);
    emit.createSub(*Fibs, 0, 0, 5);
    emit.createCall(*Fibs, "Fibs");
    emit.createLdacc(*Fibs, 1);
    emit.createSub(*Fibs, 0, 0, 5);
    emit.createCall(*Fibs, "Fibs");
    emit.createLdacc(*Fibs, 2);
    emit.createAdd(*Fibs, 3, 2, 1);
    emit.createStacc(*Fibs, 3);
    emit.createRet(*Fibs);

    std::shared_ptr<Method::Method> pMain(new Method::Method(0, 5));

    emit.createMv(*pMain, 0, n);
    emit.createCall(*pMain, "Fibs");
    emit.createLdacc(*pMain, 2);
    emit.createPrint(*pMain, "fib: ", 2);
    emit.createRet(*pMain);

    std::unordered_map<std::string, std::shared_ptr<Method::Method>> methods {};
    methods["main"] = pMain;
    methods["Fibs"] = Fibs;
    Executor exec(methods);
    exec.simpleInterpreter("main");

};

int main()
{
    FibsRecursion(11);
    return 0;
}