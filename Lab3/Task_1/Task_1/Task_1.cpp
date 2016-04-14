// Task_1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Car.h"

using namespace std;

void PrintCurrentState(CCar const & car)
{
	cout << "State engine " << car.IsTurnedOn() << endl;
	switch (car.GetDirection())
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

void PrintHelp()
{
	cout << "Machine control commands: " << endl;
	cout << "TurnOn - starts engine" << endl;
	cout << "TurnOff - shuts off the engine" << endl;
	cout << "SetSpeed X - rate of change in the X" << endl;
	cout << "SetGear X - switching gear" << endl;
	cout << "Info - displays information about the car" << endl;
	cout << "Help - prompts" << endl;
}

Gear StringToGear(std::string const & gear)
{
	if (gear == "reverse")
		return Gear::REVERSE;
	else if (gear == "neutral")
		return Gear::NEUTRAL;
	else if (gear == "first")
		return Gear::FIRST;
	else if (gear == "second")
		return Gear::SECOND;
	else if (gear == "third")
		return Gear::THIRD;
	else if (gear == "fourth")
		return Gear::FOURTH;
	else if (gear == "fifth")
		return Gear::FIFTH;
	return Gear::NEUTRAL;
}

void ProcessInstructionsLoop(CCar & car)
{
	std::string string;
	int argument;
	PrintHelp();
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
			std::string gear;
			std::cin >> gear;
			car.SetGear(StringToGear(gear));
		}
		else if (string == "Info")
		{
			PrintCurrentState(car);
		}
		else if (string == "Help")
		{
			PrintHelp();
		}
		else
		{
			std::cout << "Invalid command!" << std::endl;
		}
	}
}

int main()
{
	CCar car;
	ProcessInstructionsLoop(car);

    return 0;
}

