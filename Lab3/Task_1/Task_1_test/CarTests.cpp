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
		BOOST_CHECK(!car.SetSpeed(20));
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
		BOOST_CHECK(car.SetSpeed(0)); // TODO: выделить в отдельный тест (задает нулевую скорость, когда скорость равна 0)
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
	}
	BOOST_AUTO_TEST_CASE(cannot_change_speed_when_transmission_is_neutral)
	{
		BOOST_CHECK(!car.SetSpeed(10));
	}
	BOOST_AUTO_TEST_CASE(switching_to_neutral_when_transmission_is_neutral)
	{
		BOOST_CHECK(car.SetGear(0));
	}

	BOOST_AUTO_TEST_CASE(switching_to_reverse)
	{
		car.TurnOnEngine();
		BOOST_CHECK(car.SetGear(-1));
		BOOST_CHECK_EQUAL(car.GetGear(), -1);
		car.SetGear(1);
		BOOST_CHECK(car.SetGear(-1));
		BOOST_CHECK_EQUAL(car.GetGear(), -1);


		car.SetSpeed(10);
		BOOST_CHECK(car.SetGear(0));
		BOOST_CHECK_EQUAL(car.GetGear(), 0);

		BOOST_CHECK(car.SetGear(1));
		BOOST_CHECK_EQUAL(car.GetGear(), 1);

		// TODO: в отдельный тест
		car.TurnOffEngine();
		car.TurnOnEngine();
		BOOST_CHECK(car.SetGear(1));
		BOOST_CHECK(car.SetSpeed(3));
		BOOST_CHECK(!car.SetGear(-1));
		BOOST_CHECK(car.SetGear(0));
		BOOST_CHECK_EQUAL(car.GetDirection(), 0);
		//----
	}
	struct when_turned_on_ : CCarFixture
	{
		when_turned_on_()
		{
			car.TurnOnEngine();
		}
	};
	/*BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)

		BOOST_AUTO_TEST_CASE(displays_channel_one)
		{
			BOOST_CHECK_EQUAL(car.GetGear(), 0);
			BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
		}

	BOOST_AUTO_TEST_SUITE_END()*/

BOOST_AUTO_TEST_SUITE_END()