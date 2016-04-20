#pragma once

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <Math.h>
#include <limits>
#include <set>
#include <boost/optional.hpp>

enum ErrorType
{
	uncorrectNameVar,
	cannotBeFunction,
	cannotBeVariables,
	nameDuplication,
	emptyOperand,
	noVariable,
	notDetermined
};

using SPerform = boost::optional<ErrorType>;

static std::set<std::string> COMMANDS { "var", "print", "printvars", "printfns", "let", "fn" };

enum class BinaryOperation
{
	Add,
	Multiply,
	Div,
	Substr
};

struct SVarInfo
{
	boost::optional<double> value = std::numeric_limits<double>::quiet_NaN();
};

struct SFnInfo : public SVarInfo
{
	std::string leftOperand;
	std::string rightOperand;
	bool isBinary = false;
	BinaryOperation type;
};

using Function = std::map<std::string, SFnInfo>;

static const std::map<std::string, BinaryOperation> OPERATOR_MAP
{
	{ "+", BinaryOperation::Add },
	{ "-", BinaryOperation::Substr },
	{ "/", BinaryOperation::Div },
	{ "*", BinaryOperation::Multiply }
};