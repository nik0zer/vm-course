#include "method.hh"
#include "executor.hh"

#include <stdexcept>

namespace Frame
{

void Method::addInstruction(Instr instr)
{
    instructionSet_.push_back(instr);
}

std::shared_ptr<Method> Method::getCleanCopy() const
{
    return std::make_shared<Method>(*this);
}

void Method::createMark(const MarkType mark)
{
    marks.emplace(mark, instructionSet_.size());
}

}