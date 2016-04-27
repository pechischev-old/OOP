#include "VolumeBody.h"


CVolumeBody::CVolumeBody(double density, double radius, double height, std::string name)
	:CSolidBody(density, name)
	, m_radius(radius)
	, m_height(height)
{
}

double CVolumeBody::GetRadius() const
{
	return m_radius;
}

double CVolumeBody::GetHeight() const
{
	return m_height;
}

void CVolumeBody::AppendProperties(std::ostream & strm) const
{
	strm << "\tradius = " << GetRadius() << std::endl;
	strm << "\theight = " << GetHeight() << std::endl;
}
