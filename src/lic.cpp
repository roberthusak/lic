#include <iostream>
#include <algorithm>

#include "interpreter/Interpreter.h"

using namespace std;
using namespace lic;

int main(int argc, char* argv[])
{
    // TODO: Allow to pass as arguments
    string assemblyPath = "C:\\Users\\husak\\OneDrive\\skola\\fit\\run\\lic\\samples\\Basic\\bin\\Debug\\netstandard1.4\\Basic.dll";
    string typeName = "Arithmetic";
    string methodName = "AddSimple";

    Interpreter interpreter(assemblyPath, cin, cout, cerr);
    auto& assembly = interpreter.Assemblies()[0];

    // Dump the contents of the assembly
    for (auto& type : assembly.Types())
    {
        cout << type.Namespace() << '.' << type.Name() << endl;

        for (auto& method : type.Methods())
        {
            cout << '\t' << method.Name() << "(...)" << endl;
        }
    }

    cout << endl;

    // Find the selected type
    auto types = assembly.Types();
    auto typeIt = find_if(types.begin(), types.end(), [&typeName](auto& type) { return type.Name() == typeName; });
    if (typeIt == types.end())
    {
        cerr << "Type " << typeName << " not found" << endl;
        return 1;
    }

    // Find the selected method
    auto methods = typeIt->Methods();
    auto methodIt = find_if(methods.begin(), methods.end(), [&methodName](auto& method) { return method.Name() == methodName; });
    if (methodIt == methods.end())
    {
        cerr << "Method " << methodName << " on type " << typeName << " not found" << endl;
        return 1;
    }

    // Run the method
    interpreter.Run(*methodIt);

    return 0;
}
