#ifndef LIC_EVALUATION_STACK
#define LIC_EVALUATION_STACK

#include <vector>

#include "types/RuntimeType.h"

namespace lic
{

constexpr size_t MaxValueSize = 8;

struct TypedValue
{
    RuntimeType* type;
    std::array<gsl::byte, MaxValueSize> data;
};

class EvaluationStack
{
public:
    void Push(TypedValue value);
    TypedValue Pop();
    TypedValue& Top();

    void PerformUnaryOp(Opcode op);
    void PerformBinaryOp(Opcode op);

private:
    std::vector<TypedValue> stack;
};

}

#endif // !LIC_EVALUATION_STACK

