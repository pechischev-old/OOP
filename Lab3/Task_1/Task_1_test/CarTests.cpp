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

	BOOST_AUTO_TEST_CASE(cannot_set_speed_is_greater_than_0_for_neutral_gear)
	{
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
		BOOST_CHECK(!car.SetSpeed(20));
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
		BOOST_CHECK(car.SetSpeed(0)); 
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}
	BOOST_AUTO_TEST_CASE(switching_to_neutral_when_transmission_is_neutral)
	{
		BOOST_CHECK(car.SetGear(0));
	}
	
	struct when_turned_on_ : CCarFixture
	{
		when_turned_on_()
		{
			car.TurnOnEngine();
		}
	};
	
	BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
		// не может быть еще раз включен если уже включен
		BOOST_AUTO_TEST_CASE(cannot_turned_on_if_already_turned_on)
		{
			BOOST_CHECK(!car.TurnOnEngine());
		}
		BOOST_AUTO_TEST_CASE(displays_value_by_default)
		{
			BOOST_CHECK_EQUAL(car.GetGear(), 0);
			BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
		}

		BOOST_AUTO_TEST_CASE(check_inability_of_switching_first_transmission_to_reverse)
		{
			BOOST_CHECK(car.SetGear(1));
			BOOST_CHECK(car.SetSpeed(3));
			BOOST_CHECK(!car.SetGear(-1));
			BOOST_CHECK(car.SetGear(0));
			BOOST_CHECK_EQUAL(car.GetDirection(), 0);
		}
		BOOST_AUTO_TEST_CASE(switching_to_reverse_gear)
		{
			BOOST_CHECK_EQUAL(car.GetGear(), 0);
			BOOST_CHECK(car.SetGear(-1));
			BOOST_CHECK_EQUAL(car.GetGear(), -1);
			car.SetGear(1);
			BOOST_CHECK(car.SetGear(-1));
			BOOST_CHECK_EQUAL(car.GetGear(), -1);
		}
		BOOST_AUTO_TEST_CASE(switching_from_first_gear_to_second_gear_and_back)
		{
			car.SetGear(1);
			BOOST_CHECK(car.SetSpeed(30));
			BOOST_CHECK(car.SetGear(2));
			BOOST_CHECK_EQUAL(car.GetGear(), 2);
			BOOST_CHECK(car.SetSpeed(20));
			BOOST_CHECK(car.SetGear(1));
			BOOST_CHECK_EQUAL(car.GetGear(), 1);
		}
		BOOST_AUTO_TEST_CASE(cannot_switching_to_second_gear_when_not_enough_speed)
		{
			car.SetGear(1);
			BOOST_CHECK(car.SetSpeed(15));
			BOOST_CHECK(!car.SetGear(2));
			BOOST_CHECK_EQUAL(car.GetGear(), 1);
		}
		// переключение со 2-й на 4-ю
		// переключение с 4-й на 5-ю
		// переключение с 5-й, 4-й на нейтралку
		// выключение на скорости и на нейтралке
		BOOST_AUTO_TEST_CASE(switching_gears)
		{
			car.SetGear(1);
			car.SetSpeed(20);
			car.SetGear(2);
			BOOST_CHECK(!car.SetGear(4));
			car.SetSpeed(50);
			BOOST_CHECK(car.SetGear(4));
			BOOST_CHECK_EQUAL(car.GetGear(), 4);
			car.SetSpeed(90);
			BOOST_CHECK(car.SetGear(5));
			BOOST_CHECK_EQUAL(car.GetGear(), 5);
			BOOST_CHECK(car.SetGear(4));
			BOOST_CHECK_EQUAL(car.GetGear(), 4);
			BOOST_CHECK(car.SetGear(0));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 0);

			car.SetGear(1);
			BOOST_CHECK(car.SetSpeed(120));
			BOOST_CHECK(car.SetGear(5));
			BOOST_CHECK_EQUAL(car.GetGear(), 5);
			BOOST_CHECK(!car.SetSpeed(170));
			BOOST_CHECK(car.SetGear(0));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
		}
		BOOST_AUTO_TEST_CASE(cannot_turn_off_when_speed_is_greater_than_0)
		{

			BOOST_CHECK(car.SetGear(0));
			BOOST_CHECK(car.SetGear(1));
			BOOST_CHECK(car.SetSpeed(20));
			BOOST_CHECK(!car.TurnOffEngine());
		}
		BOOST_AUTO_TEST_CASE(can_turn_off_when_speed_is_0_and_transmission_is_neutral)
		{
			BOOST_CHECK(car.TurnOffEngine());
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct when_turned_off_ : CCarFixture
	{
		when_turned_off_()
		{
			car.TurnOffEngine();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_turned_off, when_turned_off_)
		BOOST_AUTO_TEST_CASE(is_turned_off)
		{
			BOOST_CHECK(!car.IsTurnedOn());
		}
		BOOST_AUTO_TEST_CASE(repeat_turn_off)
		{
			BOOST_CHECK(car.TurnOffEngine());
		}
		BOOST_AUTO_TEST_CASE(Unable_to_switch_to_first_gear_and_set_speed)
		{
			BOOST_CHECK(!car.SetGear(1));
			BOOST_CHECK_EQUAL(car.GetGear(), 0);
			BOOST_CHECK(!car.SetSpeed(5));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
			BOOST_CHECK(car.SetGear(0));
		}

	BOOST_AUTO_TEST_SUITE_END()
	//повторное включение
	BOOST_AUTO_TEST_CASE(reclosing)
	{
		car.TurnOnEngine();
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

BOOST_AUTO_TEST_SUITE_END()