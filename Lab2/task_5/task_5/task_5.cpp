// task_5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>

#include "ExpandTemplate.h"

using namespace std;

bool IsFileEmpty(string const & nameInputFile)
{
	ifstream fin(nameInputFile);
	if (fin.is_open())
	{
		fin.seekg(0, std::ios::end);
		size_t size = static_cast<size_t>(fin.tellg());
		fin.seekg(0, std::ios::beg);
		return size == 0;
	}
	return true;
}

void WriteInFile(string const & nameOutputFile, string const & tpl)
{
	ofstream fout(nameOutputFile, ios_base::app);
	fout << tpl;
}

void FillMapWithParams(int argc, char * argv[], map<string, string> & params)
{
	for (int i = 3; i < (argc - 1); i += 2)
	{
		string key = argv[i];
		string value = argv[i + 1];
		if (!key.empty())
		{
			params.emplace(move(key), move(value));
		}
	}
}

int main(int argc, char * argv[])
{
	if (argc >= 3)
	{
		if (IsFileEmpty(argv[1]))
		{
			return 1;
		}
	
		map<string, string> params;
		FillMapWithParams(argc, argv, params);
		ifstream fin(argv[1]);
		string inputString;
		while (getline(fin, inputString))
		{
			WriteInFile(argv[2], ExpandTemplate(inputString, params));
		}

	}
    return 0;
}

