#include "Parallelepiped.h"



CParallelepiped::CParallelepiped(double density, double height, double width, double depth)
	: CBody("Parallelepiped", density)
	, m_height(height)
	, m_width(width)
	, m_depth(depth)
{
}

double CParallelepiped::GetVolume() const
{
	return GetDepth() * GetHeight() * GetWidth();
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

void CParallelepiped::AppendProperties(std::ostream & strm) const
{
	strm << "\twidth = " << GetWidth() << std::endl;
	strm << "\theight = " << GetHeight() << std::endl;
	strm << "\tdepth = " << GetDepth() << std::endl;
}


