#pragma once
#include "stdafx.h"
#include "Body.h"


class CSolidBody : public CBody
{
public:
	CSolidBody(double density, std::string name);
	double GetMass() const override;
	double GetDensity() const override;
protected:
	double m_density = 0;
};

