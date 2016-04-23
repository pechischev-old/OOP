#include "SolidBody.h"



CSolidBody::CSolidBody(double density, double radius, double height, std::string name)
	:CBody(name, density)
	, m_radius(radius)
	, m_height(height)
{
}

double CSolidBody::GetRadius() const
{
	return m_radius;
}

double CSolidBody::GetHeight() const
{
	return m_height;
}

void CSolidBody::AppendProperties(std::ostream & strm) const
{
	strm << "\tradius = " << GetRadius() << std::endl;
	strm << "\theight = " << GetHeight() << std::endl;
}