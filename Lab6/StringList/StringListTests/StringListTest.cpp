#include "stdafx.h"
#include <vector>
#include <string>
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
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
			BOOST_CHECK(!list.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.PushBack("goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "goodbye");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.PushBack("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_last_element)
		{
			list.PushBack("begin");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(after_add_a_string_to_front)
		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.GetSize();
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetFrontElement_method)
		{
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			list.PushFront("goodbye");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "goodbye");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.PushFront("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetFrontElement()));
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct was_filled_ : public EmptyStringList
	{
		was_filled_()
		{
			list.PushBack("first");
			list.PushBack("second");
			list.PushBack("third");
		}
		std::vector<std::string> expectedString = { "first", "second", "third" };
	};
	BOOST_FIXTURE_TEST_SUITE(initialised_list, was_filled_)
		BOOST_AUTO_TEST_CASE(can_go_through_the_list_using_the_operators_start_and_end)
		{
			size_t index = 0;
			for (auto iter = list.begin(); iter != list.end(); ++iter)
			{
				BOOST_CHECK(*iter == expectedString[index]);
				++index;
			}
		}
		BOOST_AUTO_TEST_CASE(can_go_through_the_list_using_reverse_iterators)
		{
			size_t index = list.GetSize() - 1;
			for (auto iter = list.rbegin(); iter != list.rend(); --iter)
			{
				BOOST_CHECK(*iter == expectedString[index]);
				--index;
			}
		}
		BOOST_AUTO_TEST_CASE(can_get_access_to_elements_from_range_based_for)
		{
			size_t index = 0;
			for (auto str : list)
			{
				BOOST_CHECK(str == expectedString[index]);
				++index;
			}
		}
		BOOST_AUTO_TEST_CASE(can_insert_element_at_iterator_pos)
		{
			auto it = ++list.begin();
			list.Insert("20", it);
			BOOST_CHECK_EQUAL(*(++list.begin()), "20");

			list.Insert("11", list.begin());
			BOOST_CHECK_EQUAL(*list.begin(), "11");

			list.Insert("30", list.end());

			std::vector<std::string> expectedStrings = { "11", "first", "20", "second", "third", "30" };
			size_t i = 0;
			for (auto str : list)
			{
				BOOST_CHECK_EQUAL(str, expectedStrings[i]);
				i++;
			}
		}
		// TODO: добавить тесты проверки очищенного списка
		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			BOOST_CHECK(!list.IsEmpty());
			list.Clear();
			BOOST_CHECK(list.IsEmpty());
			
		}
		BOOST_AUTO_TEST_CASE(can_be_cleared_where_the_list_is_empty)
		{
			CStringList emptyList;

			BOOST_CHECK(emptyList.IsEmpty());
			emptyList.Clear();
			BOOST_CHECK(emptyList.IsEmpty());
		}
		// TODO: отчистка из пустого вектора
		BOOST_AUTO_TEST_CASE(can_erase_element_at_iterator_pos)
		{
			/*auto it = list.begin();
			BOOST_CHECK_EQUAL(*it, "first");
			auto elem = list.Erase(it);
			BOOST_CHECK_EQUAL(*elem, "first");
*/
			/*BOOST_CHECK_EQUAL(*++list.begin(), "second");

			list.Erase(list.begin());
			BOOST_CHECK_EQUAL(*list.begin(), "second");

			list.Erase(list.begin());
			BOOST_CHECK(list.IsEmpty());*/
		}
	BOOST_AUTO_TEST_SUITE_END()
	

BOOST_AUTO_TEST_SUITE_END()