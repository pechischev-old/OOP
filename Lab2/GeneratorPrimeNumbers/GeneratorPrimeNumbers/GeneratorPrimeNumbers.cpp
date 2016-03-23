// GeneratorPrimeNumbers.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Generator.h"
#include <sstream>

using namespace std;


int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		stringstream ss(argv[1]);
		unsigned upperBound;
		ss >> upperBound;
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

