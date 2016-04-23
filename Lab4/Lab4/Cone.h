#pragma once
#include "stdafx.h"
#include "SolidBody.h"

class CCone final : public CSolidBody
{
public:
	CCone(double density, double radius, double height);
	double GetVolume() const override;
};

