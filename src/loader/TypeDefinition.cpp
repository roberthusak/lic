#include "TypeDefinition.h"

#include "Assembly.h"

lic::TypeDefinition::TypeDefinition(Assembly& assembly, gsl::byte* typeDefRow)
    : assembly{ assembly }, typeDefRow{ typeDefRow }
{
}

lic::TypeDefinition::~TypeDefinition()
{
}

const char* lic::TypeDefinition::Name() const
{
    uint16_t index = *reinterpret_cast<uint16_t*>(this->typeDefRow + 4);
    return (char*)&this->assembly.stringStream[index];
}

const char * lic::TypeDefinition::Namespace() const
{
    uint16_t index = *reinterpret_cast<uint16_t*>(this->typeDefRow + 6);
    return (char*)&this->assembly.stringStream[index];
}
