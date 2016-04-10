#pragma once
#include "stdafx.h"
#include "Definition.h"


class CCalculator
{
public:
	CCalculator() = default;
	SPerform SetVar(std::string const & var);
	SPerform SetLet(std::string const & m_var, std::string const & var);
	SPerform SetLet(std::string const & m_var, float const & value);
	SPerform SetFunction(std::string const & varFunction, std::string const & var);
	SPerform SetFunction(std::string const & varFunction, std::string const &firstOperand, std::string const &operatorFn, std::string const &secondOperand);
	float GetValueLet(std::string const & var);
	SFnInfo GetValueFunction(std::string const & function);
	std::string Print(std::string const &var);

	std::list<std::string> GetVars();
	std::list<std::string> GetFns();
private:
	std::string GetStringCalculatingFn(SFnInfo const & fnInfo);
	float GetCalculateValue(std::string const & name);
	bool CheckNameVar(std::string const & nameVar);
	bool IsVar(std::string const & var);
	bool IsFunction(std::string const & nameFunction);
	void CalculateValueFunction(SFnInfo & fnInfo);
private:
	Function m_function;
	std::map<std::string, SVarInfo> m_variables;
};

