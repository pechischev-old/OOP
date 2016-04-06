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
	BOOST_AUTO_TEST_CASE(returns_false_if_the_variable_name_does_not_match_demand)
	{
		BOOST_CHECK(!calculator.SetVar("1abcd"));
		BOOST_CHECK(!calculator.SetVar("_abcd"));
	}
	BOOST_AUTO_TEST_CASE(returns_true_if_the_variable_is_set)
	{
		BOOST_CHECK(calculator.SetVar("xyz"));
		BOOST_CHECK(calculator.SetVar("xyz3"));
		BOOST_CHECK(calculator.SetVar("xy_z"));
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
	struct when_set_variables_ : SCalculator
	{
		when_set_variables_()
		{
			calculator.SetVar("y0");
			calculator.SetLet("x0", 15);
			calculator.SetLet("z0", -8);
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_set_variables, when_set_variables_)
		BOOST_AUTO_TEST_CASE(function_can_be_set_to_name_of_the_variable)
		{
			BOOST_CHECK(calculator.SetFunction("SomeFunction", "x0"));
		}
		BOOST_AUTO_TEST_CASE(function_cannot_be_set_to_the_name_if_it_does_not_match_demand)
		{
			BOOST_CHECK(!calculator.SetFunction("2omeFunction", "x0"));
			BOOST_CHECK(!calculator.SetFunction("", "x0"));
		}
		BOOST_AUTO_TEST_CASE(function_takes_the_value_of_the_expression)
		{
			BOOST_CHECK(calculator.SetFunction("SomeFunction1", "x0", "/", "z0"));
			BOOST_CHECK(calculator.SetFunction("SomeFunction2", "x0", "+", "z0"));
			BOOST_CHECK(calculator.SetFunction("SomeFunction3", "x0", "-", "z0"));
			BOOST_CHECK(calculator.SetFunction("SomeFunction2", "y0", "*", "z0"));
		}

		BOOST_AUTO_TEST_CASE(display_values_by_one_name_variable)
		{
			BOOST_CHECK_EQUAL(calculator.Print("z0"), "-8.000000");
			BOOST_CHECK_EQUAL(calculator.Print("y0"), "nan");
			calculator.SetFunction("SomeFunction2", "x0", "+", "z0");
			BOOST_CHECK_EQUAL(calculator.Print("SomeFunction2"), "7.000000");
			calculator.SetFunction("SomeFunction2", "y0", "+", "z0");
			BOOST_CHECK_EQUAL(calculator.Print("SomeFunction2"), "nan");
		}

		bool VerefyLists(list<string> const & sourceList, list<string> const & reference)
		{
			return sourceList == reference;
		};

		BOOST_AUTO_TEST_CASE(display_valyes_all_vars)
		{
			list<string> reference = {"x0:15.000000", "y0:nan", "z0:-8.000000"};
			BOOST_CHECK(VerefyLists(calculator.PrintVars(), reference));
		}

		BOOST_AUTO_TEST_CASE(display_valyes_when_the_variables_are_not_declared)
		{
			CCalculator calc;
			BOOST_CHECK(calc.PrintVars().empty());
		}

		BOOST_AUTO_TEST_CASE(display_valyes_all_functions)
		{
			calculator.SetFunction("Fn2", "x0", "+", "z0");
			calculator.SetFunction("Fn", "y0", "+", "z0");
			calculator.SetFunction("FnZ", "x0", "*", "z0");
			list<string> reference = { "Fn:nan", "Fn2:7.000000", "FnZ:-120.000000" };
			BOOST_CHECK(VerefyLists(calculator.PrintFns(), reference));
		}

		BOOST_AUTO_TEST_CASE(display_valyes_when_the_functions_are_not_declared)
		{
			CCalculator calc;
			BOOST_CHECK(calc.PrintFns().empty());
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()