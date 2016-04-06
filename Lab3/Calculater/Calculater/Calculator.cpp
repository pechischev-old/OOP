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
			fnInfo.firstOperator = var;
			m_function.insert(pair<string, SFnInfo>(varFunction, fnInfo));
		}
		else
		{
			m_function[varFunction].firstOperator = var;
		}
		return true;
	}
	return false;
}

bool CCalculator::SetFunction(std::string varFunction, std::string firstOperand, std::string operatorFn, std::string secondOperand)
{
	if (IsVar(firstOperand) && IsVar(secondOperand) && !IsVar(varFunction))
	{
		SFnInfo fnInfo;
		fnInfo.isTwoOperands = true;
		fnInfo.firstOperator = firstOperand;
		fnInfo.secondOperator = secondOperand;
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

void CCalculator::CalculateValueFunction(SFnInfo & fnInfo)
{
	double result = NAN;
	switch (fnInfo.type)
	{
	case OperatorType::Add:
		result = m_variables[fnInfo.firstOperator].value + m_variables[fnInfo.secondOperator].value;
		break;
	case OperatorType::Div:
		result = m_variables[fnInfo.firstOperator].value / m_variables[fnInfo.secondOperator].value;
		break;
	case OperatorType::Multiply:
		result = m_variables[fnInfo.firstOperator].value * m_variables[fnInfo.secondOperator].value;
		break;
	case OperatorType::Substr:
		result = m_variables[fnInfo.firstOperator].value - m_variables[fnInfo.secondOperator].value;
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
		return GetCalculatingFn(m_function[var]);
	}
	else if (IsVar(var))
	{
		return (m_variables[var].isDeterminate ? to_string(m_variables[var].value) : "nan");
	}
	return string();
}

std::string CCalculator::GetCalculatingFn(SFnInfo fn)
{
	if (fn.isTwoOperands)
	{
		CalculateValueFunction(fn);
	}
	else
	{
		fn.value = m_variables[fn.firstOperator].value;
		fn.isDeterminate = m_variables[fn.firstOperator].isDeterminate;
	}
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
			resultList.push_back(it.first + ":" + GetCalculatingFn(it.second));
		}
		return resultList;
	}
	return list<string>();
}
