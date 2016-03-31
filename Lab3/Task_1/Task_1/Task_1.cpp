// Task_1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Car.h"

using namespace std;

void PrintCurrentState(CCar const & car)
{
	cout << "State engine " << car.IsTurnedOn() << endl;
	switch (static_cast<Direction>(car.GetDirection()))
	{
	case Direction::STAND:
		cout << "Car stay at now!" << endl;
		break;
	case Direction::FORWARD:
		cout << "Car move foward at now!" << endl;
		break;
	case Direction::BACK:
		cout << "Car move back at now!" << endl;
		break;
	}
	cout << "Current speed " << car.GetSpeed() << endl;
	cout << "Current gear " << car.GetGear() << endl;
}

void Help()
{
	cout << "Machine control commands: " << endl;
	cout << "TurnOn - engine starts" << endl;
	cout << "TurnOff - shuts off the engine" << endl;
	cout << "SetSpeed X - shuts off the engine" << endl;
	cout << "SetGear X - changes gear" << endl;
	cout << "Info - displays information about the car" << endl;
	cout << "Help - prompts" << endl;
}

int main()
{
	CCar car;
	std::string string;
	int argument;
	Help();
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		std::cin >> string;

		if (string == "TurnOff")
		{
			car.TurnOffEngine();
		}
		else if (string == "TurnOn")
		{
			car.TurnOnEngine();
		}
		else if (string == "SetSpeed")
		{
			std::cin >> argument;
			car.SetSpeed(argument);
		}
		else if (string == "SetGear")
		{
			std::cin >> argument;
			car.SetGear(argument);
		}
		else if (string == "Info")
		{
			PrintCurrentState(car);
		}
		else if (string == "Help")
		{
			Help();
		}
		else
		{
			std::cout << "Invalid command!" << std::endl;
		}
	}

    return 0;
}

