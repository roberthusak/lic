#include "CallStackFrame.h"

using namespace lic;

lic::CallStackFrame::CallStackFrame(MethodDefinition& method, gsl::span<TypedValue> args, Opcode* returnAddress)
    : method{ method }, args{ args.begin(), args.end() }, returnAddress{ returnAddress }
{
}

lic::CallStackFrame::CallStackFrame(MethodDefinition& method, TypedValue& thisRef, gsl::span<TypedValue> args, Opcode* returnAddress)
    : method{ method }, returnAddress{ returnAddress }
{
    this->args.push_back(thisRef);
    this->args.insert(this->args.end(), args.begin(), args.end());
}

MethodDefinition& lic::CallStackFrame::Method()
{
    return this->method;
}

TypedValue& lic::CallStackFrame::Arg(size_t index)
{
    return this->args[index];
}

TypedValue& lic::CallStackFrame::Local(size_t index)
{
    // Local variables are allocated on demand (zero initiated)
    if (index >= this->locals.size())
    {
        this->locals.resize(index + 1, TypedValue{});
    }

    return this->locals[index];
}

EvaluationStack& lic::CallStackFrame::Stack()
{
    return this->stack;
}

Opcode* lic::CallStackFrame::ReturnAddress() const
{
    return this->returnAddress;
}