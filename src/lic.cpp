#include <iostream>

#include "loader/AssemblyLoader.h"

using namespace std;
using namespace lic;

int main(int argc, char* argv[])
{
    // TODO: Find the path automatically and independently of the absolute location
    AssemblyLoader loader;
    auto& assembly = loader.LoadAssembly("C:\\Users\\husak\\OneDrive\\skola\\fit\\run\\lic\\samples\\Basic\\bin\\Debug\\netstandard1.4\\Basic.dll");

    for (auto& type : assembly.Types())
    {
        cout << type.Namespace() << '.' << type.Name() << endl;
    }

    return 0;
}
