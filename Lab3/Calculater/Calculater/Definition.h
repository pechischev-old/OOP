#pragma once

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <Math.h>

enum ErrorType
{
	uncorrectNameVar,
	cannotBeFunction,
	cannotBeVariables,
	nameDuplication,
	emptyOperand,
	noVariable,
	notError
};

struct SPerform
{
public:
	SPerform(bool isSuccesful = true, ErrorType error = notError)
		: m_isSuccesful(isSuccesful)
		, m_error(error)
	{
	};
	bool IsSuccesful() const
	{
		return m_isSuccesful;
	};
	ErrorType GetError() const
	{
		return m_error;
	};
private:
	bool m_isSuccesful;
	ErrorType m_error;
};

enum class OperatorType
{
	Add,
	Multiply,
	Div,
	Substr
};

struct SVarInfo
{
	float value = NAN;
	bool isDeterminate = false;
};

struct SFnInfo
{
	float value = NAN;
	std::string firstOperand;
	std::string secondOperand;
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