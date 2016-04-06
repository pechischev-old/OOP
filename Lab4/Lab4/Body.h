#pragma once

#include "stdafx.h"

class CBody
{
public:
	CBody() = default;
	virtual ~CBody() {};
	virtual void SetMass(unsigned mass) = 0;
	virtual void SetDensity(unsigned density) = 0;
	virtual void SetVolume(unsigned volume) = 0;
	virtual std::string GetInfo() = 0;
protected:
	unsigned m_density;
	unsigned m_volume;
	unsigned m_mass;
	std::string m_type;
};

