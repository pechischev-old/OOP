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

SPerform CCalculator::DefineVar(string const & variable)
{
	if (!IsCorrectName(variable))
	{
		return SPerform(uncorrectNameVar);
	}
	else if (IsFunction(variable))
	{
		return SPerform(cannotBeFunction);
	}
	else if (!IsVar(variable))
	{
		m_variables.insert(pair<string, SVarInfo>(variable, SVarInfo()));
		return SPerform();
	}
	return SPerform(nameDuplication);
}

SPerform CCalculator::AssignVar(std::string const & var, std::string const & otherVar)
{
	if (otherVar.empty())
	{
		return SPerform(emptyOperand);
	}
	if (!IsVar(otherVar) && !IsFunction(otherVar))
	{
		return SPerform(notDetermined);
	}
	if (!IsVar(var))
	{
		SPerform perform = DefineVar(var);
		if (perform.is_initialized())
		{
			return perform;
		}
	}
	if (IsFunction(otherVar))
	{
		SFnInfo result = FindFunction(otherVar);
		m_variables[var] = result;
	}
	else
	{
		m_variables[var] = m_variables[otherVar];
	}
	return SPerform();
}

SPerform CCalculator::SetValue(std::string const & var, double const & value)
{
	if (IsFunction(var))
	{
		return SPerform(cannotBeFunction);
	}
	if (!IsVar(var))
	{
		SPerform perform = DefineVar(var);
		if (perform.is_initialized())
		{
			return perform;
		}
	}
	m_variables[var].value = value;
	return SPerform();
}

bool CCalculator::IsVar(std::string const & variable) const
{
	auto findedVar = m_variables.find(variable);
	return (findedVar != m_variables.end());
}

bool CCalculator::IsFunction(std::string const & nameFunction) const
{
	auto findedVar = m_function.find(nameFunction);
	return (findedVar != m_function.end());
}

SPerform CCalculator::DefineFunction(std::string const & varFunction, std::string const & var)
{
	if (IsVar(varFunction))
	{
		return SPerform(cannotBeVariables);
	}
	if (var.empty())
	{
		return SPerform(emptyOperand);
	}
	if (!IsFunction(varFunction))
	{
		if (!IsCorrectName(varFunction) )
		{
			return SPerform(uncorrectNameVar);
		}
		SFnInfo fnInfo;
		fnInfo.leftOperand = var;
		m_function.insert(pair<string, SFnInfo>(varFunction, fnInfo));
	}
	else
	{
		m_function[varFunction].leftOperand = var;
	}
	return SPerform();
	
	
}

SPerform CCalculator::DefineFunction(std::string const & varFunction, std::string const &firstOperand, 
	BinaryOperation const &  operatorFn, std::string const &secondOperand)
{
	if (IsVar(varFunction))
	{
		return SPerform(cannotBeVariables);
	}
	if (firstOperand.empty() || secondOperand.empty())
	{
		return SPerform(emptyOperand);
	}
	SFnInfo fnInfo;
	fnInfo.isBinary = true;
	fnInfo.leftOperand = firstOperand;
	fnInfo.rightOperand = secondOperand;
	fnInfo.type = operatorFn;
	if (!IsFunction(varFunction))
	{	
		if (!IsCorrectName(varFunction))
		{ 
			return SPerform(uncorrectNameVar);
		}
		m_function.insert(pair<string, SFnInfo>(varFunction, fnInfo));
	}
	else
	{
		m_function[varFunction] = fnInfo;
	}
	return SPerform();
	
}

double CCalculator::GetCalculateValue(std::string const & name) 
{
	if (IsFunction(name))
	{
		
		if (m_function[name].value.is_initialized())
		{
			return m_function[name].value.get();
		}
		else
		{
			CalculateValueFunction(m_function[name]);
			return m_function[name].value.get();
		}
	}
	else if (IsVar(name))
	{
		return m_variables[name].value.get();
	}
	return std::numeric_limits<double>::quiet_NaN();
}

void CCalculator::CalculateValueFunction(SFnInfo & fnInfo)
{
	boost::optional<double> result = std::numeric_limits<double>::quiet_NaN();
	double firstOperand = GetCalculateValue(fnInfo.leftOperand);
	double secondOperand = GetCalculateValue(fnInfo.rightOperand);
	switch (fnInfo.type)
	{
	case BinaryOperation::Add:
		result = firstOperand + secondOperand;
		break;
	case BinaryOperation::Div:
		result = firstOperand / secondOperand;
		break;
	case BinaryOperation::Multiply:
		result = firstOperand * secondOperand;
		break;
	case BinaryOperation::Substr:
		result = firstOperand - secondOperand;
		break;
	}
	if (result != std::numeric_limits<double>::quiet_NaN())
	{
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
		return GetStringCalculatingFn(FindFunction(var));
	}
	else if (IsVar(var))
	{
		return (m_variables[var].value.is_initialized() ? GetFormatingString(m_variables[var].value.value()) : "nan");
	}
	return string();
}

std::string CCalculator::GetStringCalculatingFn(SFnInfo const & fn) const
{	
	return (fn.value.is_initialized() ? GetFormatingString(fn.value.get()) : "nan");
}

std::list<std::string> CCalculator::DumpVars() const
{
	if (!m_variables.empty())
	{
		list<string> resultList;
		for (auto it : m_variables)
		{
			resultList.push_back(it.first + ":" + (it.second.value.is_initialized() ? GetFormatingString(it.second.value.get()) : "nan"));
		}
		return resultList;
	}
	return list<string>();
}

std::list<std::string> CCalculator::DumpFns()
{
	list<string> resultList;
	for (auto it : m_function)
	{
		resultList.push_back(it.first + ":" + GetStringCalculatingFn(FindFunction(it.first)));
	}
	return resultList;
}

SFnInfo CCalculator::FindFunction(std::string const & functionName) 
{
	if (IsFunction(functionName))
	{
		auto & function = m_function[functionName];
		if (function.isBinary)
		{
			CalculateValueFunction(function);
		}
		else
		{
			if (IsFunction(function.leftOperand))
			{
				function.value = m_function[function.leftOperand].value;
			}
			else
			{
				function.value = m_variables[function.leftOperand].value;
			}
		}
		return function;
	}
	return SFnInfo();
}