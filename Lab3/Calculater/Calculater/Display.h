#pragma once
#include "Calculator.h"

class CDisplay
{
public:
	CDisplay();
	~CDisplay();
	void InputCommand(std::string const & command);
	void SetLet();
	void SetFn();
private:
	CCalculator m_calculator;
};

