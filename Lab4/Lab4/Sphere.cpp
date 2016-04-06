#include "Sphere.h"



CSphere::CSphere()
{
}


CSphere::~CSphere()
{
}

void CSphere::SetMass(unsigned mass)
{
	m_mass = mass;
}

void CSphere::SetDensity(unsigned density)
{
	m_density = density;
}

void CSphere::SetVolume(unsigned volume)
{
	m_volume = volume;
}

std::string CSphere::GetInfo()
{
	return std::string();
}
