#pragma once
#include "Calculator.h"

class CInterpreter
{
public:
	CInterpreter();
	~CInterpreter();

	void InputCommand(std::string const & command);
	void AssignVar();
	void DefineFunction();
	void OutputErrors(ErrorType const & error);
private:
	std::string InputExpession();
	bool IsNotCommand(std::string const & nameVar);
private:
	CCalculator m_calculator;
};

bool IsNumber(std::string const & str);
