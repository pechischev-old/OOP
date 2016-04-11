#include "stdafx.h"
#include "../Lab4/Cylinder.h"

struct Cylinder_
{
	const double expectedRadius = 34.57;
	const double expectedHeight = 75.156;
	const double expectedDensity = 5.89;
	const double expectedVolume = 282170.94;
	const CCylinder cylinder;
	Cylinder_()
		: cylinder(expectedDensity, expectedRadius, expectedHeight)
	{}
};

// Сфера
BOOST_FIXTURE_TEST_SUITE(Cylinder, Cylinder_)
	// является объемным телом
	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&cylinder));
	}
	// имеет радиус
	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK_EQUAL(cylinder.GetRadius(), expectedRadius);
	}
	// имеет радиус
	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_EQUAL(cylinder.GetHeight(), expectedHeight);
	}
	// имеет плотность
	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(cylinder).GetDensity(), expectedDensity);
	}
	// имеет объем
	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cylinder).GetVolume(), expectedVolume, 1e-7);
	}
	// имеет массу
	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cylinder).GetMass(), expectedVolume * expectedDensity, 1e-7);
	}
	// имеет строковое представление
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = R"(Cylinder:
	density = 5.89
	volume = 282170.943
	mass = 1661986.854
	radius = 34.57
	height = 75.156
)";
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(cylinder).ToString(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()