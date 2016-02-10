// Task1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

static const int MAX_AMOUNT_ARGUMENTS = 5;
static const int MAX_FILE_SIZE = 2147483647;
static const string NO_ARGUMENTS = "no required arguments";
static const string NOT_OPEN = " file can not be opened";
static const string ERROR_BIG_FILE_SIZE = " file size more than two gigabytes";
static const string FORMAT_INPUT = "MyProgram.exe inputFile outputFile searchStrin replaceString";

struct SProgramData 
{
	string searchString;
	string replaceString;
	ifstream fin;
	ofstream fout;
};

bool CheckFileSize(ifstream & inputFile)
{
	inputFile.seekg(0, std::ios::end);
	size_t size = static_cast<size_t>(inputFile.tellg());
	inputFile.seekg(0, std::ios::beg);
	return size >= MAX_FILE_SIZE;
}

bool InitProgram(int argc, char* argv[], SProgramData & progData) 
{
	string inputFileName;
	string outputFileName;
	if (argc == MAX_AMOUNT_ARGUMENTS)
	{
		inputFileName = argv[1];
		outputFileName = argv[2];
		progData.searchString = argv[3];
		progData.replaceString = argv[4];
	}
	else
	{
		cout << NO_ARGUMENTS << endl;
		cout << FORMAT_INPUT << endl;
		return false;
	}
	progData.fin.open(inputFileName);
	if (!progData.fin.is_open()) 
	{
		cout << inputFileName + NOT_OPEN << endl;
		return false;
	}
	if (CheckFileSize(progData.fin)) {
		cout << inputFileName + ERROR_BIG_FILE_SIZE << endl;
		return false;
	}
	progData.fout.open(outputFileName);
	if (!progData.fout.is_open()) 
	{
		cout << outputFileName + NOT_OPEN << endl;
		return false;
	}
	return true;
}

void WriteInFile(ofstream & fout,const string & outputStr)
{
	fout << outputStr;
}

bool FindSubstr(const string & str, const size_t & begin, const string & substr) 
{
	size_t j = 0;
	return str.substr(begin, substr.length()) == substr;
}

void ReplaceString(SProgramData & progData, const string & str)
{
	string outputStr;
	string substr = progData.searchString;
	bool canReplace = substr.size() > 0;
	for (size_t i = 0; i < str.length();) {
		if (FindSubstr(str, i, substr) && (str.length() - i) >= substr.size() && canReplace)
		{
			i = i + substr.size();
			outputStr += progData.replaceString;
		}
		else 
		{
			outputStr += str[i];
			++i;
		}
	}
	WriteInFile(progData.fout, outputStr);
}

void Run(SProgramData & progData) 
{
	string buffStr;
	while (!progData.fin.eof())
	{
		getline(progData.fin, buffStr);
		buffStr += '\n';
		ReplaceString(progData, buffStr);
	}
	progData.fin.close();
	progData.fout.close();
}

int main(int argc, char* argv[])
{
	SProgramData progData;
	if (InitProgram(argc, argv, progData))
		Run(progData);
	return 0;
}