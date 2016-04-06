#pragma once
#include "stdafx.h"
#include "Definition.h"


class CCalculator
{
public:
	CCalculator() = default;
	bool SetVar(std::string var);
	bool SetLet(std::string m_var, std::string var);
	bool SetLet(std::string m_var, double value);
	bool SetFunction(std::string varFunction, std::string var);
	bool SetFunction(std::string varFunction, std::string firstOperand, std::string operatorFn, std::string secondOperand);
	std::string Print(std::string var);

	std::list<std::string> PrintVars();
	std::list<std::string> PrintFns();
private:
	bool CheckNameVar(std::string const & nameVar);
	bool IsVar(std::string const & var);
	std::string GetCalculatingFn(SFnInfo fnInfo);
	void CalculateValueFunction(SFnInfo & fnInfo);
	bool IsFunction(std::string const & nameFunction);
	std::map<std::string, SVarInfo> m_variables;
	Function m_function; 
};

