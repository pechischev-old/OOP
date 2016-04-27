#pragma once
#include "stdafx.h"
#include "VolumeBody.h"

class CCone final : public CVolumeBody
{
public:
	CCone(double density, double radius, double height);
	double GetVolume() const override;
};

