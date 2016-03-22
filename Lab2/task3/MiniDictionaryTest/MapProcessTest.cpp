#include "stdafx.h"
#include "../task3/MapProcess.h"


using namespace std;

BOOST_AUTO_TEST_SUITE(AddNewWordInDictionary_function)
	BOOST_AUTO_TEST_CASE(add_pair_words_in_dictionary)
	{
		Dictionary dict;
		BOOST_CHECK(AddNewWordInDictionary(dict, "cat", "кот") );
	}
	BOOST_AUTO_TEST_CASE(add_only_key_in_dictionary)
	{
		Dictionary dict;
		BOOST_CHECK(!AddNewWordInDictionary(dict, "cat", "") && dict.size() == 0);
	}
	BOOST_AUTO_TEST_CASE(add_only_value_in_dictionary)
	{
		Dictionary dict;
		BOOST_CHECK(!AddNewWordInDictionary(dict, "", "кот") && dict.size() == 0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FindValueOnKey_function)
	BOOST_AUTO_TEST_CASE(find_value_on_key)
	{
		Dictionary dict = { {"cat", "кот"}, {"dog", "собака"},{ "red", "красный" } };
		BOOST_CHECK(FindValueOnKey(dict, "dog") == "собака");
	}
	BOOST_AUTO_TEST_CASE(find_value_in_empty_dictionary)
	{
		Dictionary dict;
		BOOST_CHECK(!(FindValueOnKey(dict, "dog") == "собака"));
	}
	BOOST_AUTO_TEST_CASE(find_values_in__dictionary_when_key_is_recorded_in_different_register)
	{
		Dictionary dict;
		BOOST_CHECK(!(FindValueOnKey(dict, "dOg") == "собака"));
		BOOST_CHECK(!(FindValueOnKey(dict, "BalL") == "мяч"));
		BOOST_CHECK(!(FindValueOnKey(dict, "LOW") == "низкий"));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FillDictionary_function)
	BOOST_AUTO_TEST_CASE(fill_dictionary_from_file)
	{
		Dictionary dict;
		FillDictionary("dict.txt", dict);
		BOOST_CHECK(dict.size() != 0);
	}
	BOOST_AUTO_TEST_CASE(fill_dictionary_from_empty_file)
	{
		Dictionary dict;
		FillDictionary("empty.txt", dict);
		BOOST_CHECK(dict.size() == 0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(WriteNewWordsInFile_function)
	BOOST_AUTO_TEST_CASE(write_empty_dictionary_in_file)
	{
		Dictionary dict;
		WriteNewWordsInFile(dict, "empty.txt");
		BOOST_CHECK(!IsFileNotEmpty("empty.txt"));
	}
	BOOST_AUTO_TEST_CASE(write_dictionary_in_file)
	{
		Dictionary dict = { { "cat", "кот" },{ "dog", "собака" },{ "red", "красный" } };
		WriteNewWordsInFile(dict, "out.txt");
		BOOST_CHECK(IsFileNotEmpty("out.txt"));
	}
BOOST_AUTO_TEST_SUITE_END()