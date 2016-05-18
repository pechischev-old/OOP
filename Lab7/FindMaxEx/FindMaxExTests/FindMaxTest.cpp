#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(FindMaxEx)

	BOOST_AUTO_TEST_CASE(can_not_find_the_max_value_when_the_vector_is_empty)
	{
		string maxValue;
		BOOST_CHECK(!FindMax(vector<string>(), maxValue, [](string const & lhs, string const &  rhs) {
															return lhs.length() < rhs.length(); }));
	}
	BOOST_AUTO_TEST_CASE(can_find_the_max_value_when_the_vector_numbers_is_initialized)
	{
		int maxValue = 0;
		vector<int> arr = {5, 48, 230, 97, 23, 97, 2};
		BOOST_CHECK(FindMax(arr, maxValue, [](int lhs, int rhs) {return lhs < rhs; }));
		BOOST_CHECK_EQUAL(maxValue, 230);
	}
	BOOST_AUTO_TEST_CASE(can_find_the_max_length_of_a_string_in_a_vector_of_strings)
	{
		string maxLenghtStr;
		vector<string> arr = { "some", "min", "max", "parallelepiped" };
		BOOST_CHECK(FindMax(arr, maxLenghtStr, [](string const & lhs, string const &  rhs) {
					return lhs.length() < rhs.length(); }));
		BOOST_CHECK_EQUAL(maxLenghtStr, "parallelepiped");
	}
	BOOST_AUTO_TEST_CASE(can_replace_the_existing_max_value)
	{
		float maxFloat = 555.f;
		vector<float> arr = { 54.3f, 548.f, -78.f, 98.f };
		BOOST_CHECK(FindMax(arr, maxFloat, [](float lhs, float rhs) {
			return lhs < rhs; }));
		BOOST_CHECK_EQUAL(maxFloat, 548.f);
	}
	BOOST_AUTO_TEST_CASE(can_replace_the_max_value)
	{
		float maxFloat = 555.f;
		vector<float> arr = { 54.3f };
		BOOST_CHECK(FindMax(arr, maxFloat, [](float lhs, float rhs) {
			return lhs < rhs; }));
		BOOST_CHECK_EQUAL(maxFloat, 54.3f);
	}
BOOST_AUTO_TEST_SUITE_END()