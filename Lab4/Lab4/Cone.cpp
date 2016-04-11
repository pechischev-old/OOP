#include "Cone.h"



CCone::CCone(double density, double radius, double height)
	: CBody("Cone", density)
	, m_radius(radius)
	, m_height(height)
{
}

double CCone::GetRadius() const
{
	return m_radius;
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return (pow(m_radius, 2) * M_PI) * m_height * 1 / 3;
}

void CCone::AppendProperties(std::ostream & strm) const
{
	strm << "\tradius = " << GetRadius() << std::endl;
	strm << "\theight = " << GetHeight() << std::endl;
}


