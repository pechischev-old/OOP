#include "stdafx.h"
#include "../String/MyString.h"


using namespace std;

struct my_string_can_be_declared_by_default_
{
	CMyString myString;
};

BOOST_FIXTURE_TEST_SUITE(before_declared_string, my_string_can_be_declared_by_default_)

	BOOST_AUTO_TEST_CASE(default_pointer_to_an_array_of_char_strings_is_nullptr)
	{
		BOOST_CHECK(myString.GetStringData()[0] == '\0');
	}

	BOOST_AUTO_TEST_CASE(default_length_of_the_string_is_equal_to_zero)
	{
		BOOST_CHECK(myString.GetLength() == 0u);
	}

	BOOST_AUTO_TEST_CASE(my_str_have_a_null_char_on_end)
	{
		BOOST_CHECK(myString.GetStringData()[myString.GetLength()] == '\0');
	}

	BOOST_AUTO_TEST_CASE(attempt_to_take_substring_if_empty_str_returns_exception)
	{
		BOOST_REQUIRE_THROW(auto substr = myString.SubString(0u, 30u), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(can_clear_empty_string)
	{
		BOOST_CHECK_NO_THROW(myString.Clear());
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(can_create_my_string_without_null_char)
{
	CMyString myStr("\0");
	BOOST_CHECK_EQUAL(myStr.GetStringData(), "\0");
	BOOST_CHECK_EQUAL(myStr.GetLength(), 0u);
}

BOOST_AUTO_TEST_CASE(my_string_without_null_char_in_center_str_will_be_cut)
{
	CMyString myStr("Test\0 String");
	BOOST_CHECK_EQUAL(myStr.GetStringData()[myStr.GetLength()], '\0');
	BOOST_CHECK_EQUAL(myStr.GetLength(), 4u);
}


void VerifyString(CMyString const & str, size_t lenght, std::string const & reference)
{
	BOOST_CHECK_EQUAL(str.GetLength(), lenght);
	BOOST_CHECK_EQUAL(str.GetStringData(), reference);
}

BOOST_AUTO_TEST_SUITE(CreatingAnObjectOfClassLines)

	BOOST_AUTO_TEST_CASE(can_set_string_by_default)
	{
		CMyString str;
		VerifyString(str, 0u, "");
	}
	BOOST_AUTO_TEST_CASE(can_set_string_with_other_string)
	{
		CMyString str("4 cats");
		VerifyString(str, 6u, "4 cats");
	}
	BOOST_AUTO_TEST_CASE(can_initialize_a_string_of_a_certain_length)
	{
		CMyString str("3 dogs", 9);
		VerifyString(str, 9u, "3 dogs");
	}
	BOOST_AUTO_TEST_CASE(can_copy_the_string)
	{
		CMyString str("house and sky", 15);
		CMyString str1(str);
		VerifyString(str1, 15u, "house and sky");
	}
	BOOST_AUTO_TEST_CASE(can_move_the_string_where_movable_srring_to_become_empty)
	{
		CMyString str("dark sky");
		CMyString str1(move(str));
		VerifyString(str1, 8u, "dark sky");
		VerifyString(str, 0u, "");
	}
	BOOST_AUTO_TEST_CASE(can_initialize_a_string_data_from_the_string_Standard_Library)
	{
		std::string str("can initialize");
		CMyString str1(str);
		VerifyString(str1, str.size(), "can initialize");
	}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_CASE(can_get_a_substring)
{
	CMyString str("123456");
	BOOST_CHECK_EQUAL(str.SubString(3, 2).GetStringData(),  "45");
	BOOST_CHECK_EQUAL(str.SubString(0, 6).GetStringData(), "123456");
}


