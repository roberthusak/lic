#include <iostream>

#include "loader\AssemblyLoader.h"

using namespace std;
using namespace lic;

int main (int argc, char* argv[])
{
	// TODO: Find the path automatically and independently of the absolute location
	DumpBinaryFile("C:\\Users\\husak\\OneDrive\\skola\\fit\\run\\lic\\samples\\Basic\\bin\\Debug\\netstandard1.4\\Basic.dll", cout);

	return 0;
}
