#include "AssemblyLoader.h"

#include <fstream>
#include <iomanip>

using namespace std;

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
