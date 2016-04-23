// Lab4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Interpreter.h"



int main()
{
	CInterpreter interpreter;
	std::string shapeName;
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		std::cin >> shapeName;
		if (!std::cin.fail())
		{
			interpreter.CreateShape(shapeName);
		}
	}
	interpreter.DisplaySummaryInfo();

    return 0;
}

