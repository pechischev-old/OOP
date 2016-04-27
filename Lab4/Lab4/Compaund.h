#pragma once
#include "stdafx.h"
#include "Body.h"

class CCompound final : public CBody
{
public:
	CCompound();
	void AppendShape(std::shared_ptr<CBody> && shape);
	size_t GetShapesCount() const;
	double GetVolume() const override;
	double GetMass() const override;
	double GetDensity() const override;
private:
	void AddMass();
	void AddVolume();
	std::string ToInfo() const;
protected:
	void AppendProperties(std::ostream & strm) const override;
private:
	std::vector<std::shared_ptr<CBody>> m_shapes;
	double m_mass = 0;
	double m_volume = 0;
};

