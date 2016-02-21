// fill.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "ConstVar.h"

using namespace std;

struct SCoord {
	size_t i;
	size_t j;
};

typedef vector<vector<char>> Field;

typedef vector<SCoord> Queue;

void Push(Field & field, size_t i, size_t j, Queue & paths) {
	if (i < field.size() && i >= 0)
	{
		if (j < field[i].size() && j >= 0)
		{
			if (field[i][j] == '#')
				return;
			if (field[i][j] == '.')
				return;
			if (field[i][j] == ' ')
				field[i][j] = '.';
			paths.push_back({ i + 1, j });
			paths.push_back({ i - 1, j });
			paths.push_back({ i, j - 1 });
			paths.push_back({ i, j + 1 });		
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
			i = paths[0].i;
			j = paths[0].j;
			paths.erase(paths.begin());
			if (i < 0 || i >= field.size())
				continue;
			if (i < field.size() && i >= 0)
			{
				if (j >= field[i].size() || j < 0)
					continue;
			}
		}
		Push(field, i, j, paths);
	} while (!paths.empty());
}

void Run(Field & field)
{
	for (size_t i = 0; i < field.size(); ++i)
	{
		for (size_t j = 0; j < field[i].size(); ++j)
		{
			if (field[i][j] == 'O') 
				Fill(field, i, j);
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
		size_t length = (inputStr.length() < MAX_SIZE) ? inputStr.length() : MAX_SIZE;
		for (size_t i = 0; i < length; ++i)
			buffArray.push_back(toupper(int(inputStr[i])));
		
		field.push_back(buffArray);
	}
}

bool IsCorrectSymbol(const char & symbol)
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
	string inputStr = "";
	while (getline(fin, inputStr))
	{
		for (auto symbol : inputStr) 
		{
			if (!IsCorrectSymbol(symbol)) 
			{
				cout << INVALID_CHARACTER << endl;
				return false;
			}
		}
	}
	return true;
}

bool InitProgram(int argc, char* argv[], Field & field)
{
	if (argc == MAX_AMOUNT_ARGUMENTS)
	{
		if (!CheckFileContent(argv[1]))
			return false;
		FillArray(field, argv[1]);
	}
	else
	{
		cout << NO_ARGUMENTS << endl;
		cout << INPUT_FORMAT << endl;
		return false;
	}
	return true;
}

void WriteInFile(Field & field,const string & nameOutputFile)
{
	ofstream fout(nameOutputFile);
	for (size_t i = 0; i < field.size(); ++i)
	{
		for (size_t j = 0; j < field[i].size(); ++j)
		{
			fout << field[i][j];
		}
		fout << '\n';
	}
	if (!fout.flush()) {
		cout << NOT_WRITE + nameOutputFile << endl;
	}
}

int main(int argc, char* argv[])
{
	Field field;
 	if (InitProgram(argc, argv, field))
	{
		Run(field);
		WriteInFile(field, argv[2]);
	}
    return 0;
}

