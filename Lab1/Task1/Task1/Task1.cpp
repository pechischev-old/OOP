// Task1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

static const int MAX_AMOUNT_ARGUMENTS = 5;

struct SProgramData {
	string inputFileName;
	string outputFileName;
	string searchString;
	string replaceString;
	ifstream fin;
	ofstream fout;
	bool canChange;
};


void ExitProgram() {
	exit(1);
}

void InitProgram(int argc, char* argv[], SProgramData & progData) {
	/*progData.inputFileName = "input.txt";
	progData.outputFileName = "output.txt";
	progData.searchString = "qwea";
	progData.replaceString = "123";*/
	if (argc == MAX_AMOUNT_ARGUMENTS)
	{
		progData.inputFileName = argv[1];
		progData.outputFileName = argv[2];
		progData.searchString = argv[3];
		progData.replaceString = argv[4];
	}
	else
	{
		cout << "no required arguments" << endl;
		ExitProgram();
	}

	progData.fin.open(progData.inputFileName);
	if (!progData.fin.is_open()) {
		cout << progData.inputFileName + " file can not be opened" << endl;
		ExitProgram();
	}
	
	progData.fout.open(progData.outputFileName);
	if (!progData.fout.is_open()) {
		cout << progData.outputFileName + " file can not be opened" << endl;
		ExitProgram();
	}
}

void WriteInFile(ofstream & fout, string outputStr) {
	fout << outputStr;
}

void ReplaceString(SProgramData & progData, string & buffStr) {
	size_t j = 0;
	string recStr;
	string rec;
	for (size_t i = 0; i < buffStr.length(); ++i) {
		if (buffStr[i] == progData.searchString[j]) {
			j += 1;
			rec += buffStr[i];
		}
		else {
			recStr += rec + buffStr[i];
			j = 0;
			rec.clear();
		}
		if (j == progData.searchString.length() && progData.canChange) {
			recStr += progData.replaceString;
			j = 0;
			rec.clear();
		}
	}
	WriteInFile(progData.fout, recStr);
	buffStr.clear();
}

void Run(SProgramData & progData) {

	string buffStr;
	progData.canChange = progData.searchString.length() > 0;
	while (getline(progData.fin, buffStr)) {
		buffStr += '\n';
		ReplaceString(progData, buffStr);
	}
	progData.fin.close();
	progData.fout.close();
}

int main(int argc, char* argv[])
{
	SProgramData progData;
	InitProgram(argc, argv, progData);
	Run(progData);
	return 0;
}