#ifndef LIC_METHOD_DEFINITION
#define LIC_METHOD_DEFINITION

#include <gsl/gsl>

#include "Metadata.h"

namespace lic
{

class MethodDefinition : Metadata
{
public:
    MethodDefinition(Assembly& assembly, MetadataTable table, size_t rid, gsl::byte* row);
    ~MethodDefinition();

    const char* Name() const;
    const gsl::byte* Code() const;
};

}

#endif // !LIC_METHOD_DEFINITION
