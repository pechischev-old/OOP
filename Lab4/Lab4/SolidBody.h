#pragma once
#include "stdafx.h"
#include "Body.h"


class CSolidBody : public CBody
{
public:
	CSolidBody(double density, double radius, double height, std::string name);
	double GetRadius() const;
	double GetHeight() const;
protected:
	void AppendProperties(std::ostream & strm) const override;
	double m_radius;
	double m_height;
};

