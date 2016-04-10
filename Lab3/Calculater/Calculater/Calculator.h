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
	double GetValueLet(std::string var);
	SFnInfo GetValueFunction(std::string function);
	std::string Print(std::string var);

	std::list<std::string> GetVars();
	std::list<std::string> GetFns();
private:
	std::string GetStringCalculatingFn(SFnInfo fnInfo);
	double GetCalculateValue(std::string const & name);
	bool CheckNameVar(std::string const & nameVar);
	bool IsVar(std::string const & var);
	bool IsFunction(std::string const & nameFunction);
	void CalculateValueFunction(SFnInfo & fnInfo);
private:
	Function m_function;
	std::map<std::string, SVarInfo> m_variables;
};

