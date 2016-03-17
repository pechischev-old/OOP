#include "stdafx.h"
#include "../GeneratorPrimeNumbers/Generator.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(GeneratePrimeNumbersSet_function)
	BOOST_AUTO_TEST_CASE(no_prime_number)
	{
		std::set<unsigned int> primeSet = GeneratePrimeNumbersSet(1);
		BOOST_CHECK(primeSet.size() == 0);
	}

	BOOST_AUTO_TEST_CASE(SOME_PRIME_NUMBERS)
	{
		std::set<unsigned int> primeSet = GeneratePrimeNumbersSet(9);
		std::set<unsigned int> checkPrimeSet = { 2, 3, 5, 7 };
		BOOST_CHECK(primeSet == checkPrimeSet);
	}

	BOOST_AUTO_TEST_CASE(check_for_exceeding_the_maximum_permissible_number)
	{
		std::set<unsigned int> primeSet = GeneratePrimeNumbersSet(100000001);
		BOOST_CHECK(primeSet.size() == 0);
	}

	BOOST_AUTO_TEST_CASE(HUNDRED_MILLION_COUNT_OF_PRIME_NUMBERS)
	{
		std::set<unsigned int> primeSet = GeneratePrimeNumbersSet(100000000);
		BOOST_CHECK(primeSet.size() == 5761455);
	}
BOOST_AUTO_TEST_SUITE_END()