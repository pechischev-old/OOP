#pragma once
#include "stdafx.h"

#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Sphere.h"

class CInterpreter
{
public:
	CInterpreter() = default;
	void CreateShape(std::string const & name);
	void DisplaySummaryInfo();
private:
	// TODO: rename
	double GetRadius();
	double GetHeight();
	double GetDensity();
	double GetDepth();
	double GetWidth();
private:
	std::vector<std::shared_ptr<CBody *>> shapes;
};

