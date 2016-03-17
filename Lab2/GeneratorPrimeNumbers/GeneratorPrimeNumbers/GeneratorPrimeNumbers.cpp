// GeneratorPrimeNumbers.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Generator.h"

using namespace std;


int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		unsigned int upperBound = atoi(argv[1]);
		if (upperBound > MAX_NUMBER)
		{
			return 1;
		}
		auto primeNumberSet = GeneratePrimeNumbersSet(upperBound);
		for (auto const & iterator : primeNumberSet)
		{
			cout << iterator << endl;
		}
	}
    return 0;
}

