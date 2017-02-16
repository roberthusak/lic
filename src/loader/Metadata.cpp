#include "Metadata.h"

#include "Assembly.h"
#include "format/ClrMetadataFormat.h"

using namespace gsl;
using namespace lic;

lic::Metadata::Metadata(Assembly& assembly, MetadataTable table, size_t rid, gsl::byte* row)
    : assembly{ assembly }, table{ table }, rid{ rid }, row{ row }
{
}

lic::Metadata::~Metadata()
{
}
