#include <iostream>
#include <sstream>

#include "interpreter/Interpreter.h"

using namespace std;
using namespace lic;

bool RunMethod(
    Interpreter& interpreter,
    stringstream& output,
    TypeDefinition& type,
    const string& methodName,
    const string& expectedReturn)
{
    // Find the selected method
    auto methods = type.Methods();
    auto methodIt = find_if(methods.begin(), methods.end(), [&methodName](auto& method) { return method.Name() == methodName; });
    interpreter.Run(*methodIt);

    string returned;
    output >> returned;
    output.clear();
    cout << "Method " << methodName << " returned " << returned << " (" << expectedReturn << " expected)...";

    if (returned == expectedReturn)
    {
        cout << "SUCCESS" << endl;
        return true;
    }
    else
    {
        cout << "FAIL" << endl;
        return false;
    }

}

int main(int argc, char* argv[])
{
    try
    {
        string assemblyPath = argv[1];
        string typeName = "Fibonacci";

        stringstream output, ignored;

        cout << "Loading the interpreter.." << endl;
        Interpreter interpreter(assemblyPath, cin, output, ignored);
        auto& assembly = interpreter.Assemblies()[0];

        // Find the tested type
        cout << "Searching for the tested class.." << endl;
        auto types = assembly.Types();
        auto& type = *find_if(types.begin(), types.end(), [&typeName](auto& type) { return type.Name() == typeName; });

        cout << "Running the methods.." << endl;
        bool success = true;
        success = success && RunMethod(interpreter, output, type, "FibSimple_0", "0");
        success = success && RunMethod(interpreter, output, type, "FibSimple_1", "1");
        success = success && RunMethod(interpreter, output, type, "FibSimple_2", "1");
        success = success && RunMethod(interpreter, output, type, "FibSimple_3", "2");
        success = success && RunMethod(interpreter, output, type, "Fib_5", "5");
        success = success && RunMethod(interpreter, output, type, "Fib_10", "55");
        success = success && RunMethod(interpreter, output, type, "Fib_15", "610");
        success = success && RunMethod(interpreter, output, type, "Fib_21", "10946");

        cout << endl;
        if (success)
        {
            cout << "All tests passed" << endl;
            return 0;
        }
        else
        {
            cout << "Tests not passed" << endl;
            return 1;
        }
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}