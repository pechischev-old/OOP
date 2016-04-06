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
private:
	bool CheckNameVar(std::string const & nameVar);
	bool IsVar(std::string const & var);
	double CalculateValueFunction(double const & firstValue, OperatorType const & operatorFn, double const & secondValue);
	bool IsFunction(std::string const & nameFunction);
	std::map<std::string, double> m_variables;
	Function m_function;
};

