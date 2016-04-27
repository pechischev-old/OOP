#include "Cone.h"



CCone::CCone(double density, double radius, double height)
	: CVolumeBody(density, radius, height, "Cone")
{
}

double CCone::GetVolume() const
{
	return (pow(m_radius, 2) * M_PI) * m_height * 1 / 3;
}




