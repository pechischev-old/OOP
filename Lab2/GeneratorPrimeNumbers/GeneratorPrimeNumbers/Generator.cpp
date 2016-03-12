#include "Generator.h"

using namespace std;



set<int> GeneratePrimeNumbersSet(int upperBound)
{
	vector<bool> isSingleNumbers(upperBound, true);
	set<int> primeNumbersSet;

	SieveEratosthenes(upperBound, isSingleNumbers);

	for (int primeNumber = 2; primeNumber < upperBound; ++primeNumber)
	{
		if (isSingleNumbers[primeNumber])
		{
			primeNumbersSet.emplace(primeNumber);
		}
	}
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