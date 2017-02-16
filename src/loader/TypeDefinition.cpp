#include "TypeDefinition.h"

#include "Assembly.h"
#include "format/ClrMetadataFormat.h"

using namespace gsl;
using namespace lic;

lic::TypeDefinition::TypeDefinition(Assembly& assembly, MetadataTable table, size_t rid, gsl::byte* row)
    : Metadata(assembly, table, rid, row)
{
}

lic::TypeDefinition::~TypeDefinition()
{
}

const char* lic::TypeDefinition::Name() const
{
    uint16_t index = *reinterpret_cast<uint16_t*>(this->row + 4);
    return (char*)&this->assembly.stringStream[index];
}

const char * lic::TypeDefinition::Namespace() const
{
    uint16_t index = *reinterpret_cast<uint16_t*>(this->row + 6);
    return (char*)&this->assembly.stringStream[index];
}

const span<MethodDefinition> lic::TypeDefinition::Methods()
{
    uint16_t firstMethodRid = this->FirstMethodRid();
    if (firstMethodRid == 0)
    {
        return span<MethodDefinition>();
    }

    auto assemblyMethods = this->assembly.Methods();

    if (this->rid == this->assembly.metadataRowCounts[(size_t)MetadataTable::TypeDef])
    {
        // Last type in the table
        return assemblyMethods.subspan(firstMethodRid - 1);
    }
    else
    {
        // Otherwise are the methods delimited by the next type
        auto& nextType = this->assembly.Types()[this->rid];         // +1 -1
        size_t nextTypeFirstMethodRid = nextType.FirstMethodRid();

        return assemblyMethods.subspan(firstMethodRid - 1, nextTypeFirstMethodRid - firstMethodRid);
    }
}

size_t lic::TypeDefinition::FirstMethodRid()
{
    return *reinterpret_cast<uint16_t*>(this->row + 12);
}
