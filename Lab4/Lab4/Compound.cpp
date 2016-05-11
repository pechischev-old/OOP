#include "Compound.h"


using namespace std;

CCompound::CCompound()
	: CBody("Compound", 0)
{
}

// TODO: может принимать себя из самого себя
void CCompound::AppendShape(std::shared_ptr<CBody> && shape)
{
	const CBody *body = this;
	const CBody *second = shape.get();
	if (body != second)
	{
		m_shapes.push_back(move(shape));
		AddMass();
		AddVolume();
	}
	
}

size_t CCompound::GetShapesCount() const
{
	return m_shapes.size();
}

double CCompound::GetVolume() const
{
	return m_volume;
}

double CCompound::GetMass() const
{
	return m_mass;
}

double CCompound::GetDensity() const
{
	return GetMass() / GetVolume();
}

void CCompound::AddMass()
{
	for (auto const & shape : m_shapes)
	{
		m_mass += (shape)->GetMass();
	}
}

void CCompound::AddVolume()
{
	for (auto const & shape : m_shapes)
	{
		m_volume += (shape)->GetVolume();
	}
}

void CCompound::AppendProperties(std::ostream & strm) const
{
	strm << ToInfo();
}

std::string CCompound::ToInfo() const
{
	string info;
	for (auto const & shape : m_shapes)
	{
		info += (shape)->ToString();
	}
	return info;
}
