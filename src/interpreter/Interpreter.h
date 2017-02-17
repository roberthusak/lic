#ifndef LIC_INTERPRETER
#define LIC_INTERPRETER

#include <gsl/gsl>

#include "loader/AssemblyLoader.h"

namespace lic
{

class Interpreter
{
public:
    Interpreter(const std::string& assembly, std::istream& in, std::ostream& out);

    gsl::span<Assembly> Assemblies();

    void Run(MethodDefinition& method);

private:
    std::istream& in;
    std::ostream& out;

    AssemblyLoader loader;
};

}

#endif // !LIC_INTERPRETER
