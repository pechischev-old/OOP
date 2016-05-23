#include "stdafx.h"
#include "../StringList/StringList.h"

using namespace std;

struct EmptyStringList
{
	CStringList list;
};

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)
	BOOST_AUTO_TEST_SUITE(when_created)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(list.GetSize(), 0u);
			BOOST_CHECK(list.IsEmpty());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_appeding_a_string)
		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.GetSize();
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
			BOOST_CHECK(!list.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.Append("goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "goodbye");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.Append("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_last_element)
		{
			list.Append("begin");
			list.Append("end");
			auto it = list.end();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct was_filled_ : public EmptyStringList
	{
		was_filled_()
		{
			list.Append("first");
			list.Append("second");
			list.Append("third");
		}
		
	};
	/*BOOST_FIXTURE_TEST_SUITE(initialised_list, was_filled_)
		BOOST_AUTO_TEST_CASE(insert_string_to_the_list)
		{
			auto it = list.begin();
			list.Insert("hello", it);

		}
	BOOST_AUTO_TEST_SUITE_END()*/
	

BOOST_AUTO_TEST_SUITE_END()