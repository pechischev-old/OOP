#include "stdafx.h"
#include "../task_5/ExpandTemplate.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ExpandTemplate_function)
	BOOST_AUTO_TEST_CASE(insert_user_name_and_week_day_in_the_string)
	{
		map<string, string> params;
		params["%USER_NAME%"] = "Ivan Petrov";
		params["{WEEK_DAY}"] = "Friday";
		string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";

		BOOST_CHECK(ExpandTemplate(tpl, params) == "Hello, Ivan Petrov. Today is Friday.");
	}

BOOST_AUTO_TEST_SUITE_END()