#include "stdafx.h"
#include "../Calculater/Calculator.h"

using namespace std;

bool VerefyLists(list<string> const & sourceList, list<string> const & reference)
{
	return sourceList == reference;
};

struct SCalculator
{
	CCalculator calculator;
};

BOOST_FIXTURE_TEST_SUITE(Calculator, SCalculator)
	BOOST_AUTO_TEST_CASE(returns_false_if_the_variable_is_not_set)
	{
		BOOST_CHECK(!calculator.SetVar("").IsSuccesful());
	}
	BOOST_AUTO_TEST_CASE(returns_false_if_the_variable_name_does_not_match_demand)
	{
		BOOST_CHECK(!calculator.SetVar("1abcd").IsSuccesful());
		BOOST_CHECK(!calculator.SetVar("_abcd").IsSuccesful());
	}
	BOOST_AUTO_TEST_CASE(returns_true_if_the_variable_is_set)
	{
		BOOST_CHECK(calculator.SetVar("xyz").IsSuccesful());
		BOOST_CHECK(calculator.SetVar("xyz3").IsSuccesful());
		BOOST_CHECK(calculator.SetVar("xy_z").IsSuccesful());
	}
	BOOST_AUTO_TEST_CASE(cannot_set_variable_when_it_is_already_taken)
	{
		calculator.SetVar("somevar");
		BOOST_CHECK(!calculator.SetVar("somevar").IsSuccesful());
	}

	BOOST_AUTO_TEST_CASE(can_set_the_value_of_an_existing_variable)
	{
		calculator.SetVar("somevar");
		BOOST_CHECK(calculator.SetLet("somevar", 5).IsSuccesful());
		BOOST_CHECK_EQUAL(calculator.GetValueLet("somevar"), 5);
		BOOST_CHECK(calculator.SetLet("s", 5).IsSuccesful());
		BOOST_CHECK_EQUAL(calculator.GetValueLet("s"), 5);
	}
	BOOST_AUTO_TEST_CASE(can_set_the_value_when_it_the_variable_is_not_set)
	{
		BOOST_CHECK(calculator.SetLet("someVar", 5).IsSuccesful());
	}
	BOOST_AUTO_TEST_CASE(cannot_pass_the_value_of_another_variable_when_other_variable_is_not_determinate)
	{
		BOOST_CHECK(!calculator.SetLet("someVar", "somevar").IsSuccesful());
	}
	BOOST_AUTO_TEST_CASE(can_pass_the_value_of_another_variable_when_other_variable_is_determinate)
	{
		calculator.SetVar("somevar");
		BOOST_CHECK(calculator.SetLet("someVar", "somevar").IsSuccesful());
	}
	struct when_set_variables_ : SCalculator
	{
		when_set_variables_()
		{
			calculator.SetVar("y");
			calculator.SetLet("x", 15);
			calculator.SetLet("z", -8);
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_set_variables, when_set_variables_)
		BOOST_AUTO_TEST_CASE(function_can_be_set_to_name_of_the_variable)
		{
			BOOST_CHECK(calculator.SetFunction("SomeFunction", "x").IsSuccesful());
		}
		BOOST_AUTO_TEST_CASE(function_cannot_be_set_to_the_name_if_it_does_not_match_demand)
		{
			BOOST_CHECK(!calculator.SetFunction("2omeFunction", "x").IsSuccesful());
			BOOST_CHECK(!calculator.SetFunction("", "x").IsSuccesful());
		}
		BOOST_AUTO_TEST_CASE(function_takes_the_value_of_the_expression)
		{
			BOOST_CHECK(calculator.SetFunction("SomeFunction1", "x", "/", "z").IsSuccesful());
			BOOST_CHECK(calculator.SetFunction("SomeFunction2", "x", "+", "z").IsSuccesful());
			BOOST_CHECK(calculator.SetFunction("SomeFunction3", "x", "-", "z").IsSuccesful());
			BOOST_CHECK(calculator.SetFunction("SomeFunction2", "y", "*", "z").IsSuccesful());
		}

		BOOST_AUTO_TEST_CASE(display_values_by_one_name_variable)
		{
			BOOST_CHECK_EQUAL(calculator.Print("z"), "-8.00");
			BOOST_CHECK_EQUAL(calculator.Print("y"), "nan");
			calculator.SetFunction("SomeFunction2", "x", "+", "z");
			BOOST_CHECK_EQUAL(calculator.Print("SomeFunction2"), "7.00");
			calculator.SetFunction("SomeFunction2", "y", "+", "z");
			BOOST_CHECK_EQUAL(calculator.Print("SomeFunction2"), "nan");
		}

		BOOST_AUTO_TEST_CASE(display_valyes_all_vars)
		{
			list<string> reference = {"x:15.00", "y:nan", "z:-8.00"};
			BOOST_CHECK(VerefyLists(calculator.GetVars(), reference));
		}

		BOOST_AUTO_TEST_CASE(display_valyes_when_the_variables_are_not_declared)
		{
			CCalculator calc;
			BOOST_CHECK(calc.GetVars().empty());
		}

		BOOST_AUTO_TEST_CASE(display_valyes_all_functions)
		{
			calculator.SetFunction("Fn2", "x", "+", "z");
			calculator.SetFunction("Fn", "y", "+", "z");
			calculator.SetFunction("FnZ", "x", "*", "z");
			list<string> reference = { "Fn:nan", "Fn2:7.00", "FnZ:-120.00" };
			BOOST_CHECK(VerefyLists(calculator.GetFns(), reference));
		}

		BOOST_AUTO_TEST_CASE(display_valyes_when_the_functions_are_not_declared)
		{
			CCalculator calc;
			BOOST_CHECK(calc.GetFns().empty());
		}


	BOOST_AUTO_TEST_SUITE_END()

	void SetFibonacciSequence(CCalculator & calculator, unsigned const & number)
	{
		calculator.SetLet("v0", 0);
		calculator.SetLet("v1", 1);
		calculator.SetFunction("fib0", "v0");
		calculator.SetFunction("fib1", "v1");
		for (size_t i = 2; i <= number; ++i)
		{
			calculator.SetFunction("fib" + to_string(i), "fib" + to_string(i - 2), "+", "fib" + to_string(i - 1));
		}
	}

	BOOST_AUTO_TEST_CASE(calculate_Fibonacci_sequence)
	{
		list<string> reference = { "fib0:0.00",
			"fib1:1.00",
			"fib2:1.00",
			"fib3:2.00",
			"fib4:3.00",
			"fib5:5.00",
			"fib6:8.00"
		};
		SetFibonacciSequence(calculator, 6);
		BOOST_CHECK(VerefyLists(calculator.GetFns(), reference));
	}

BOOST_AUTO_TEST_SUITE_END()