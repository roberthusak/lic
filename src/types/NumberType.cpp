#include "NumberType.h"

#include <sstream>

using namespace std;
using namespace lic;

lic::NumberType::NumberType()
{
}

NumberType& lic::NumberType::Instance()
{
    static NumberType instance;
    return instance;
}

std::string lic::NumberType::Name() const
{
    return "Int32";
}

std::string lic::NumberType::ToString(gsl::byte* data) const
{
    int32_t value = *reinterpret_cast<int32_t*>(data);

    stringstream ss;
    ss << value;

    return ss.str();
}

void lic::NumberType::PerformUnaryOp(Opcode op, gsl::byte * data) const
{
}

void lic::NumberType::PerformBinaryOp(Opcode op, gsl::byte * leftData, RuntimeType * rightType, gsl::byte * rightData) const
{
}
