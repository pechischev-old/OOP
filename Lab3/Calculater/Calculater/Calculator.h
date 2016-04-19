#pragma once
#include "stdafx.h"
#include "Definition.h"


class CCalculator
{
public:
	CCalculator() = default;
	SPerform DefineVar(std::string const & var);
	SPerform AssignVar(std::string const & var, std::string const & otherVar); 
	SPerform SetValue(std::string const & var, double const & value); 
	SPerform DefineFunction(std::string const & varFunction, std::string const & var); 
	SPerform DefineFunction(std::string const & varFunction, std::string const &firstOperand, BinaryOperation const & operatorFn, std::string const &secondOperand);
	SFnInfo FindFunction(std::string const & function); 

	std::string GetValue(std::string const &var);
	std::list<std::string> DumpVars() const;
	std::list<std::string> DumpFns();
private:
	std::string GetStringCalculatingFn(SFnInfo const & fnInfo) const;
	double GetCalculateValue(std::string const & name);
	bool IsVar(std::string const & var) const;
	bool IsFunction(std::string const & nameFunction) const;
	void CalculateValueFunction(SFnInfo & fnInfo);
private:
	Function m_function;
	std::map<std::string, SVarInfo> m_variables;
};

