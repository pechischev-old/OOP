// FindAndReplace.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "MainProcess.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		string inputStr;
		while (getline(cin, inputStr))
		{
			if (inputStr.empty())
			{
				break;
			}
			cout << FindAndReplace(inputStr, argv[1], argv[2]) << endl;
		}
	}
    return 0;
}

