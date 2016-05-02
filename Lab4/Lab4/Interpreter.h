#pragma once
#include "stdafx.h"

#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Sphere.h"

class CBodyFactory
{
public:
	static std::shared_ptr<CBody> CreateBody(std::string const & name);
private:
	static double GetData(std::string const & type);
};

class CInterpreter
{
public:
	CInterpreter() = default;
	void SetBody(std::string const & name); 
	void DisplaySummaryInfo();
private:
	std::vector<std::shared_ptr<CBody>> bodies;
};

