// Calculator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Display.h"


int main()
{
	CInterpreter userInterface;
	std::string command;
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		std::cin >> command;
		userInterface.InputCommand(command);
	}

    return 0;
}

