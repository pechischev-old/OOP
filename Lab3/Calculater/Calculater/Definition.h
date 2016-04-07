#pragma once

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>



enum class OperatorType
{
	Add,
	Multiply,
	Div,
	Substr
};

struct SVarInfo
{
	double value = NAN;
	bool isDeterminate = false;
};

struct SFnInfo
{
	double value = NAN;
	std::string firstOperator;
	std::string secondOperator;
	bool isTwoOperands = false;
	OperatorType type;
	bool isDeterminate = false;
};

using Function = std::map<std::string, SFnInfo>;

static const std::map<std::string, OperatorType> OPERATOR_MAP
{
	{ "+", OperatorType::Add },
	{ "-", OperatorType::Substr },
	{ "/", OperatorType::Div },
	{ "*", OperatorType::Multiply }
};