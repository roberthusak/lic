#ifndef LIC_ASSEMBLY_LOADER
#define LIC_ASSEMBLY_LOADER

#include <iostream>
#include <string>
#include <vector>

#include "Assembly.h"

namespace lic
{

// Helper function for debugging purposes
void DumpBinaryFile(const std::string& filepath, std::ostream& out);

class AssemblyLoader
{
public:
    AssemblyLoader();
    ~AssemblyLoader();

    // Disable copying
    AssemblyLoader(const AssemblyLoader&) = delete;
    AssemblyLoader& operator=(const AssemblyLoader&) = delete;

    Assembly& LoadAssembly(const std::string& filepath);

private:
    std::vector<std::unique_ptr<Assembly>> assemblies;
};

}

#endif // !LIC_ASSEMBLY_LOADER
