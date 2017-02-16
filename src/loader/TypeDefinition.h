#ifndef LIC_TYPE_DEFINITION
#define LIC_TYPE_DEFINITION

#include <gsl/gsl>

namespace lic
{

class Assembly;

class TypeDefinition
{
public:
    TypeDefinition(Assembly& assembly, gsl::byte* typeDefRow);
    ~TypeDefinition();

    const char* Name() const;
    const char* Namespace() const;

private:
    Assembly& assembly;
    gsl::byte* typeDefRow;
};

}

#endif // !LIC_TYPE_DEFINITION
