#include "Interpreter.h"

using namespace std;
using namespace lic;

lic::Interpreter::Interpreter(const std::string& assembly, std::istream & in, std::ostream & out)
    : in{ in }, out{ out }
{
    this->loader.LoadAssembly(assembly);
}

gsl::span<Assembly> lic::Interpreter::Assemblies()
{
    return this->loader.Assemblies();
}

void lic::Interpreter::Run(MethodDefinition& method)
{
    // TODO
    this->out << "Running method " << method.Name() << "..." << endl;
}
