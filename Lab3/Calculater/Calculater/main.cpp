// Calculator.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Display.h"


int main()
{
	CDisplay userInterface;
	std::string command;
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		std::cin >> command;
		userInterface.InputCommand(command);
	}

    return 0;
}

