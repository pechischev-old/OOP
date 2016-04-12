#include "Calculator.h"
#include <boost/format.hpp>

using namespace std;

bool IsCorrectName(std::string const & nameVar)
{
	if (nameVar.size() == 1)
	{
		return !nameVar.empty() && isalpha(int(nameVar.front()));
	}
	return !nameVar.empty() && isalpha(int(nameVar.front())) && all_of(nameVar.begin() + 1, nameVar.end(), [](char symbol) {
		return (isalnum(int(symbol)) || symbol == '_');
	});
}

SPerform CCalculator::SetVar(string const & variable)
{
	if (!IsCorrectName(variable))
		return SPerform(false, uncorrectNameVar);
	else if (IsFunction(variable))
		return SPerform(false, cannotBeFunction);
	else if (!IsVar(variable))
	{
		m_variables.insert(pair<string, SVarInfo>(variable, SVarInfo()));
		return SPerform();
	}
	return SPerform(false, nameDuplication);
}

SPerform CCalculator::SetLet(std::string const & var, std::string const & otherVar)
{
	if (otherVar.empty())
		return SPerform(false, emptyOperand);
	if (!IsVar(otherVar) && !IsFunction(otherVar))
		return SPerform(false, notDetermined);
	if (!IsVar(var))
	{
		SPerform perform = SetVar(var);
		if (!perform.IsSuccesful())
		{
			return perform;
		}
	}
	if (IsFunction(otherVar))
	{
		SFnInfo result = GetValueFunction(otherVar);
		m_variables[var].isDeterminate = result.isDeterminate;
		m_variables[var].value = result.value;
	}
	else
	{
		m_variables[var] = m_variables[otherVar];
	}
	return SPerform();
}

SPerform CCalculator::SetLet(std::string const & var, float const & value)
{
	if (IsFunction(var))
		return SPerform(false, cannotBeFunction);
	if (!IsVar(var))
	{
		SPerform perform = SetVar(var);
		if (!perform.IsSuccesful())
		{
			return perform;
		}
	}
	m_variables[var].value = value;
	m_variables[var].isDeterminate = true;
	return SPerform();
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

SPerform CCalculator::SetFunction(std::string const & varFunction, std::string const & var)
{
	if (IsVar(varFunction))
		return SPerform(false, cannotBeVariables);

	if (var.empty())
	{
		return SPerform(false, emptyOperand);
	}
	if (!IsFunction(varFunction))
	{
		if (!IsCorrectName(varFunction) )
		{
			return SPerform(false, uncorrectNameVar);
		}
		SFnInfo fnInfo;
		fnInfo.firstOperand = var;
		m_function.insert(pair<string, SFnInfo>(varFunction, fnInfo));
	}
	else
	{
		m_function[varFunction].firstOperand = var;
	}
	return SPerform();
	
	
}

SPerform CCalculator::SetFunction(std::string const & varFunction, std::string const &firstOperand, 
									std::string const & operatorFn, std::string const &secondOperand)
{
	if (IsVar(varFunction))
	{
		return SPerform(false, cannotBeVariables);
	}
	if (firstOperand.empty() || operatorFn.empty() || secondOperand.empty())
	{
		return SPerform(false, emptyOperand);
	}
	SFnInfo fnInfo;
	fnInfo.isTwoOperands = true;
	fnInfo.firstOperand = firstOperand;
	fnInfo.secondOperand = secondOperand;
	fnInfo.type = OPERATOR_MAP.find(operatorFn)->second;
	if (!IsFunction(varFunction))
	{	
		if (!IsCorrectName(varFunction))
		{ 
			return SPerform(false, uncorrectNameVar);
		}
		m_function.insert(pair<string, SFnInfo>(varFunction, fnInfo));
	}
	else
	{
		m_function[varFunction] = fnInfo;
	}
	return SPerform();
	
}

float CCalculator::GetCalculateValue(std::string const & name)
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
	float result = NAN;
	float firstOperand = GetCalculateValue(fnInfo.firstOperand);
	float secondOperand = GetCalculateValue(fnInfo.secondOperand);
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

string GetFormatingString(double const & value)
{
	return str(boost::format("%.2f") % value);
}

std::string CCalculator::GetValue(std::string const &var)
{
	if (IsFunction(var))
	{
		return GetStringCalculatingFn(GetValueFunction(var));
	}
	else if (IsVar(var))
	{
		return (m_variables[var].isDeterminate ? GetFormatingString(m_variables[var].value) : "nan");
	}
	return string();
}

std::string CCalculator::GetStringCalculatingFn(SFnInfo const & fn)
{	
	return (fn.isDeterminate ? GetFormatingString(fn.value) : "nan");
}

std::list<std::string> CCalculator::GetVars()
{
	if (!m_variables.empty())
	{
		list<string> resultList;
		for (auto it : m_variables)
		{
			resultList.push_back(it.first + ":" + (it.second.isDeterminate ? GetFormatingString(it.second.value) : "nan"));
		}
		return resultList;
	}
	return list<string>();
}

std::list<std::string> CCalculator::GetFns() 
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

float CCalculator::GetValueLet(std::string const & var)
{
	if (IsVar(var))
	{
		return m_variables[var].value;
	}
	return NAN;
}

SFnInfo CCalculator::GetValueFunction(std::string const & function)
{
	if (IsFunction(function))
	{
		if (m_function[function].isTwoOperands)
		{
			CalculateValueFunction(m_function[function]);
		}
		else
		{
			if (IsFunction(m_function[function].firstOperand))
			{
				m_function[function] = m_function[m_function[function].firstOperand];
			}
			else
			{
				m_function[function].value = m_variables[m_function[function].firstOperand].value;
				m_function[function].isDeterminate = m_variables[m_function[function].firstOperand].isDeterminate;
			}
		}
		return m_function[function];
	}
	return SFnInfo();
}