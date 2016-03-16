// task2.cpp: определяет точку входа для консольного приложения.
//

#define _SCL_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "MapProcess.h"

using namespace std;


int main(int argc, char *argv[])
{
	if (argc <= 2) 
	{
		Dictionary dict;
		string fileName = argv[1];
		if (fileName.empty())
		{
			return 0;
		}
		FillDictionary(fileName, dict);
		ProcessMap(dict, fileName);

	}

    return 0;
}

