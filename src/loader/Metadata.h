#ifndef LIC_METADATA_DEFINITION
#define LIC_METADATA_DEFINITION

#include <gsl/gsl>

#include "format/ClrMetadataFormat.h"

namespace lic
{

class Assembly;

class Metadata
{
public:
    Metadata(Assembly& assembly, MetadataTable table, size_t rid, gsl::byte* row);
    ~Metadata();

protected:
    Assembly& assembly;
    MetadataTable table;
    size_t rid;
    gsl::byte* row;
};

}

#endif // !LIC_METADATA_DEFINITION
