#pragma once

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

#include "stdafx.h"


class CCalculator
{
public:
	CCalculator() = default;
	bool SetVar(std::string variable);
	bool SetLet(std::string m_variable, std::string variable);
	bool SetLet(std::string m_variable, double value);
private:
	bool IsVar(std::string const & variable);
	std::map<std::string, double> m_variables;
};

