#include "stdafx.h"
#include "../Calculater/Calculator.h"

using namespace std;


struct SCalculator
{
	CCalculator calculator;
};

BOOST_FIXTURE_TEST_SUITE(Calculator, SCalculator)
	BOOST_AUTO_TEST_CASE(returns_false_if_the_variable_is_not_set)
	{
		BOOST_CHECK(!calculator.SetVar(""));
	}
	BOOST_AUTO_TEST_CASE(returns_true_if_the_variable_is_set)
	{
		BOOST_CHECK(calculator.SetVar("xyz"));
	}
	BOOST_AUTO_TEST_CASE(cannot_set_variable_when_it_is_already_taken)
	{
		calculator.SetVar("somevar");
		BOOST_CHECK(!calculator.SetVar("somevar"));
	}

	BOOST_AUTO_TEST_CASE(can_set_the_value_of_an_existing_variable)
	{
		calculator.SetVar("somevar");
		BOOST_CHECK(calculator.SetLet("somevar", 5));
	}
	BOOST_AUTO_TEST_CASE(can_set_the_value_when_it_the_variable_is_not_set)
	{
		BOOST_CHECK(calculator.SetLet("someVar", 5));
	}
	BOOST_AUTO_TEST_CASE(can_pass_the_value_of_another_variable)
	{
		BOOST_CHECK(calculator.SetLet("someVar", "somevar"));
	}

BOOST_AUTO_TEST_SUITE_END()