#pragma once
#include "stdafx.h"
#include "SolidBody.h"

class CVolumeBody : public CSolidBody
{
public:
	CVolumeBody(double density, double radius, double height, std::string const & name);
	double GetRadius() const;
	double GetHeight() const;
protected:
	void AppendProperties(std::ostream & strm) const override;
	double m_radius = 0;
	double m_height = 0;
};

