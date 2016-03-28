// Task_1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Car.h"
#include "RemoteController.h"

using namespace std;

int main()
{
	CCar car;
	CRemoteController remoteControl(car, cin, cout);
	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!remoteControl.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
    return 0;
}

