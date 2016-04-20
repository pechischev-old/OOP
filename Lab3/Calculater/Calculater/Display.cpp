#define _SCL_SECURE_NO_WARNINGS

#include "Display.h"
#include <boost\algorithm\string.hpp>
#include <sstream>
#include <vector>


CInterpreter::CInterpreter()
{
}


CInterpreter::~CInterpreter()
{
}

float StringToInt(std::string const & numberStr)
{
	std::stringstream ss(numberStr);
	float upperBound = 0;
	ss >> upperBound;
	return upperBound;
}

void CInterpreter::OutputErrors(ErrorType const & error)
{
	switch (error)
	{
	case uncorrectNameVar:
		std::cerr << "ERROR: The variable name is named incorrectly.\n For example: some_var_1 or someVar1" << std::endl;
		break;
	case cannotBeFunction:
		std::cerr << "ERROR: Variable can not be a function. Please, enter the variable" << std::endl;
		break;
	case cannotBeVariables:
		std::cerr << "ERROR: Function can not be a variable. Please, enter the function" << std::endl;
		break;
	case nameDuplication:
		std::cerr << "ERROR: Variable already declared" << std::endl;
		break;
	case emptyOperand:
		std::cerr << "ERROR: Transferred to an empty argument" << std::endl;
		break;
	case noVariable:
		std::cerr << "ERROR: Variable is not declared" << std::endl;
		break;
	case notDetermined:
		std::cerr << "ERROR: Variable is not determined" << std::endl;
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
	bool isSinglePoint = true;
	return all_of(str.begin(), str.end(), [&](char const & symbol)
	{
		/*if (symbol == '.' && isSinglePoint)
		{
			isSinglePoint = false;
		}*/
		return isdigit(int(symbol)) || (symbol == '.' && !isSinglePoint);
	});
}

void DisplayListString(std::list<std::string> const & listString)
{
	for (auto it : listString)
	{
		if (!it.empty())
		{
			std::cout << it << std::endl;
		}
	}
}

bool CInterpreter::IsNotCommand(std::string const & nameVar)
{
	return COMMANDS.count(nameVar) != 0;
}

std::string CInterpreter::InputExpession()
{
	std::string expression;
	std::cin >> expression;
	if (IsNotCommand(expression))
	{
		return expression;
	}
	std::cerr << "Can not use the name command as a variable" << std::endl;
	return "";
}

void CInterpreter::InputCommand(std::string const & command)
{
	if (command == "var")
	{
		OutputErrors(m_calculator.DefineVar(InputExpession()).get());
	}
	else if (command == "print")
	{
		std::string value = m_calculator.GetValue(InputExpession());
		if (!value.empty())
		{
			std::cout << value << std::endl;
		}
	}
	else if (command == "printvars")
	{
		DisplayListString(m_calculator.DumpVars());
	}
	else if (command == "printfns")
	{
		DisplayListString(m_calculator.DumpFns());
	}
	else if (command == "let")
	{
		this->AssignVar();
	}
	else if (command == "fn")
	{
		this->DefineFunction();
	}
	else
	{
		std::cerr << "Invalid command!" << std::endl;
	}
}

void CInterpreter::AssignVar()
{
	std::vector<std::string> tokens = SplitStringBySymbol(InputExpession(), "=");
	if (tokens.size() == 2 && !tokens[0].empty() && !tokens[1].empty())
	{
		if (IsNumber(tokens.back()))
		{
			OutputErrors(m_calculator.SetValue(tokens.front(), StringToInt(tokens.back())).get());
		}
		else
		{
			OutputErrors(m_calculator.AssignVar(tokens.front(), tokens.back()).get());
		}
	}
	else
	{
		std::cerr << "ERROR: The phrase entered does not match:\n let <var>=<value> or let <var>=<var>" << std::endl;
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
	return "";
}

void CInterpreter::DefineFunction()
{
	std::vector<std::string> tokens = SplitStringBySymbol(InputExpession(), "=");
	if (tokens.size() == 2 && !tokens.back().empty())
	{
		std::string operatorExpression = FindOperator(tokens.back());
		if (operatorExpression.empty())
		{
			OutputErrors(m_calculator.DefineFunction(tokens.front(), tokens.back()).get());
		}
		else
		{
			std::vector<std::string> operands = SplitStringBySymbol(tokens.back(), operatorExpression);
			if (operands.size() == 2 && !operands.empty())
			{
				OutputErrors(m_calculator.DefineFunction(tokens.front(),
								operands.front(), OPERATOR_MAP.find(operatorExpression)->second, operands.back()).get());
			}
		}
	}
	else
	{
		std::cerr << "ERROR: The phrase entered does not match:\n fn <var>=<var> or fn <var>=<var><operator><var>" << std::endl;
		// введенное выражение не соответствует формату fn <var>=<var> or fn <var>=<var><operator><var>
	}
}