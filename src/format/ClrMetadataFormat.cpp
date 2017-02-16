#include "ClrMetadataFormat.h"

using namespace std;

//const size_t RowDefaultSizes[CLI_METADATA_TABLES_COUNT]
const array<size_t, CLI_METADATA_TABLES_COUNT> lic::RowDefaultSizes
{
    10,	    // 0x00 Module
    6,	    // 0x01 TypeRef
    14,	    // 0x02 TypeDef
    0,	    // 0x03 ???
    6,      // 0x04 Field
    0,      // 0x05 ???
    14,     // 0x06 MethodDef
    0,      // 0x07 ???
    6,      // 0x08 Param
    4,      // 0x09 InterfaceImpl
    6,      // 0x0A MemberRef
    6,      // 0x0B Constant
    6,      // 0x0C CustomAttribute
    4,      // 0x0D FieldMarshal
    6,      // 0x0E DeclSecurity
    8,      // 0x0F ClassLayout
    6,      // 0x10 FieldLayout
    2,      // 0x11 StandAloneSig
    4,      // 0x12 EventMap
    0,      // 0x13 ???
    6,      // 0x14 Event
    4,      // 0x15 PropertyMap
    0,      // 0x16 ???
    6,      // 0x17 Property
    6,      // 0x18 MethodSemantics
    6,      // 0x19 MethodImpl
    2,      // 0x1A ModuleRef
    2,      // 0x1B TypeSpec
    8,      // 0x1C ImplMap
    6,      // 0x1D FieldRVA
    0,      // 0x1E ???
    0,      // 0x1F ???
    22,     // 0x20 Assembly
    4,      // 0x21 AssemblyProcessor
    12,     // 0x22 AssemblyOS
    20,     // 0x23 AssemblyRef
    6,      // 0x24 AssemblyRefProcessor
    14,     // 0x25 AssemblyRefOS
    8,      // 0x26 File
    14,     // 0x27 ExportedType
    12,     // 0x28 ManifestResource
    4,      // 0x29 NestedClass
    8,      // 0x2A GenericParam
    4,      // 0x2B MethodSpec
    4       // 0x2C GenericParamConstraint
};
