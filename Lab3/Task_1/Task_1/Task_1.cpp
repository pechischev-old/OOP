// Task_1.cpp: ���������� ����� ����� ��� ����������� ����������.
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

Gear GetGear(std::string const & gear)
{
	if (gear == "reverse")
		return Gear::reverse;
	else if (gear == "neutral")
		return Gear::neutral;
	else if (gear == "first")
		return Gear::first;
	else if (gear == "second")
		return Gear::second;
	else if (gear == "third")
		return Gear::third;
	else if (gear == "fourth")
		return Gear::fourth;
	else if (gear == "fifth")
		return Gear::fifth;
	return Gear::neutral;
}

void UserInterface(CCar & car)
{
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
			std::string gear;
			std::cin >> gear;
			car.SetGear(GetGear(gear));
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
}

int main()
{
	CCar car;
	UserInterface(car);

    return 0;
}

