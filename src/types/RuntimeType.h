#ifndef LIC_RUNTIME_TYPE
#define LIC_RUNTIME_TYPE

#include <string>
#include <gsl/gsl>

#include <format/Opcodes.h>

namespace lic
{

class RuntimeType
{
public:
    virtual ~RuntimeType();

    virtual std::string Name() const = 0;
    virtual std::string ToString(gsl::byte* data) const = 0;

    virtual void PerformUnaryOp(Opcode op, gsl::byte* data) const;
    virtual void PerformBinaryOp(Opcode op, gsl::byte* leftData, RuntimeType* rightType, gsl::byte* rightData) const;

protected:
    RuntimeType();
};

}

#endif // !LIC_RUNTIME_TYPE
