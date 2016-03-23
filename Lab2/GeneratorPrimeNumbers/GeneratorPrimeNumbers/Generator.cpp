#include "Generator.h"
#include <algorithm>

using namespace std;

const int FIRST_PRIME_NUMBER = 2;


set<unsigned int> GeneratePrimeNumbersSet(unsigned int upperBound)
{
	if ( FIRST_PRIME_NUMBER <= upperBound && upperBound <= MAX_NUMBER)
	{
		vector<bool> isSingleNumbers(upperBound + 1, true);
		isSingleNumbers[0] = false;
		isSingleNumbers[1] = false;
		
		SieveEratosthenes(upperBound, isSingleNumbers);

		unsigned int  primeNumber = 0;
		set<unsigned int> primeNumbersSet;
		for (auto isSingleNumber : isSingleNumbers) 
		{
			if (isSingleNumber)
			{
				primeNumbersSet.insert(primeNumber);
			}
			++primeNumber;
		}

		//int  primeNumber = FIRST_PRIME_NUMBER;
		/*for_each(isSingleNumbers.begin() + FIRST_PRIME_NUMBER, isSingleNumbers.end(), [&](bool isSingleNumber) {
			if (isSingleNumber)
			{
				primeNumbersSet.insert(primeNumber);
			}
			++primeNumber;
		});*/
		return primeNumbersSet;
	}
	return {};
}

void SieveEratosthenes(unsigned int const & upperBound, std::vector<bool> & isSingleNumbers)
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