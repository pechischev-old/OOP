#include "stdafx.h"
#include "../Calculater/Calculator.h"

using namespace std;


bool VerifyLists(list<string> const & sourceList, list<string> const & reference)
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
		BOOST_CHECK(calculator.DefineVar("").GetError() != ErrorType::notError);
	}
	BOOST_AUTO_TEST_CASE(returns_false_if_the_variable_name_does_not_match_demand)
	{
		BOOST_CHECK(calculator.DefineVar("1abcd").GetError() != ErrorType::notError);
		BOOST_CHECK(calculator.DefineVar("_abcd").GetError() != ErrorType::notError);
	}
	BOOST_AUTO_TEST_CASE(returns_true_if_the_variable_is_set)
	{
		BOOST_CHECK(calculator.DefineVar("xyz").GetError() == ErrorType::notError);
		BOOST_CHECK(calculator.DefineVar("xyz3").GetError() == ErrorType::notError);
		BOOST_CHECK(calculator.DefineVar("xy_z").GetError() == ErrorType::notError);
	}
	BOOST_AUTO_TEST_CASE(cannot_set_variable_when_it_is_already_taken)
	{
		calculator.DefineVar("somevar");
		BOOST_CHECK(calculator.DefineVar("somevar").GetError() != ErrorType::notError);
	}

	BOOST_AUTO_TEST_CASE(can_set_the_value_of_an_existing_variable)
	{
		calculator.DefineVar("somevar");
		BOOST_CHECK(calculator.SetValue("somevar", 5).GetError() == ErrorType::notError);
		BOOST_CHECK_EQUAL(calculator.GetValue("somevar"), "5.00");
		BOOST_CHECK(calculator.SetValue("s", 5).GetError() == ErrorType::notError);
		BOOST_CHECK_EQUAL(calculator.GetValue("s"), "5.00");
	}
	BOOST_AUTO_TEST_CASE(can_set_the_value_when_it_the_variable_is_not_set)
	{
		BOOST_CHECK(calculator.SetValue("someVar", 5).GetError() == ErrorType::notError);
	}
	BOOST_AUTO_TEST_CASE(cannot_pass_the_value_of_another_variable_when_other_variable_is_not_determinate)
	{
		BOOST_CHECK(calculator.AssignVar("someVar", "somevar").GetError() != ErrorType::notError);
	}
	BOOST_AUTO_TEST_CASE(can_pass_the_value_of_another_variable_when_other_variable_is_determinate)
	{
		calculator.DefineVar("somevar");
		BOOST_CHECK(calculator.AssignVar("someVar", "somevar").GetError() == ErrorType::notError);
	}
	struct when_set_variables_ : SCalculator
	{
		when_set_variables_()
		{
			calculator.DefineVar("y");
			calculator.SetValue("x", 15);
			calculator.SetValue("z", -8);
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_set_variables, when_set_variables_)
		BOOST_AUTO_TEST_CASE(function_can_be_set_to_name_of_the_variable)
		{
			BOOST_CHECK(calculator.DefineFunction("SomeFunction", "x").GetError() == ErrorType::notError);
		}
		BOOST_AUTO_TEST_CASE(function_cannot_be_set_to_the_name_if_it_does_not_match_demand)
		{
			BOOST_CHECK(calculator.DefineFunction("2omeFunction", "x").GetError() != ErrorType::notError);
			BOOST_CHECK(calculator.DefineFunction("", "x").GetError() != ErrorType::notError);
		}
		BOOST_AUTO_TEST_CASE(function_takes_the_value_of_the_expression)
		{
			BOOST_CHECK(calculator.DefineFunction("SomeFunction1", "x", BinaryOperation::Div, "z").GetError() == ErrorType::notError);
			BOOST_CHECK(calculator.DefineFunction("SomeFunction2", "x", BinaryOperation::Add, "z").GetError() == ErrorType::notError);
			BOOST_CHECK(calculator.DefineFunction("SomeFunction3", "x", BinaryOperation::Substr, "z").GetError() == ErrorType::notError);
			BOOST_CHECK(calculator.DefineFunction("SomeFunction2", "y", BinaryOperation::Multiply, "z").GetError() == ErrorType::notError);
		}

		BOOST_AUTO_TEST_CASE(display_values_by_one_name_variable)
		{
			BOOST_CHECK_EQUAL(calculator.GetValue("z"), "-8.00");
			BOOST_CHECK_EQUAL(calculator.GetValue("y"), "nan");
			calculator.DefineFunction("SomeFunction2", "x", BinaryOperation::Add, "z");
			BOOST_CHECK_EQUAL(calculator.GetValue("SomeFunction2"), "7.00");
			calculator.DefineFunction("SomeFunction2", "y", BinaryOperation::Add, "z");
			BOOST_CHECK_EQUAL(calculator.GetValue("SomeFunction2"), "nan");
		}

		BOOST_AUTO_TEST_CASE(display_valyes_all_vars)
		{
			list<string> reference = {"x:15.00", "y:nan", "z:-8.00"};
			BOOST_CHECK(VerifyLists(calculator.DumpVars(), reference));
		}

		BOOST_AUTO_TEST_CASE(display_valyes_when_the_variables_are_not_declared)
		{
			CCalculator calc;
			BOOST_CHECK(calc.DumpVars().empty());
		}

		BOOST_AUTO_TEST_CASE(display_valyes_all_functions)
		{
			calculator.DefineFunction("Fn2", "x", BinaryOperation::Add, "z");
			calculator.DefineFunction("Fn", "y", BinaryOperation::Add, "z");
			calculator.DefineFunction("FnZ", "x", BinaryOperation::Multiply, "z");
			list<string> reference = { "Fn:nan", "Fn2:7.00", "FnZ:-120.00" };
			BOOST_CHECK(VerifyLists(calculator.DumpFns(), reference));
		}

		BOOST_AUTO_TEST_CASE(display_valyes_when_the_functions_are_not_declared)
		{
			CCalculator calc;
			BOOST_CHECK(calc.DumpFns().empty());
		}


	BOOST_AUTO_TEST_SUITE_END()

	void SetFibonacciSequence(CCalculator & calculator, unsigned const & number)
	{
		calculator.SetValue("v0", 0);
		calculator.SetValue("v1", 1);
		calculator.DefineFunction("fib0", "v0");
		calculator.DefineFunction("fib1", "v1");
		for (size_t i = 2; i <= number; ++i)
		{
			calculator.DefineFunction("fib" + to_string(i), "fib" + to_string(i - 2), BinaryOperation::Add, "fib" + to_string(i - 1));
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
		BOOST_CHECK(VerifyLists(calculator.DumpFns(), reference));
	}

BOOST_AUTO_TEST_SUITE_END()