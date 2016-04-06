#include "Calculator.h"

using namespace std;

bool CCalculator::CheckNameVar(std::string const & nameVar)
{
	return nameVar != "" && isalpha(int(nameVar.front())) && any_of(nameVar.begin() + 1, nameVar.end(), [](char symbol) {
		return isalnum(int(symbol)) || symbol == '_';
	});
}

bool CCalculator::SetVar(string variable)
{
	if (!IsVar(variable) && CheckNameVar(variable))
	{
		m_variables.insert(pair<string, double>(variable, NAN));
		return true;
	}
	return false;
}

bool CCalculator::SetLet(std::string m_variable, std::string variable)
{
	if (!IsVar(m_variable))
	{
		SetVar(m_variable);
	}
	if (IsVar(m_variable))
	{
		m_variables[m_variable] = m_variables[variable];
		return true;
	}
	return false;
}

bool CCalculator::SetLet(std::string m_var, double value)
{
	if (!IsVar(m_var))
	{
		SetVar(m_var);
	}
	if (IsVar(m_var))
	{
		m_variables[m_var] = value;
		cout << m_var << " = " << value << endl;
		return true;
	}
	return false;
}

bool CCalculator::IsVar(std::string const & variable)
{
	auto findedVar = m_variables.find(variable);
	return (findedVar != m_variables.end());
}

bool CCalculator::IsFunction(std::string const & nameFunction)
{
	auto findedVar = m_function.find(nameFunction);
	return (findedVar != m_function.end());
}

bool CCalculator::SetFunction(std::string varFunction, std::string var)
{
	if (IsVar(var))
	{
		if (!IsFunction(varFunction) && CheckNameVar(varFunction))
		{
			m_function.insert(pair<string, double>(varFunction, m_variables[var]));
		}
		else
		{
			m_function[varFunction] = m_variables[var];
		}
		return true;
	}
	return false;
}

bool CCalculator::SetFunction(std::string varFunction, std::string firstOperand, std::string operatorFn, std::string secondOperand)
{
	if (IsVar(firstOperand) && IsVar(secondOperand))
	{
		if (!IsFunction(varFunction) && CheckNameVar(varFunction))
		{
			double result = CalculateValueFunction(m_variables[firstOperand], OPERATOR_MAP.find(operatorFn)->second, m_variables[secondOperand]);
			m_function.insert(pair<string, double>(varFunction, result));
		}
		else
		{
			m_function[varFunction] = CalculateValueFunction(m_variables[firstOperand], OPERATOR_MAP.find(operatorFn)->second, m_variables[secondOperand]);
		}
		return true;
	}
	return false;
}

double CCalculator::CalculateValueFunction(double const & firstValue, OperatorType const & operatorFn, double const & secondValue)
{
	double result = NAN;
	switch (operatorFn)
	{
	case OperatorType::Add:
		result = firstValue + secondValue;
		break;
	case OperatorType::Div:
		result = firstValue / secondValue;
		break;
	case OperatorType::Multiply:
		result = firstValue * secondValue;
		break;
	case OperatorType::Substr:
		result = firstValue - secondValue;
		break;
	}
	return result;
}

std::string CCalculator::Print(std::string var)
{
	return std::string();
}
