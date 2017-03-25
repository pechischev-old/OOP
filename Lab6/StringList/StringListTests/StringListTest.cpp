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
		BOOST_AUTO_TEST_CASE(iterators_of_begin_and_end_are_equal)
		{
			BOOST_CHECK(list.begin() == list.end());
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
		BOOST_AUTO_TEST_CASE(after_decrement_saved_end_pos_iter_it_return_added_element)
		{
			auto end = list.end();
			list.PushBack("sample");
			BOOST_CHECK_EQUAL(*--list.end(), "sample");
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
			/*auto it = ++list.begin();
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
			}*/
		}
		
		BOOST_AUTO_TEST_CASE(can_erase_element_at_iterator_pos)
		{
			auto it = ++list.begin();
			BOOST_CHECK_EQUAL(*it, "second");
			list.Erase(it);
			BOOST_CHECK_EQUAL(*++list.begin(), "third");

			list.Erase(list.begin());
			BOOST_CHECK_EQUAL(*list.begin(), "third");

			list.Erase(list.begin());
			BOOST_CHECK(list.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(if_size_is_equal_1_and_iterator_of_end)
		{
			CStringList lst;
			lst.PushBack("123");
			lst.Erase(lst.end());
			BOOST_CHECK(lst.IsEmpty());
			
		}

		struct was_clear_ : public was_filled_
		{
			was_clear_()
			{
				list.Clear();
			}
		};
		BOOST_FIXTURE_TEST_SUITE(after_clear_a_string_list, was_clear_)

			BOOST_AUTO_TEST_CASE(list_is_empty)
			{
				BOOST_CHECK(list.IsEmpty());
			}
			BOOST_AUTO_TEST_CASE(list_size_is_equal_zero)
			{
				BOOST_CHECK_EQUAL(list.GetSize(), 0);
			}
			BOOST_AUTO_TEST_CASE(can_clear_already_empty_list_with_no_throw)
			{
				BOOST_REQUIRE_NO_THROW(list.Clear());
			}
		BOOST_AUTO_TEST_SUITE_END()
		
		
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(can_insert_data_in_iterator_pos, was_filled_)
		BOOST_AUTO_TEST_CASE(element_is_inserted_before_iterator_position)
		{
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "first");
			BOOST_REQUIRE_NO_THROW(list.Insert("Hm...", list.begin()));
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "Hm...");
		}
		BOOST_AUTO_TEST_CASE(inserting_incremented_list_size)
		{
			auto oldSize = list.GetSize();
			BOOST_REQUIRE_NO_THROW(list.Insert("String", list.begin()));
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			BOOST_REQUIRE_NO_THROW(list.Insert("Ptn", list.begin()));
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}
		BOOST_AUTO_TEST_CASE(can_insert_element_in_any_pos)
		{
			BOOST_CHECK_EQUAL(*(++list.begin()), "second");
			BOOST_REQUIRE_NO_THROW(list.Insert("Or Welkome in?", ++list.begin()));
			BOOST_CHECK_EQUAL(*(++list.begin()), "Or Welkome in?");
		}
		BOOST_AUTO_TEST_CASE(can_insert_to_empty_list)
		{
			CStringList emptyList;
			BOOST_CHECK_NO_THROW(emptyList.Insert("123", emptyList.begin()));
			BOOST_CHECK_EQUAL(emptyList.GetFrontElement(), "123");
			BOOST_CHECK_EQUAL(emptyList.GetBackElement(), "123");
		}
		BOOST_AUTO_TEST_CASE(can_insert_before_end_iter_pos)
		{
			BOOST_CHECK_EQUAL(list.GetBackElement(), "third");
			BOOST_REQUIRE_NO_THROW(list.Insert("What?", list.end()));
			BOOST_CHECK_EQUAL(*(--list.end()), "What?");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "What?");
		}
	BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END();