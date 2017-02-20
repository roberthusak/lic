#include "EvaluationStack.h"

using namespace lic;

size_t lic::EvaluationStack::Size() const
{
    return this->stack.size();
}

void lic::EvaluationStack::Push(TypedValue value)
{
    this->stack.push_back(value);
}

TypedValue lic::EvaluationStack::Pop()
{
    auto top = this->stack.back();
    this->stack.pop_back();

    return top;
}

TypedValue& lic::EvaluationStack::Top()
{
    return this->stack.back();
}

void lic::EvaluationStack::PerformUnaryOp(Opcode op)
{
    this->stack.back().type->PerformUnaryOp(op, &this->stack.back().data[0]);
}

void lic::EvaluationStack::PerformBinaryOp(Opcode op)
{
    auto& leftOp = this->stack[this->stack.size() - 2];
    auto& rightOp = this->stack.back();

    leftOp.type->PerformBinaryOp(op, &leftOp.data[0], rightOp.type, &rightOp.data[0]);
    this->Pop();
}