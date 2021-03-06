﻿// task1tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../task1/Rational.h"
#include <iostream>

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}



/*
Рациональное число:
равно нулю по умолчанию (0/1)
может быть созданно из целого в формате (n / 1)
может быть задано с указанием числителя и знаменателя
хранится в нормализованном виде
*/

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		VerifyRational(CRational(), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
	{
		VerifyRational(CRational(10), 10, 1);
		VerifyRational(CRational(-10), -10, 1);
		VerifyRational(CRational(0), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
	{
		VerifyRational(CRational(5, 2), 5, 2);
		VerifyRational(CRational(-5, 2), -5, 2);
		VerifyRational(CRational(5, -2), -5, 2);
		VerifyRational(CRational(-5, -2), 5, 2);
	}
	BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
	{
		VerifyRational(CRational(6, 8), 3, 4);
		VerifyRational(CRational(6, -8), -3, 4);
		VerifyRational(CRational(-6, 8), -3, 4);
		VerifyRational(CRational(-6, -8), 3, 4);
		VerifyRational(CRational(-10, 20), -1, 2);
	}
	BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
	{
		BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	}




//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
// Возвращает отношение числителя и знаменателя в виде числа double
// Пример использования:
//	CRational r(3, 5)
//	cout << r.ToDouble(); // Должно вывести 0.6
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(can_get_numeric_in_double_format)
	{
		BOOST_CHECK_EQUAL(CRational(3, 5).ToDouble(), 0.6);
		BOOST_CHECK_EQUAL(CRational(1, 3).ToDouble(), 0.33333333333333333);
		BOOST_CHECK_EQUAL(CRational(0, 3).ToDouble(), 0);
		BOOST_CHECK_EQUAL(CRational().ToDouble(), 0);
		BOOST_CHECK_EQUAL(CRational(-1, 3).ToDouble(), -0.33333333333333333);
	}	



//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
// Указание: см. материалы к лекции
// Пример использования:
//	const CRational r1(3, 5);
//	CRational r2 = -r1; // r2 должно стать -3/5
//	assert(r2.GetNumerator(), -3);
//	assert(r2.GetDenominator(), 5);
//	CRational r3 = +r2; // r3 также равно -3/5
//	assert(r3.GetNumerator(), -3);
//	assert(r3.GetDenominator(), 5);
// Унарный минус возвращает раицональное число без знака
// Унарный плюс возвращает рациональное число, равное текущему
// Реализация не должна допускать операции вроде:
//  -someRational = someOtherRational;
//	+someRational = someOtherRational;
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(can_available_number_that_is_the_same_or_opposite_meaningfully)
	{
		const CRational r1(3, 5);
		CRational r2 = -r1; // r2 должно стать -3/5
		BOOST_CHECK_EQUAL(r2.GetNumerator(), -3);
		BOOST_CHECK_EQUAL(r2.GetDenominator(), 5);
		CRational r3 = +r2; // r3 также равно -3/5
		BOOST_CHECK_EQUAL(r3.GetNumerator(), -3);
		BOOST_CHECK_EQUAL(r3.GetDenominator(), 5);
	}


//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
// Возвращает результат сложения двух рациональных чисел, 
//	рационального числа с целым, целого числа с рациональным.
//	(1/2) + (1/6) = (2/3)
//	(1/2) + 1     = (3/2)
//	1 + (1/2)     = (3/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(can_add_up_with_other_rational_number)
	{
		VerifyRational(CRational(1, 2) + CRational(1, 6), 2, 3);
		VerifyRational(CRational(1, 2) + CRational(1, 3), 5, 6);
		VerifyRational(CRational(1, 5) + CRational(-2, 3), -7, 15);
	}
	BOOST_AUTO_TEST_CASE(can_add_up_with_integer_number)
	{
		VerifyRational(CRational(1, 2) + 1, 3, 2);
		VerifyRational(1 + CRational(1, 2), 3, 2);
	}


//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
// Возвращает разность двух рациональных чисел, 
//	рационального числа и целого, либо целого числа и рационального:
//	(1/2) - (1/6) = (1/3)
//	(1/2) - 1     = (-1/2)
//	1 - (1/2)     = (1/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(substraction_rational_values)
	{
		VerifyRational(CRational(1, 2) - CRational(1, 6), 1, 3);
		VerifyRational(CRational(6, 8) - CRational(2, 8), 1, 2);
		VerifyRational(CRational(-6, 8) - CRational(2, 8), -1, 1);
		VerifyRational(CRational(-6, 8) - CRational(-2, 8), -1, 2);
		VerifyRational(CRational(6, 8) - CRational(-2, 8), 1, 1);
		VerifyRational(1 - CRational(1, 2), 1, 2);
		VerifyRational(CRational(1, 2) - 1, -1, 2);
	}


//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
// Выполняет увеличение рационального числа на величину второго рационального,
//	либо целого числа:
//	(1/2) += (1/6)  → (2/3)
//	(1/2) += 1      → (3/2)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(has_adding_assigment_operator)
	{
		CRational number(2, 7);
		VerifyRational(number += number, 4, 7);
		VerifyRational(CRational(1, 2) += CRational(1, 6), 2, 3);
		VerifyRational(CRational(1, 2) += 1, 3, 2);
		VerifyRational(CRational(1, 2) += 0, 1, 2);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
// Выполняет уменьшение рационального числа на величину второго рационального либо целого числа :
// (1/2) -= (1/6)  → (1/3)
// (1/2) -= 1      → (-1/2)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(operator_minus_assignment_substract_from_rational)
	{
		CRational rat1(3, 5);
		CRational rat2(-3, 7);
		rat1 -= rat2;
		VerifyRational(rat1, 36, 35);
		BOOST_CHECK(rat1.GetNumerator() != -36);
		BOOST_CHECK(rat1.GetDenominator() != 39);
		rat1 = CRational(2, 3);
		rat2 = CRational(3, 2);
		rat1 -= rat2;
		VerifyRational(rat1, -5, 6);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
// Возвращает результат произведения рациональных чисел, 
//	рационального и целого, либо целого и рационального :
//	(1/2) * (2/3) = (1/3)
//	(1/2) * (-3)  = (-3/2)
//	(7*2) / 3     = (14/3)
//////////////////////////////////////////////////////////////////////////
	
	BOOST_AUTO_TEST_CASE(can_multiply_rational_numbers) 
	{
		VerifyRational(CRational(1, 2) * CRational(2, 3), 1, 3);
		VerifyRational(CRational(1, 2) * (-3), -3, 2);
		VerifyRational(10 * CRational(3, 5), 6, 1);

		VerifyRational(CRational(1, 2) * CRational(2, 4), 1, 4);
		VerifyRational(CRational(1, 2) * 2, 1, 1);
		VerifyRational(2 * CRational(1, 2), 1, 1);
		VerifyRational(0 * CRational(1, 2), 0, 1);
		VerifyRational(-3 * CRational(1, 2), -3, 2);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
// Возвращает частное двух рациональных чисел, 
//	рационального и целого, целого и рационального :
//	(1/2) ⁄ (2/3) = (3/4)
//	(1/2) ⁄ 5     = (1/10)
//	7 ⁄ (2/3)     = (21/2)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(can_divide_rational_numbers)
	{
		VerifyRational(CRational(1, 2) / CRational(2, 3), 3, 4);
		VerifyRational(CRational(1, 2) / 5, 1, 10);
		VerifyRational(7 / CRational(2, 3), 21, 2);
	}

	BOOST_AUTO_TEST_CASE(can_not_be_divide_rational_on_zero)
	{
		BOOST_REQUIRE_THROW(auto answer = CRational(1, 2) / CRational(0), std::invalid_argument::exception);

		BOOST_REQUIRE_THROW(auto answer = CRational(1, 2) / CRational(0, 1), std::invalid_argument::exception);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
// Умножает значение первого рационального числа на другое рациональное, 
//	либо целое:
//	(1/2) *= (2/3) → (1/3)
//	(1/2) *= 3     → (3/2)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(can_multiply_the_value_of_the_first_rational_number_to_another)
	{
		CRational rat1(1, 2);
		rat1 *= CRational(2, 3);
		VerifyRational(rat1, 1, 3);

		CRational rat2(1, 2);
		rat2 *= 3;
		VerifyRational(rat2, 3, 2);
		rat2 *= 0;
		VerifyRational(rat2, 0, 1);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
// Делит первое рациональное число на другое рациональное, 
//	либо целое:
//	(1/2) /= (2/3) → (3/4)
//	(1/2) /= 3     → (1/6)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(can_divide_the_value_of_the_first_rational_number_to_another)
	{
		CRational rat1(1, 2);
		rat1 /= CRational(2, 3);
		VerifyRational(rat1, 3, 4);

		CRational rat2(1, 2);
		rat2 /= 3;
		VerifyRational(rat2, 1, 6);

		BOOST_REQUIRE_THROW(CRational(45, 7) /= 0, std::invalid_argument::exception);
	}	


//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
// Проверяют равенство (и неравенство) двух рациональных чисел, 
//	целого и рационального, рационального и целого:
//	(1/2) == (1/2) → true
//	(4/1) == 4     → true
//	3 == (3/1)     → true
//	(1/2) != (2/3) → true
//	(1/2) != 7     → true
//	3 != (2/3)     → true
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(can_check_equality_and_inequality_of_two_rational_numbers)
	{
		BOOST_CHECK(CRational(1, 2) == CRational(1, 2));
		BOOST_CHECK(CRational(4, 1) == 4);
		BOOST_CHECK(3 == CRational(3, 1));

		BOOST_CHECK(CRational(1, 2) != CRational(2, 3));
		BOOST_CHECK(CRational(1, 2) != 7);
		BOOST_CHECK(3 != CRational(2, 3));
	}


//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
// Сравнивают два рациональных числа, рациональное с целым, 
//	целое с рациональным:
//	(1/2) >= (1/3) → true
//	(1/2) <= (1/3) → false
//	(3/1) > 2      → true
//	(1/2) < 7      → true
//	3 <= (7/2)     → true
//	3 >= (8/2)     → false
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(can_compare_two_rational_numbers)
	{
		BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
		BOOST_CHECK(! (CRational(1, 2) <= CRational(1, 3)));

		BOOST_CHECK(CRational(3, 1) > 2);
		BOOST_CHECK(CRational(1, 2) < 7);
		BOOST_CHECK(3 <= CRational(7, 2));
		BOOST_CHECK(!(3 >= CRational(8, 2)));
	}



//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//	std::ostream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////

	void VerifyOutputStream(CRational const & rational, std::string const & reference)
	{
		std::ostringstream strm;
		strm << rational;
		BOOST_CHECK_EQUAL(strm.str(), reference);
	}

	BOOST_AUTO_TEST_CASE(rational_number_can_be_displayed_in_the_output_stream)
	{
		VerifyOutputStream(CRational(1, 2), "1/2");
		VerifyOutputStream(CRational(-8, 45), "-8/45");
		VerifyOutputStream(0, "0/1");
	}


//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//	std::istream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////

	void VerifyInputStream(CRational const & rational, std::string const & inputStr)
	{
		std::istringstream strm(inputStr);
		CRational gettingRational;
		strm >> gettingRational;
		VerifyRational(gettingRational, rational.GetNumerator(), rational.GetDenominator());
	}

	BOOST_AUTO_TEST_CASE(rational_number_can_be_obtained_from_the_input_stream)
	{
		VerifyInputStream(CRational(1, 2), "1/2");
		VerifyInputStream(CRational(-8, 45), "-8/45");
		VerifyInputStream(0, "0/1");
		VerifyInputStream(-8, "-8/1");
	}

	void VerifyCompoundFraction(CRational const & rational, int const & integerPart, CRational const & rationalReference)
	{
		std::pair<int, CRational> compoundFraction = rational.ToCompoundFraction();
		BOOST_CHECK_EQUAL(compoundFraction.first, integerPart);
		VerifyRational(compoundFraction.second, rationalReference.GetNumerator(), rationalReference.GetDenominator());
	}

	BOOST_AUTO_TEST_CASE(rational_numbers_can_be_represented_in_the_form_of_compound_fraction)
	{
		VerifyCompoundFraction(CRational(-10, 4), -2, CRational(-2, 4));
		VerifyCompoundFraction(CRational(9, 4), 2, CRational(1, 4));
		VerifyCompoundFraction(CRational(2, 4), 0, CRational(1, 2)); 
		VerifyCompoundFraction(CRational(287, 1), 287, CRational(0, 1));
	}

BOOST_AUTO_TEST_SUITE_END()
