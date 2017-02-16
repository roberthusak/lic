#ifndef LIC_CLR_METADATA_FORMAT
#define LIC_CLR_METADATA_FORMAT

#include <array>

#define CLI_USUAL_HEADER_SIZE 0x48
#define CLI_HEADER_METADATA_RVA_OFFSET 0x10
#define CLI_HEADER_METADATA_SIZE_OFFSET 0x14

#define CLI_METADATA_HEADER_SIZE 0x20

#define CLI_STREAM_HEADER_OFFSET_OFFSET 0x0
#define CLI_STREAM_HEADER_SIZE_OFFSET 0x4
#define CLI_STREAM_HEADER_NAME_OFFSET 0x8

#define CLI_METADATA_STREAM_HEADER_HEAP_SIZES_OFFSET 0x6
#define CLI_METADATA_STREAM_HEADER_VALID_TABLES_OFFSET 0x8
#define CLI_METADATA_STREAM_HEADER_ROW_COUNTS_OFFSET 0x18

#define CLI_METADATA_TABLES_COUNT 45

// Defensive - at most 5 bits might be used to encode table in encoded token
#define CLI_RID_SIZE_TRESHOLD 0x07FF

namespace lic
{

enum class MetadataTable
{
    Module = 0x00,
    TypeRef = 0x01,
    TypeDef = 0x02,
    Field = 0x04,
    MethodDef = 0x06,
    Param = 0x08,
    InterfaceImpl = 0x09,
    MemberRef = 0x0A,
    Constant = 0x0B,
    CustomAttribute = 0x0C,
    FieldMarshal = 0x0D,
    DeclSecurity = 0x0E,
    ClassLayout = 0x0F,
    FieldLayout = 0x10,
    StandAloneSig = 0x11,
    EventMap = 0x12,
    Event = 0x14,
    PropertyMap = 0x15,
    Property = 0x17,
    MethodSemantics = 0x18,
    MethodImpl = 0x19,
    ModuleRef = 0x1A,
    TypeSpec = 0x1B,
    ImplMap = 0x1C,
    FieldRVA = 0x1D,
    Assembly = 0x20,
    AssemblyProcessor = 0x21,
    AssemblyOS = 0x22,
    AssemblyRef = 0x23,
    AssemblyRefProcessor = 0x24,
    AssemblyRefOS = 0x25,
    File = 0x26,
    ExportedType = 0x27,
    ManifestResource = 0x28,
    NestedClass = 0x29,
    GenericParam = 0x2A,
    MethodSpec = 0x2B,
    GenericParamConstraint = 0x2C
};

extern const std::array<size_t, CLI_METADATA_TABLES_COUNT> RowDefaultSizes;

}

#endif // !LIC_CLR_METADATA_FORMAT
