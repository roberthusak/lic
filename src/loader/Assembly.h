#ifndef LIC_ASSEMBLY
#define LIC_ASSEMBLY

#include <gsl/gsl>

#include "TypeDefinition.h"

namespace lic
{

class AssemblyLoader;

// We need to use it in the class definition below, hence the duplicity
constexpr size_t MetadataTablesCount = 45;

class Assembly
{
public:
    Assembly(size_t baseRva, std::unique_ptr<gsl::byte[]> &&data);
    ~Assembly();

    // Disable copying
    Assembly(const Assembly&) = delete;
    Assembly& operator=(const Assembly&) = delete;

    const gsl::span<TypeDefinition> Types();

private:
    friend class AssemblyLoader;


    size_t baseRva;
    std::unique_ptr<gsl::byte[]> data;

    gsl::span<gsl::byte> metadataStream;
    gsl::span<gsl::byte> stringStream;
    gsl::span<gsl::byte> userStringStream;
    gsl::span<gsl::byte> guidStream;
    gsl::span<gsl::byte> blobStream;

    std::array<size_t, MetadataTablesCount> metadataRowSizes;
    std::array<gsl::span<gsl::byte>, MetadataTablesCount> metadataTables;
};

}

#endif // !LIC_ASSEMBLY
