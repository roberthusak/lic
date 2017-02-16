#include "MethodDefinition.h"

#include "Assembly.h"

using namespace gsl;

lic::MethodDefinition::MethodDefinition(Assembly& assembly, MetadataTable table, size_t rid, gsl::byte* row)
    : Metadata(assembly, table, rid, row)
{
}

lic::MethodDefinition::~MethodDefinition()
{
}

const char* lic::MethodDefinition::Name() const
{
    uint16_t index = *reinterpret_cast<uint16_t*>(this->row + 8);
    return reinterpret_cast<char*>(&this->assembly.stringStream[index]);
}
