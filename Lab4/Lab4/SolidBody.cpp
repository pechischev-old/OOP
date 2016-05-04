#include "SolidBody.h"



CSolidBody::CSolidBody(double density, std::string const & name)
	:CBody(name, density)
	, m_density(density)
{
}

double CSolidBody::GetMass() const
{
	return GetDensity() * GetVolume();
}

double CSolidBody::GetDensity() const
{
	return m_density;
}
