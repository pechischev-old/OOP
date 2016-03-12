#include "Generator.h"
#include <algorithm>

using namespace std;



set<int> GeneratePrimeNumbersSet(int upperBound)
{
	vector<bool> isSingleNumbers(upperBound, true);
	set<int> primeNumbersSet;
	int  primeNumber = 2;
	SieveEratosthenes(upperBound, isSingleNumbers);
	for_each(isSingleNumbers.begin() + 2, isSingleNumbers.end(), [&](bool isSingleNumber) {
		if (isSingleNumber)
		{
			primeNumbersSet.emplace(primeNumber);
		}
		++primeNumber;
	});
	return primeNumbersSet;
}

void SieveEratosthenes(int upperBound, std::vector<bool> & isSingleNumbers)
{
	int primeNumber = 2; 
	while (primeNumber * primeNumber <= upperBound)
	{
		int i = primeNumber * primeNumber; 
		if (isSingleNumbers[primeNumber])
		{
			while (i < upperBound)
			{
				isSingleNumbers[i] = false;
				i += primeNumber;
			}
		}
		++primeNumber; 
	}
}