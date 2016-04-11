#include "stdafx.h"
#include "../Lab4/Cone.h"

struct Cone_
{
	const double expectedRadius = 34.57;
	const double expectedHeight = 75.156;
	const double expectedDensity = 5.89;
	const double expectedVolume = 94056.98;
	const CCone cone;
	Cone_()
		: cone(expectedDensity, expectedRadius, expectedHeight)
	{}
};

// Сфера
BOOST_FIXTURE_TEST_SUITE(Cone, Cone_)
	// является объемным телом
	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&cone));
	}
	// имеет радиус
	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK_EQUAL(cone.GetRadius(), expectedRadius);
	}
	// имеет радиус
	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_EQUAL(cone.GetHeight(), expectedHeight);
	}
	// имеет плотность
	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(cone).GetDensity(), expectedDensity);
	}
	// имеет объем
	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cone).GetVolume(), expectedVolume, 1e-7);
	}
	// имеет массу
	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cone).GetMass(), expectedVolume * expectedDensity, 1e-7);
	}
	// имеет строковое представление
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = R"(Cone:
	density = 5.89
	volume = 94056.98099
	mass = 553995.6181
	radius = 34.57
	height = 75.156
)";
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(cone).ToString(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()