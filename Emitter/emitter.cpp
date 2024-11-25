#include "emitter.hh"
#include "method.hh"
#include <sys/mman.h>

namespace Emitter
{

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

    // загрузить инструкции в буффер пропатчив инструкции джампа (в джампе заменить марк на высчитанный офсет) 
    // и кола (заменить марк функции на индекс функции найденный в векторе methods, 
    // если его там нет то добавить его туда) 

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

}