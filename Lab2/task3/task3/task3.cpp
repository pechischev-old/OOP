// task2.cpp: определяет точку входа для консольного приложения.
//

#define _SCL_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "MapProcess.h"


#include "boost/algorithm/string.hpp"

using namespace std;


bool IsFileNotEmpty(string const & fileName) 
{
	ifstream fin(fileName);
	if (fin.is_open())
	{
		fin.seekg(0, std::ios::end);
		size_t size = static_cast<size_t>(fin.tellg());
		fin.seekg(0, std::ios::beg);
		return size != 0;
	}
	return false;
}

void FillDictionary(string const & fileName, Dictionary & dict)
{
	ifstream fin(fileName);
	string inputString;
	while (getline(fin, inputString)) 
	{
		vector<string> pairDict;
		boost::split(pairDict, inputString, boost::is_any_of(":"));
		dict.emplace(move(pairDict[0]), move(pairDict[1]));
	}
}

int main(int argc, char *argv[])
{
	if (argc <= 2) 
	{
		Dictionary dict;
		string fileName = "";//argv[1];
		if (IsFileNotEmpty(fileName))
		{
			FillDictionary(fileName, dict);
		}
		ProcessMap(dict, fileName);

	}

    return 0;
}

