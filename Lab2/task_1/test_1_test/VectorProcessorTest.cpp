#include "stdafx.h"
#include "..\task_1\VectorProcessor.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

// Функция ProcessVector
BOOST_AUTO_TEST_SUITE(ProcessVector_function)

	// Создает пустой вектор из пустого вектора
	BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
	{
		vector<double> emptyVector;
		ProcessVector(emptyVector);
		BOOST_CHECK(emptyVector.empty());
	}

	// не изменяет содержимое вектора, который не содержит отрицательных чисел
	BOOST_AUTO_TEST_CASE(does_not_change_vector_containing_no_negative_numbers)
	{
		vector<double> numbers = { 4, 0, 3 };
		auto copy(numbers); 
		ProcessVector(numbers);
		BOOST_CHECK(numbers == copy);
	}

	// при обработке вектора с одним положительным числом
	BOOST_AUTO_TEST_SUITE(when_processing_a_vector_with_one_positive_number)
		BOOST_AUTO_TEST_CASE(should_add_this_number_to_each_element)
		{
			vector<double> numbers = { -1, 3.5 };
			ProcessVector(numbers);

			BOOST_CHECK(VectorsAreEqual(numbers,{ (-1 * -3.5), (3.5) }	));
		}
	BOOST_AUTO_TEST_SUITE_END()

	// при обработке вектора с несколькими отрицательных элементами
	BOOST_AUTO_TEST_SUITE(when_processing_a_vector_with_several_negative_elements)
		BOOST_AUTO_TEST_CASE(should_add_their_average_to_each_element)
		{
			vector<double> numbers = { -1, 1, 2, 3, -0.5, 0 };
			ProcessVector(numbers);

			const double multiply = -1 * 3;
			BOOST_CHECK(VectorsAreEqual(numbers,{ (-1 * multiply), (1), (2), (3), (-0.5 * multiply), (0) } ));
		}		
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
