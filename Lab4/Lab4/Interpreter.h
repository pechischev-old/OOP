#pragma once
#include "stdafx.h"

#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Sphere.h"
#include "Compaund.h"

class CBodyFactory
{
public:
	std::shared_ptr<CBody> CreateBody(std::string const & name);
private:
	CCompound CreateCompound();
	double GetData(std::string const & type);
	unsigned nestingLevel = 0;
};

class CInterpreter
{
public:
	CInterpreter() = default;
	void SetBody(std::string const & name); 
	void DisplaySummaryInfo();
private:
	std::vector<std::shared_ptr<CBody>> bodies;
	CBodyFactory m_bodyFactory;
};

