#include "RuntimeType.h"

using namespace std;
using namespace lic;

lic::RuntimeType::RuntimeType()
{
}

lic::RuntimeType::~RuntimeType()
{
}

void lic::RuntimeType::PerformUnaryOp(Opcode op, gsl::byte* data) const
{
    throw runtime_error("Operation not implemented");
}

void lic::RuntimeType::PerformBinaryOp(Opcode op, gsl::byte * leftData, RuntimeType * rightType, gsl::byte * rightData) const
{
    throw runtime_error("Operation not implemented");
}