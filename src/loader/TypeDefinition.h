#ifndef LIC_TYPE_DEFINITION
#define LIC_TYPE_DEFINITION

#include <gsl/gsl>

#include "Metadata.h"

namespace lic
{

class MethodDefinition;

class TypeDefinition : Metadata
{
public:
    TypeDefinition(Assembly& assembly, MetadataTable table, size_t rid, gsl::byte* row);
    ~TypeDefinition();

    const char* Name() const;
    const char* Namespace() const;
    const gsl::span<MethodDefinition> Methods();

    size_t FirstMethodRid();
private:
};

}

#endif // !LIC_TYPE_DEFINITION
