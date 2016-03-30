// GeneratorPrimeNumbers.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Generator.h"
#include <sstream>

using namespace std;

unsigned StringToInt(string const & numberStr)
{
	stringstream ss(numberStr);
	unsigned upperBound = 0;
	ss >> upperBound;
	return upperBound;
}

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		unsigned upperBound = StringToInt(argv[1]);
		if (upperBound > MAX_NUMBER)
		{
			cout << "Exceed the maximum permissible number" << endl;
			return 1;
		}
		auto primeNumberSet = GeneratePrimeNumbersSet(upperBound);
		for (auto const & primeNumber : primeNumberSet)
		{
			cout << primeNumber << endl;
		}
	}
    return 0;
}

