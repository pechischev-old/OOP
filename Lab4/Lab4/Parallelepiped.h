#pragma once
#include "stdafx.h"

#include "Body.h"

class CParallelepiped final : public CBody
{
public:
	CParallelepiped(double density, double height, double width, double depth);

	double GetVolume() const override;
	double GetWidth() const;
	double GetDepth() const;
	double GetHeight() const;
protected:
	void AppendProperties(std::ostream & strm) const override;
private:
	double m_height;
	double m_width;
	double m_depth;
};

