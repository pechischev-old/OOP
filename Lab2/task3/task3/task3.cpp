// task2.cpp: определяет точку входа для консольного приложения.
//



#include "stdafx.h"
#include "MapProcess.h"

using namespace std;


int main(int argc, char *argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	if (argc <= 2) 
	{
		Dictionary dict;
		string fileName = argv[1];
		if (!fileName.empty())
		{
			FillDictionary(fileName, dict);
			ProcessMap(dict, fileName);
		}
	}
    return 0;
}

