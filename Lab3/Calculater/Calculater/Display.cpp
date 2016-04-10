﻿#define _SCL_SECURE_NO_WARNINGS

#include "Display.h"
#include <boost\algorithm\string.hpp>
#include <sstream>
#include <vector>


CDisplay::CDisplay()
{
}


CDisplay::~CDisplay()
{
}

double StringToInt(std::string const & numberStr)
{
	std::stringstream ss(numberStr);
	unsigned upperBound = 0;
	ss >> upperBound;
	return upperBound;
}

void CDisplay::OutputErrors(ErrorType const & error)
{
	switch (error)
	{
	case uncorrectNameVar:
		std::cout << "ERROR: The variable name is named incorrectly.\n For example: some_var_1 or someVar1" << std::endl;
		break;
	case cannotBeFunction:
		std::cout << "ERROR: Variable can not be a function. Please, enter the variable" << std::endl;
		break;
	case cannotBeVariables:
		std::cout << "ERROR: Function can not be a variable. Please, enter the function" << std::endl;
		break;
	case nameDuplication:
		std::cout << "ERROR: Variable already declared" << std::endl;
		break;
	case emptyOperand:
		std::cout << "ERROR: Transferred to an empty argument" << std::endl;
		break;
	case noVariable:
		std::cout << "ERROR: Variable is not declared" << std::endl;
		break;
	case notError:
		break;
	}
}

std::vector<std::string> SplitStringBySymbol(std::string const & expression, std::string const & symbol)
{
	std::vector<std::string> splitingString;
	boost::split(splitingString, expression, boost::is_any_of(symbol));
	return splitingString;
}

bool IsNumber(std::string const & str)
{
	return all_of(str.begin(), str.end(), [](char const & symbol)
	{
		return isdigit(int(symbol)) || symbol == '.';
	});
}

void DisplayListString(std::list<std::string> const & listString)
{
	if (!listString.empty())
	{
		for (auto it : listString)
		{
			if (it != std::string())
			{
				std::cout << it << std::endl;
			}
		}
	}
}

std::string InputExpession()
{
	std::string expression;
	std::cin >> expression;
	return expression;
}

void CDisplay::InputCommand(std::string const & command)
{
	if (command == "var")
	{
		OutputErrors(m_calculator.SetVar(InputExpession()).GetError());
	}
	else if (command == "print")
	{
		std::cout << m_calculator.Print(InputExpession()) << std::endl;
	}
	else if (command == "printvars")
	{
		DisplayListString(m_calculator.GetVars());
	}
	else if (command == "printfns")
	{
		DisplayListString(m_calculator.GetFns());
	}
	else if (command == "let")
	{
		this->SetLet();
	}
	else if (command == "fn")
	{
		this->SetFn();
	}
	else
	{
		std::cout << "Invalid command!" << std::endl;
	}
}

void CDisplay::SetLet()
{
	std::vector<std::string> splitingExpression = SplitStringBySymbol(InputExpession(), "=");
	if (splitingExpression.size() == 2 && !splitingExpression.empty())
	{
		if (IsNumber(splitingExpression.back()))
		{
			OutputErrors(m_calculator.SetLet(splitingExpression.front(), StringToInt(splitingExpression.back())).GetError());
		}
		else
		{
			OutputErrors(m_calculator.SetLet(splitingExpression.front(), splitingExpression.back()).GetError());
		}
	}
	else
	{
		std::cout << "ERROR: The phrase entered does not match:\n let <var>=<value> or let <var>=<var>" << std::endl;
		// введенное выражение не соответствует формату let <var>=<value> or <var>=<var>
	}
}

std::string FindOperator(std::string const & expression)
{
	if (expression.find('+') != std::string::npos)
	{
		return "+";
	}
	else if (expression.find('-') != std::string::npos)
	{
		return "-";
	}
	else if (expression.find('*') != std::string::npos)
	{
		return "*";
	}
	else if (expression.find('/') != std::string::npos)
	{
		return "/";
	}
	return std::string();
}

void CDisplay::SetFn()
{
	std::vector<std::string> splitingExpression = SplitStringBySymbol(InputExpession(), "=");
	if (splitingExpression.size() == 2 && !splitingExpression.back().empty())
	{
		std::string operatorExpression = FindOperator(splitingExpression.back());
		if (operatorExpression.empty())
		{
			OutputErrors(m_calculator.SetFunction(splitingExpression.front(), splitingExpression.back()).GetError());
		}
		else
		{
			std::vector<std::string> operands = SplitStringBySymbol(splitingExpression.back(), operatorExpression);
			if (operands.size() == 2 && !operands.empty())
			{
				OutputErrors(m_calculator.SetFunction(splitingExpression.front(), 
								operands.front(), operatorExpression, operands.back()).GetError());
			}
		}
	}
	else
	{
		std::cout << "ERROR: The phrase entered does not match:\n fn <var>=<var> or fn <var>=<var><operator><var>" << std::endl;
		// введенное выражение не соответствует формату fn <var>=<var> or fn <var>=<var><operator><var>
	}
}