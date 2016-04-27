#include "Cylinder.h"



CCylinder::CCylinder(double density, double radius, double height)
	: CVolumeBody(density, radius, height, "Cylinder")
{
}

double CCylinder::GetVolume() const
{
	return (pow(m_radius, 2) * M_PI) * m_height;
}

