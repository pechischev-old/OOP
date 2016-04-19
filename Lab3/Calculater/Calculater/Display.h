#pragma once
#include "Calculator.h"

class CInterpreter
{
public:
	CInterpreter();
	~CInterpreter();

	void InputCommand(std::string const & command);
	// rename SetLet, SetFn
	void SetLet();
	void SetFn();
	void OutputErrors(ErrorType const & error);
private:
	CCalculator m_calculator;
};

