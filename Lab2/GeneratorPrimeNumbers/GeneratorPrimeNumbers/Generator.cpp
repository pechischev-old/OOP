#include "Generator.h"
#include <algorithm>

using namespace std;

const int FIRST_PRIME_NUMBER = 2;


set<unsigned> GeneratePrimeNumbersSet(unsigned upperBound)
{
	if ( FIRST_PRIME_NUMBER <= upperBound && upperBound <= MAX_NUMBER)
	{
		vector<bool> isSingleNumbers(upperBound + 1, true);
		isSingleNumbers[0] = false;
		isSingleNumbers[1] = false;
		
		SieveEratosthenes(upperBound, isSingleNumbers);

		unsigned primeNumber = 0;
		set<unsigned> primeNumbersSet;
		for (auto isSingleNumber : isSingleNumbers) 
		{
			if (isSingleNumber)
			{
				primeNumbersSet.insert(primeNumber);
			}
			++primeNumber;
		}
		return primeNumbersSet;
	}
	return {};
}

void SieveEratosthenes(unsigned const & upperBound, std::vector<bool> & isSingleNumbers)
{
	for (size_t primeNumber = FIRST_PRIME_NUMBER; primeNumber * primeNumber <= upperBound; ++primeNumber)
	{
		if (isSingleNumbers[primeNumber])
		{
			for (size_t i = primeNumber * primeNumber; i <= upperBound; i += primeNumber)
			{
				isSingleNumbers[i] = false;
			}
		}
	}
}