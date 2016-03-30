#include "stdafx.h"
#include "../task3/MapProcess.h"


using namespace std;

BOOST_AUTO_TEST_SUITE(AddNewWordToDictionary_function)
	BOOST_AUTO_TEST_CASE(adds_non_empty_words_to_dict)
	{
		Dictionary dict;
		BOOST_CHECK(AddNewWordToDictionary(dict, "cat", "кот") );
	}
	BOOST_AUTO_TEST_CASE(cannot_add_empty_translation)
	{
		Dictionary dict;
		BOOST_CHECK(!AddNewWordToDictionary(dict, "cat", "") && dict.size() == 0);
	}
	BOOST_AUTO_TEST_CASE(cannot_add_empty_word)
	{
		Dictionary dict;
		BOOST_CHECK(!AddNewWordToDictionary(dict, "", "кот") && dict.size() == 0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FindValueByKey_function)
	BOOST_AUTO_TEST_CASE(return_value_by_finding_key)
	{
		Dictionary dict = { {"cat", "кот"}, {"dog", "собака"},{ "red", "красный" } };
		BOOST_CHECK(FindValueByKey(dict, "dog") == "собака");
	}
	BOOST_AUTO_TEST_CASE(canot_find_value_in_empty_dictionary)
	{
		Dictionary dict;
		BOOST_CHECK(!(FindValueByKey(dict, "dog") == "собака"));
	}
	BOOST_AUTO_TEST_CASE(find_values_in_dictionary_when_key_is_recorded_in_different_register)
	{
		Dictionary dict;
		BOOST_CHECK(!(FindValueByKey(dict, "dOg") == "собака"));
		BOOST_CHECK(!(FindValueByKey(dict, "BalL") == "мяч"));
		BOOST_CHECK(!(FindValueByKey(dict, "LOW") == "низкий"));
	}
BOOST_AUTO_TEST_SUITE_END()

void WriteStringToFile()
{
	ofstream fout("dict.txt");
	string writeStr = R"***(The Red Square:Красная площадь";
		cat:кот
		new:новый
		news:новости
		ball:мяч
		mouse:мышь
		task:задача
		low:низкий)***";
	fout << writeStr;
}

BOOST_AUTO_TEST_SUITE(FillDictionary_function)
	BOOST_AUTO_TEST_CASE(fill_dictionary_from_file)
	{
		remove("dict.txt");
		WriteStringToFile();
		Dictionary dict;
		FillDictionary("dict.txt", dict);
		BOOST_CHECK(dict.size() != 0);
		remove("dict.txt");
	}
	BOOST_AUTO_TEST_CASE(fill_dictionary_from_empty_file)
	{
		remove("empty.txt");
		Dictionary dict;
		FillDictionary("empty.txt", dict);
		BOOST_CHECK(dict.size() == 0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(WriteNewWordsToFile_function)
	BOOST_AUTO_TEST_CASE(write_empty_dictionary_in_file)
	{
		remove("empty.txt");
		Dictionary dict;
		WriteNewWordsToFile(dict, "empty.txt");
		BOOST_CHECK(!IsFileNotEmpty("empty.txt"));
		remove("empty.txt");
	}
	BOOST_AUTO_TEST_CASE(write_dictionary_in_file)
	{
		remove("out.txt");
		Dictionary dict = { { "cat", "кот" },{ "dog", "собака" },{ "red", "красный" } };
		WriteNewWordsToFile(dict, "out.txt");
		Dictionary check;
		FillDictionary("out.txt", check);
		BOOST_CHECK(check == dict);
		remove("out.txt");
	}
BOOST_AUTO_TEST_SUITE_END()