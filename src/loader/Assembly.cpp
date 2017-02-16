#include "Assembly.h"

#include <cstring>

#include "format/ClrMetadataFormat.h"

using namespace std;
using namespace gsl;

byte* ProcessStreamHeader(byte* start, byte* metadataHeaderPos, span<byte>& streamSpan, const char* streamName)
{
    uint32_t offset = *reinterpret_cast<uint32_t*>(start + CLI_STREAM_HEADER_OFFSET_OFFSET);
    uint32_t size = *reinterpret_cast<uint32_t*>(start + CLI_STREAM_HEADER_SIZE_OFFSET);
    char* name = reinterpret_cast<char*>(start + CLI_STREAM_HEADER_NAME_OFFSET);

    if (strcmp(name, streamName) != 0)
    {
        throw exception("Invalid CLI stream name");
    }

    streamSpan = make_span(metadataHeaderPos + offset, size);

    // Round the string length (including terminal '\0') to the 4 byte grid
    size_t nameLen = strlen(name) + 1;
    size_t roundedNameLen = (nameLen / 4) * 4 + ((nameLen % 4 != 0) ? 4 : 0);

    return start + CLI_STREAM_HEADER_NAME_OFFSET + roundedNameLen;
}

lic::Assembly::Assembly(size_t baseRva, unique_ptr<byte[]>&& data)
    : baseRva{ baseRva }, data{ move(data) }
{
    size_t metadataRva = *reinterpret_cast<size_t*>(&this->data[CLI_HEADER_METADATA_RVA_OFFSET]);

    // Stream headers don't have uniform size
    byte* metadataHeaderPos = this->data.get() + metadataRva - baseRva;
    byte* streamHeaderPos = metadataHeaderPos + CLI_METADATA_HEADER_SIZE;
    streamHeaderPos = ProcessStreamHeader(streamHeaderPos, metadataHeaderPos, this->metadataStream, "#~");
    streamHeaderPos = ProcessStreamHeader(streamHeaderPos, metadataHeaderPos, this->stringStream, "#Strings");
    streamHeaderPos = ProcessStreamHeader(streamHeaderPos, metadataHeaderPos, this->userStringStream, "#US");
    streamHeaderPos = ProcessStreamHeader(streamHeaderPos, metadataHeaderPos, this->guidStream, "#GUID");
    streamHeaderPos = ProcessStreamHeader(streamHeaderPos, metadataHeaderPos, this->blobStream, "#Blob");

    // #~ header is right after the stream headers
    byte* metadataStreamHeaderPos = &*this->metadataStream.begin();
    if (metadataStreamHeaderPos != streamHeaderPos)
    {
        throw exception("Error in parsing stream headers");
    }

    if (metadataStreamHeaderPos[CLI_METADATA_STREAM_HEADER_HEAP_SIZES_OFFSET] != (byte)0)
    {
        throw exception("Streams indexed by 4 bytes not supported");
    }

    // Assume the 2 byte variant for each key (if there are too many records, an error will be raised later)
    this->metadataRowSizes = RowDefaultSizes;

    uint64_t tablePresentMask = *reinterpret_cast<uint64_t*>(metadataStreamHeaderPos + CLI_METADATA_STREAM_HEADER_VALID_TABLES_OFFSET);
    uint32_t* rowCountIt = reinterpret_cast<uint32_t*>(metadataStreamHeaderPos + CLI_METADATA_STREAM_HEADER_ROW_COUNTS_OFFSET);

    for (size_t i = 0; i < CLI_METADATA_TABLES_COUNT; i++)
    {
        if (tablePresentMask & ((uint64_t)1 << i))
        {
            this->metadataRowCounts[i] = *(rowCountIt++);

            if (this->metadataRowCounts[i] > CLI_RID_SIZE_TRESHOLD)
            {
                throw exception("Tables indexed by 4 bytes not supported");
            }
            else if (this->metadataRowCounts[i] == 0)
            {
                throw exception("Invalid zero size of table");
            }
            else if (this->metadataRowSizes[i] == 0)
            {
                throw exception("Existing records in undefined table");
            }
        }
        else
        {
            this->metadataRowCounts[i] = 0;
        }
    }

    // We have proceeded to the tables, now create direct references to them
    byte* currentTablePos = reinterpret_cast<byte*>(rowCountIt);

    for (size_t i = 0; i < CLI_METADATA_TABLES_COUNT; i++)
    {
        if (this->metadataRowCounts[i] > 0)
        {
            size_t tableLen = this->metadataRowCounts[i] * this->metadataRowSizes[i];
            this->metadataTables[i] = make_span(currentTablePos, tableLen);

            currentTablePos += tableLen;
        }
        else
        {
            this->metadataTables[i] = span<byte>();
        }
    }

    // FIXME
    //if (currentTablePos != &*this->metadataStream.begin() + this->metadataStream.length())
    //{
    //    throw exception("Error in processing metadata tables");
    //}
}

lic::Assembly::~Assembly()
{
}

const gsl::span<lic::TypeDefinition> lic::Assembly::Types()
{
    if (this->types.empty())
    {
        size_t rowSize = this->metadataRowSizes[(size_t)MetadataTable::TypeDef];
        auto table = this->metadataTables[(size_t)MetadataTable::TypeDef];
        
        for (auto tableIt = table.begin(); tableIt < table.end(); tableIt += rowSize)
        {
            this->types.emplace_back((Assembly&)*this, &*tableIt);
        }
    }

    return make_span(this->types);
}
