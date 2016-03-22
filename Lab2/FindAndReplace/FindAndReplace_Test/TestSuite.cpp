#include "stdafx.h"
#include "..\FindAndReplace\MainProcess.h"
#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(Replace_function)
	BOOST_AUTO_TEST_CASE(returns_empty_string_when_subject_is_empty)
	{
		BOOST_CHECK(FindAndReplace("", "hello", "bye") == "");
	}
	BOOST_AUTO_TEST_CASE(returns_subject_when_text_to_search_is_empty)
	{
	
		BOOST_CHECK(FindAndReplace("Empty", "", "bye") == "Empty");
	}
	BOOST_AUTO_TEST_CASE(returns_subject_when_it_does_not_contain_search_string) 
	{
		BOOST_CHECK(FindAndReplace("Apple", "Microsoft", "Windows") == "Apple");
	}

	BOOST_AUTO_TEST_CASE(replace_all_entries_the_search_string_in_the_replacement_string)
	{
		BOOST_CHECK(FindAndReplace("What a beautiful day", "beautiful", "raing") == "What a raing day");
		BOOST_CHECK(FindAndReplace("This is an apple", "is", "IS") == "ThIS IS an apple");
		BOOST_CHECK(FindAndReplace("All cats like fish", "cats", "people") == "All people like fish");
		BOOST_CHECK(FindAndReplace("Girls like dancing", "Girls", "Boys") == "Boys like dancing");
		BOOST_CHECK(FindAndReplace("Cats ate birds", "s", "") == "Cat ate bird");
	}

BOOST_AUTO_TEST_SUITE_END()