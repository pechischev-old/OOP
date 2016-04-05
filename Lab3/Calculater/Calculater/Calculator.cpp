#include "Calculator.h"

using namespace std;

bool CCalculator::SetVar(string variable)
{
	if (!IsVar(variable))
	{
		m_variables.insert(pair<string, double>(variable, NAN ));
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

bool CCalculator::SetLet(std::string m_variable, double value)
{
	if (!IsVar(m_variable))
	{
		SetVar(m_variable);
	}
	if (IsVar(m_variable))
	{
		m_variables.find(m_variable)->second = value;
		return true;
	}
	return false;
}

bool CCalculator::IsVar(std::string const & variable)
{
	auto findedVar = m_variables.find(variable);
	return (findedVar != m_variables.end() || variable.empty());
}
