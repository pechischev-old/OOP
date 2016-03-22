#include "stdafx.h"
#include "../GeneratorPrimeNumbers/Generator.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(GeneratePrimeNumbersSet_function)
	BOOST_AUTO_TEST_CASE(return_empty_set)
	{
		BOOST_CHECK(GeneratePrimeNumbersSet(1).size() == 0);
	}

	BOOST_AUTO_TEST_CASE(return_not_empty_set_when_the_number_complies)
	{
		std::set<unsigned int> checkPrimeSet = { 2, 3, 5, 7 };
		BOOST_CHECK(GeneratePrimeNumbersSet(9) == checkPrimeSet);

		checkPrimeSet = { 2, 3, 5, 7, 11, 13, 17, 19 };
		BOOST_CHECK(GeneratePrimeNumbersSet(20) == checkPrimeSet);
		checkPrimeSet = { 2 };
		BOOST_CHECK(GeneratePrimeNumbersSet(2).size() == 0);
	}

	BOOST_AUTO_TEST_CASE(return_empty_set_when_exceeding_the_maximum_permissible_number)
	{
		BOOST_CHECK(GeneratePrimeNumbersSet(100000001).size() == 0);
	}

	BOOST_AUTO_TEST_CASE(return_set_at_maximum)
	{
		BOOST_CHECK(GeneratePrimeNumbersSet(100000000).size() == 5761455);
	}
BOOST_AUTO_TEST_SUITE_END()