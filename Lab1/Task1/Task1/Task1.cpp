// Task1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

#include "ConstVar.h"

using namespace std;



bool CheckFileSize(ifstream & inputFile)
{
	inputFile.seekg(0, std::ios::end);
	size_t size = static_cast<size_t>(inputFile.tellg());
	inputFile.seekg(0, std::ios::beg);
	return size >= MAX_FILE_SIZE;
}

bool CheckInputValidation(int argc, char* argv[]) 
{
	if (argc != MAX_AMOUNT_ARGUMENTS)
	{
		cout << NO_ARGUMENTS << endl;
		cout << INPUT_FORMAT << endl;
		return false;
	}
	ifstream fin(argv[1]);
	if (!fin.is_open()) 
	{
		cout << argv[1] + NOT_OPEN << endl;
		return false;
	}
	if (CheckFileSize(fin)) {
		cout << argv[1] + ERROR_BIG_FILE_SIZE << endl;
		return false;
	}
	ofstream fout(argv[2]);
	if (!fout.is_open()) 
	{
		cout << argv[2] + NOT_OPEN << endl;
		return false;
	}
	fout.close();
	return true;
}

void WriteInFile(ofstream & fout, const string & outputStr)
{
	fout << outputStr;
}

bool CheckFirstAndLastSymbols(const char & first1, const char & first2, const char & last1, const char & last2 ) {
	return first1 == first2 && last1 == last2;
}

bool FindSubstr(const string & str, const size_t & index, const string & substr) 
{
	
	if ((str.length() - index) >= substr.size() && substr.size() > 0)
		if (CheckFirstAndLastSymbols(str[index], substr[0], str[index + substr.length() - 1], substr.back()))
			return (str.substr(index, substr.length()) == substr);
	return false;

}

string ReplaceString(const string & str, const string & searchStr, const string & replaceStr)
{
	string outputStr;
	bool canReplace = searchStr.size() > 0;
	if (canReplace)
	{
		for (size_t i = 0; i < str.length();)
		{
			if (FindSubstr(str, i, searchStr))
			{
				i = i + searchStr.size();
				outputStr += replaceStr;
			}
			else
			{
				outputStr += str[i];
				++i;
			}
		}
	}
	else
		outputStr = str;
	return outputStr;
}

void Run(char* argv[])
{
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	string searchString = argv[3];
	string replaceString = argv[4];
	string buffStr;
	while (getline(fin, buffStr))
	{
		buffStr += '\n';
		string outputStr = ReplaceString(buffStr, searchString, replaceString);
		WriteInFile(fout, outputStr);
	}
	
	if (!fout.flush())
	{
		cout << NOT_WRITE + argv[2] << endl;
	};
}

int main(int argc, char* argv[])
{
	if (CheckInputValidation(argc, argv))
		Run(argv);
	else
		return 1;
	return 0;
}