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

void lic::NumberType::PerformUnaryOp(Opcode op, gsl::byte* data) const
{
    int32_t& val = *reinterpret_cast<int32_t*>(data);

    switch (op)
    {
        case lic::Opcode::Neg:
            val = -val;
            break;

        default:
            RuntimeType::PerformUnaryOp(op, data);
    }
}

void lic::NumberType::PerformBinaryOp(Opcode op, gsl::byte * leftData, RuntimeType* rightType, gsl::byte * rightData) const
{
    int32_t& left = *reinterpret_cast<int32_t*>(leftData);
    int32_t& right = *reinterpret_cast<int32_t*>(rightData);

    switch (op)
    {
        case lic::Opcode::Add:
            left += right;
            break;
        case lic::Opcode::Sub:
            left -= right;
            break;
        case lic::Opcode::Mul:
            left *= right;
            break;
        case lic::Opcode::Div:
            left /= right;
            break;
        case lic::Opcode::Rem:
            left %= right;
            break;

        default:
            RuntimeType::PerformBinaryOp(op, leftData, rightType, rightData);
    }
}

void lic::NumberType::StoreConstant(int32_t val, gsl::byte* data)
{
	*reinterpret_cast<int32_t*>(data) = val;
}
