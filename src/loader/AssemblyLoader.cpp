#include "AssemblyLoader.h"

#include <fstream>
#include <iomanip>

#include "format/PeFormat.h"

using namespace std;
using namespace gsl;
using namespace lic;

void lic::DumpBinaryFile(const string& filepath, ostream& out)
{
    ifstream file(filepath, ios::binary);

    int startPosition = 0;
    const int blockSize = 16;
    char buffer[blockSize];

    while (!file.eof())
    {
        fill(buffer, buffer + blockSize, '\0');
        file.read(buffer, blockSize);

        out << hex << setw(8) << setfill('0') << startPosition << "  ";

        for (size_t i = 0; i < blockSize; i++)
        {
            int intValue = (int)(unsigned char)buffer[i];
            out << hex << setw(2) << setfill('0') << intValue << ' ';

            if (i + 1 == blockSize / 2)
            {
                out << ' ';
            }

            if (!isprint(intValue))
            {
                // Replace non-printable characters by dots
                buffer[i] = '.';
            }
            else if (isspace(intValue))
            {
                // Turn any tabs and newlines into spaces to not polute the output later
                buffer[i] = ' ';
            }
        }

        out << ' ' << string(buffer, blockSize) << endl;

        startPosition += blockSize;
    }
}

lic::AssemblyLoader::AssemblyLoader()
{
}

lic::AssemblyLoader::~AssemblyLoader()
{
}

span<Assembly> lic::AssemblyLoader::Assemblies()
{
    // TODO: Refactor when multiple assemblies are supported
    if (this->assemblies.empty())
    {
        return span<Assembly>();
    }
    else
    {
        return make_span(this->assemblies[0], 1);
    }
}

lic::Assembly& lic::AssemblyLoader::LoadAssembly(const string& filepath)
{
    if (!this->assemblies.empty())
    {
        throw exception("Multiple assembly loading not supported");
    }

    ifstream file(filepath, ios::binary | ios::ate);
    size_t fileSize = (size_t)file.tellg();

    // TODO: Determine dynamically by parsing header
    size_t sectionRva = PE_USUAL_TEXT_SECTION_RVA;
    size_t sectionFileOffset = PE_USUAL_TEXT_SECTION_OFFSET;

    file.seekg(sectionFileOffset);
    size_t assemblySize = fileSize - sectionFileOffset;

    auto bytes = make_unique<byte[]>(assemblySize);
    file.read((char*)bytes.get(), assemblySize);

    this->assemblies.push_back(make_unique<Assembly>(sectionRva, move(bytes)));
    auto& assembly = *this->assemblies.back().get();

    return assembly;
}
