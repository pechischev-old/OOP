#pragma once
#include "stdafx.h"

#include "Body.h"


class CSphere : public CBody
{
public:
	CSphere();
	~CSphere();
	void SetMass(unsigned mass) override;
	void SetDensity(unsigned density) override;
	void SetVolume(unsigned volume) override;
	std::string GetInfo() override;
private:
	unsigned m_radius;
};

