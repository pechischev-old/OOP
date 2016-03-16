#include "stdafx.h"
#include "../task3/MapProcess.h"


using namespace std;

BOOST_AUTO_TEST_SUITE(AddNewWordInDictionary_function)
	BOOST_AUTO_TEST_CASE(add_pair_words_in_dictionary)
	{
		Dictionary dict;
		string key = "cat";
		string value = "кот";
		BOOST_CHECK(AddNewWordInDictionary(dict, key, value) );
	}
	BOOST_AUTO_TEST_CASE(add_only_key_in_dictionary)
	{
		Dictionary dict;
		string key = "cat";
		string value = "";
		BOOST_CHECK(!AddNewWordInDictionary(dict, key, value) && dict.size() == 0);
	}
	BOOST_AUTO_TEST_CASE(add_only_value_in_dictionary)
	{
		Dictionary dict;
		string key = "";
		string value = "кот";
		BOOST_CHECK(!AddNewWordInDictionary(dict, key, value) && dict.size() == 0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AddNewWordInDictionary_function)
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