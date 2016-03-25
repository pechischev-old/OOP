#include "stdafx.h"
#include "../Task_1/Car.h"

using namespace std;


struct CCarFixture
{
	CCar car;
};

// Автомобиль
BOOST_FIXTURE_TEST_SUITE(Car, CCarFixture)
	// изначально выключен
	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!car.IsTurnedOn());
	}

	BOOST_AUTO_TEST_CASE(cannot_select_gear_when_turned_off)
	{

		BOOST_CHECK(!car.SetGear(1));
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
	}
	// может быть включен
	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		BOOST_CHECK(car.TurnOnEngine());
	}

	BOOST_AUTO_TEST_CASE(displays_gear_0_by_default)
	{
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
	}

	struct when_turned_on_ : CCarFixture
	{
		when_turned_on_()
		{
			car.TurnOnEngine();
		}
	};
	// TODO : продолжить от этого теста
	BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)

		BOOST_AUTO_TEST_CASE(displays_channel_one)
		{
			BOOST_CHECK_EQUAL(car.GetGear(), 0);
			BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()