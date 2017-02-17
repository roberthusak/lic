#ifndef LIC_CALL_STACK_FRAME
#define LIC_CALL_STACK_FRAME

#include <stack>
#include <gsl/gsl>

#include "format/Opcodes.h"
#include "loader/MethodDefinition.h"
#include "EvaluationStack.h"

namespace lic
{

class CallStackFrame
{
public:
    CallStackFrame(MethodDefinition& method, gsl::span<TypedValue> args, Opcode* returnAddress);
    CallStackFrame(MethodDefinition& method, TypedValue& thisRef, gsl::span<TypedValue> args, Opcode* returnAddress);

    MethodDefinition& Method();
    TypedValue& Arg(size_t index);
    TypedValue& Local(size_t index);
    EvaluationStack& Stack();
    Opcode* ReturnAddress() const;

private:
    MethodDefinition& method;
    std::vector<TypedValue> args;
    std::vector<TypedValue> locals;
    EvaluationStack stack;
    Opcode* returnAddress;
};

}

#endif // !LIC_CALL_STACK_FRAME

