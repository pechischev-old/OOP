#pragma once
#include "stdafx.h"
#include "SolidBody.h"

class CCylinder final : public CSolidBody
{
public:
	CCylinder(double density, double radius, double height);
	double GetVolume() const override;
};

