// fill.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

#include "ConstVar.h"

using namespace std;

struct SCoord
{
	size_t i;
	size_t j;
};

using Field = vector<vector<char>>;
using Queue = queue<SCoord>;

void Push(Field & field, size_t i, size_t j, Queue & paths) 
{
	if (i < field.size())
	{
		if (j < field[i].size())
		{
			if (field[i][j] == '#')
			{
				return;
			}
			if (field[i][j] == '.')
			{
				return;
			}
			if (field[i][j] == ' ')
			{
				field[i][j] = '.';
			}
			paths.push({ i + 1, j });
			paths.push({ i - 1, j });
			paths.push({ i, j - 1 });
			paths.push({ i, j + 1 });		
		}
	}
}

void Fill(Field & field, size_t i, size_t j)
{
	Queue paths;
	do 
	{
		if (paths.size() > 0) 
		{
			i = paths.front().i;
			j = paths.front().j;
			paths.pop();
			if (i >= field.size())
			{
				continue;
			}
			if (i < field.size())
			{
				if (j >= field[i].size())
				{
					continue;
				}
			}
		}
		Push(field, i, j, paths);
	}
	while (!paths.empty());
}

void RunProgram(Field & field)
{
	for (size_t i = 0; i < field.size(); ++i)
	{
		for (size_t j = 0; j < field[i].size(); ++j)
		{
			if (field[i][j] == 'O')
			{
				Fill(field, i, j);
			}
		}
	}
}

void FillArray(Field & field, const string & inputFileStr)
{
	ifstream fin(inputFileStr);
	string inputStr;
	while (getline(fin, inputStr) && field.size() < MAX_SIZE)
	{
		vector<char> buffArray;
		size_t length = min<size_t>(inputStr.length(), MAX_SIZE);
		for (size_t i = 0; i < length; ++i)
		{
			buffArray.push_back(toupper(int(inputStr[i])));
		}
		
		field.push_back(buffArray);
	}
}

bool IsAllowedSymbol(const char & symbol)
{
	return (symbol == ' ' || toupper(static_cast<int>(symbol)) == 'O' || symbol == '#' || symbol == '\n' || symbol == '\0');
}

bool CheckFileContent(const string & inputFileStr) 
{
	ifstream fin(inputFileStr);
	if (!fin.is_open()) 
	{
		cout << inputFileStr + NOT_OPEN << endl;
		return false;
	}
	string inputStr;
	while (getline(fin, inputStr))
	{
		for (auto symbol : inputStr) 
		{
			if (!IsAllowedSymbol(symbol)) 
			{
				cout << INVALID_CHARACTER << endl;
				return false;
			}
		}
	}
	return true;
}

bool InitProgram(std::vector<std::string> const& args, Field & field)
{
	if (args.size() == MAX_AMOUNT_ARGUMENTS)
	{
		if (!CheckFileContent(args[1]))
		{
			return false;
		}
		FillArray(field, args[1]);
	}
	else
	{
		cout << NO_ARGUMENTS << endl;
		cout << INPUT_FORMAT << endl;
		return false;
	}
	return true;
}

void WriteInFile(Field & field, const string & nameOutputFile)
{
	ofstream fout(nameOutputFile);
	for (size_t i = 0; i < field.size(); ++i)
	{
		for (size_t j = 0, height = field[i].size(); j < height; ++j)
		{
			fout << field[i][j];
		}
		fout << '\n';
	}
	if (!fout.flush())
	{
		cout << NOT_WRITE + nameOutputFile << endl;
	}
}

int main(int argc, char* argv[])
{
	std::vector<std::string> args(argv, argv + argc);
	Field field;
 	if (InitProgram(args, field))
	{
		RunProgram(field);
		WriteInFile(field, argv[2]);
	}
    	return 0;
}

