#include "stdafx.h"
#include "../Lab4/Compound.h"
#include "../Lab4/Cone.h"

using namespace std;

struct Compound_
{
	shared_ptr<CCompound> pCompound = make_shared<CCompound>();
};

BOOST_FIXTURE_TEST_SUITE(Compound, Compound_)
	// является объемным телом
	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(pCompound.get()));
	}
	BOOST_AUTO_TEST_CASE(can_add_shape)
	{
		BOOST_CHECK_EQUAL(pCompound->GetShapesCount(), 0);
		auto cone = CCone(15, 10, 40);
		pCompound->AppendShape(make_shared<CCone>(CCone(15, 10, 40)));
		BOOST_CHECK_EQUAL(pCompound->GetShapesCount(), 1);
	}

	struct Consist_of_one_body_ : Compound_
	{
		const double expectedRadius = 10;
		const double expectedHeight = 40;
		const double expectedDensity = 15;
		const double expectedVolume = 4188.79;
		Consist_of_one_body_()
		{
			pCompound->AppendShape(make_shared<CCone>(CCone(expectedDensity, expectedRadius, expectedHeight)));
		}
	};
	BOOST_FIXTURE_TEST_SUITE(Consist_of_one_body, Consist_of_one_body_)
		// имеет плотность
		BOOST_AUTO_TEST_CASE(has_a_density)
		{
			BOOST_CHECK_EQUAL(pCompound->GetDensity(), expectedDensity);
		}
		// имеет объем
		BOOST_AUTO_TEST_CASE(has_a_volume)
		{
			BOOST_CHECK_CLOSE_FRACTION(pCompound->GetVolume(), expectedVolume, 1e-7);
		}
		// имеет массу
		BOOST_AUTO_TEST_CASE(has_a_mass)
		{
			BOOST_CHECK_CLOSE_FRACTION(pCompound->GetMass(), expectedVolume * expectedDensity, 1e-7);
		}
		// имеет строковое представление
		BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
		{
			const auto expectedString = R"(Compound:
	density = 15
	volume = 4188.790205
	mass = 62831.85307
Cone:
	density = 15
	volume = 4188.790205
	mass = 62831.85307
	radius = 10
	height = 40
)";
			BOOST_CHECK_EQUAL(pCompound->ToString(), expectedString);
		}
		BOOST_AUTO_TEST_CASE(can_not_take_itself)
		{			
			BOOST_CHECK_EQUAL(pCompound->GetShapesCount(), 1);
			pCompound->AppendShape(pCompound);
			BOOST_CHECK_EQUAL(pCompound->GetShapesCount(), 1);
		}
		BOOST_AUTO_TEST_CASE(can_take_yet_one_body)
		{
			pCompound->AppendShape(make_shared<CCone>(CCone(expectedDensity, expectedRadius, expectedHeight)));
			BOOST_CHECK_EQUAL(pCompound->GetShapesCount(), 2);
		}

	BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()

