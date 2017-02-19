#ifndef LIC_NUMBER_TYPE
#define LIC_NUMBER_TYPE

#include "RuntimeType.h"

namespace lic
{

// TODO: Make generic and inherit actual types
class NumberType : public RuntimeType
{
public:
    virtual std::string Name() const;
    virtual std::string ToString(gsl::byte* data) const;

    virtual void PerformUnaryOp(Opcode op, gsl::byte* data) const;
    virtual void PerformBinaryOp(Opcode op, gsl::byte* leftData, RuntimeType* rightType, gsl::byte* rightData) const;

	static void StoreConstant(int32_t val, gsl::byte* data);

    static NumberType& Instance();
private:
    NumberType();
};

}

#endif // !LIC_NUMBER_TYPE