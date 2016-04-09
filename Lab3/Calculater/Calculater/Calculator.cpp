#include "Calculator.h"

using namespace std;

bool CCalculator::CheckNameVar(std::string const & nameVar)
{
	if (nameVar.size() == 1)
	{
		return nameVar != "" && isalpha(int(nameVar.front()));
	}
	return nameVar != "" && isalpha(int(nameVar.front())) && any_of(nameVar.begin() + 1, nameVar.end(), [](char symbol) {
		return isalnum(int(symbol)) || symbol == '_';
	});
}

bool CCalculator::SetVar(string variable)
{
	if (!IsVar(variable) && CheckNameVar(variable) && !IsFunction(variable))
	{
		m_variables.insert(pair<string, SVarInfo>(variable, SVarInfo()));
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
		m_variables[m_var].value = value;
		m_variables[m_var].isDeterminate = true;
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
	if (IsVar(var) && !IsVar(varFunction))
	{
		if (!IsFunction(varFunction))
		{
			if (!CheckNameVar(varFunction))
			{
				return false;
			}
			SFnInfo fnInfo;
			fnInfo.firstOperand = var;
			m_function.insert(pair<string, SFnInfo>(varFunction, fnInfo));
		}
		else
		{
			m_function[varFunction].firstOperand = var;
		}
		return true;
	}
	return false;
}

bool CCalculator::SetFunction(std::string varFunction, std::string firstOperand, std::string operatorFn, std::string secondOperand)
{
	if (!IsVar(varFunction))
	{
		SFnInfo fnInfo;
		fnInfo.isTwoOperands = true;
		fnInfo.firstOperand = firstOperand;
		fnInfo.secondOperand = secondOperand;
		fnInfo.type = OPERATOR_MAP.find(operatorFn)->second;

		if (!IsFunction(varFunction))
		{	
			if (!CheckNameVar(varFunction))
			{ 
				return false;
			}
			m_function.insert(pair<string, SFnInfo>(varFunction, fnInfo));
		}
		else
		{
			m_function[varFunction] = fnInfo;
		}
		return true;
	}
	return false;
}

double CCalculator::GetCalculateValue(std::string const & name)
{
	if (IsFunction(name))
	{
		if (m_function[name].isDeterminate)
			return m_function[name].value;
		else
		{
			CalculateValueFunction(m_function[name]);
			return m_function[name].value;
		}
	}
	else if (IsVar(name))
	{
		return m_variables[name].value;
	}
	return NAN;
}

void CCalculator::CalculateValueFunction(SFnInfo & fnInfo)
{
	double result = NAN;
	double firstOperand = GetCalculateValue(fnInfo.firstOperand);
	double secondOperand = GetCalculateValue(fnInfo.secondOperand);
	switch (fnInfo.type)
	{
	case OperatorType::Add:
		result = firstOperand + secondOperand;
		break;
	case OperatorType::Div:
		result = firstOperand / secondOperand;
		break;
	case OperatorType::Multiply:
		result = firstOperand * secondOperand;
		break;
	case OperatorType::Substr:
		result = firstOperand - secondOperand;
		break;
	}
	if (to_string(result) != "-nan(ind)")
	{
		fnInfo.isDeterminate = true;
		fnInfo.value = result;
	}
}

std::string CCalculator::Print(std::string var)
{
	if (IsFunction(var))
	{
		return GetStringCalculatingFn(GetValueFunction(var));
	}
	else if (IsVar(var))
	{
		return (m_variables[var].isDeterminate ? to_string(m_variables[var].value) : "nan");
	}
	return string();
}

std::string CCalculator::GetStringCalculatingFn(SFnInfo fn)
{	
	return (fn.isDeterminate ? to_string(fn.value) : "nan");
}

std::list<std::string> CCalculator::PrintVars()
{
	if (!m_variables.empty())
	{
		list<string> resultList;
		for (auto it : m_variables)
		{
			resultList.push_back(it.first + ":" + (it.second.isDeterminate ? to_string(it.second.value) : "nan"));
		}
		return resultList;
	}
	return list<string>();
}

std::list<std::string> CCalculator::PrintFns() 
{
	if (!m_function.empty())
	{
		list<string> resultList;
		for (auto it : m_function)
		{
			resultList.push_back(it.first + ":" + GetStringCalculatingFn(GetValueFunction(it.first)));
		}
		return resultList;
	}
	return list<string>();
}

double CCalculator::GetValueLet(std::string var)
{
	if (IsVar(var))
	{
		return m_variables[var].value;
	}
	return NAN;
}

SFnInfo CCalculator::GetValueFunction(std::string function)
{
	if (IsFunction(function))
	{
		if (m_function[function].isTwoOperands)
		{
			CalculateValueFunction(m_function[function]);
		}
		else
		{
			m_function[function].value = m_variables[m_function[function].firstOperand].value;
			m_function[function].isDeterminate = m_variables[m_function[function].firstOperand].isDeterminate;
		}
		return m_function[function];
	}
	return SFnInfo();
}