// radix.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "ConstVar.h"

using namespace std;

typedef vector<int> arrayInt;

struct  SProgramData 
{
	int sourceNotation;
	int destinationNotation;
	string value;
	bool wasError;
	char sign;
};

void IntToString(const int & sourceBase, bool & wasError, string & value, const arrayInt & numbers)
{
	string newValueStr;
	for (size_t i = 0; i < numbers.size(); ++i) 
	{
		if (numbers[i] >= sourceBase)
		{
			wasError = true;
			cout << EXCESS_ERROR << endl;
			break;
		}
		else if (numbers[i] >= DECIMAL_BASE) 
			newValueStr += FIRST_LETTER + numbers[i] - DECIMAL_BASE;
		else 
			newValueStr += numbers[i] + SHIFT_CHAR;
	}
	value = newValueStr;
}

arrayInt StringToInt(const int & sourceBase, bool & wasError, const string & value) 
{
	arrayInt arr;
	for (size_t i = 0; i < value.size(); ++i) 
	{
		if (isdigit(value[i]) && value[i] < sourceBase + SHIFT_CHAR)
			arr.push_back(value[i] - SHIFT_CHAR);
		else if (value[i] < (FIRST_LETTER + sourceBase - DECIMAL_BASE) && isalpha(value[i]))
			arr.push_back(DECIMAL_BASE + value[i] - FIRST_LETTER);
		else {
			wasError = true;
			cout << EXCESS_ERROR << endl;
			break;
		}
	}
	return arr;
}

string TranslationInString(const int & valueDecimal) {
	string valueStr;
	std::stringstream str;
	str << valueDecimal;
	str >> valueStr;
	return valueStr;
}

void TransferToDecimalNotation(int & sourceBase, bool & wasError, string & value) 
{
	arrayInt arrNumbers = StringToInt(sourceBase, wasError, value); // TODO: проверить на пустоту
	if (!wasError) 
	{
		int valueDecimal = 0;
		int power = value.length() - 1;
		for (size_t i = 0; i < value.length(); ++i)
		{
			valueDecimal += arrNumbers[i] * static_cast<int>(pow(sourceBase, power));
			--power;
		}
		sourceBase = DECIMAL_BASE;
		value = TranslationInString(valueDecimal);
		// сравнение на допустимую длину 
	}
}

void TransferIntoOtherNotation(const int & destinationBase, const int & sourceBase, bool & wasError, string & value)
{
	int valueInt = atoi(value.c_str()); 
	int remain;
	vector<int> arrRemain;
	if (valueInt == 0)
		arrRemain.push_back(valueInt);
	while (valueInt > 0) {
		remain = valueInt % destinationBase;
		valueInt /= destinationBase;
		arrRemain.insert(arrRemain.begin(), remain);
	}
	IntToString(sourceBase, wasError, value, arrRemain);
}

void RememberSign(char & sign, string & value) // TODO: переименовать функцию
{
	sign = !isalnum(value[0]) ? value[0] : '\0';
	value = (sign == '-') ? value.substr(1, value.length()) : value;
}

bool InitProgram(int argc, char* argv[], SProgramData & progData) 
{
	if (argc == MAX_AMOUNT_ARGUMENTS)
		{ 
		if (argv[1] == argv[2]) 
		{
			cout << COINCIDENCE_NOTATION << endl;
			return false;
		}
		if (!(MIN_NOTATION <= atoi(argv[1]) && atoi(argv[1]) <= MAX_NOTATION))
		{	
			cout << DISPARITY <<endl;
			return false;
		}
		if (!(MIN_NOTATION <= atoi(argv[2]) && atoi(argv[2]) <= MAX_NOTATION))
		{
			cout << DISPARITY << endl; 
			return false;
		}
		progData.sourceNotation = atoi(argv[1]);
		progData.destinationNotation = atoi(argv[2]);
		progData.value = argv[3];
		progData.wasError = false;
		RememberSign(progData.sign, progData.value);
	}
	else 
	{
		cout << NOT_ARGUMENT << endl;
		cout << FORMAT_STRING << endl;
		return false;
	}
	return true;
}

void Output(string value, char sign)
{
	if (sign == '-')
		cout << sign + value << endl;
	else
		cout << value << endl;
}

void Run(SProgramData & progData) 
{
	if (progData.sourceNotation != DECIMAL_BASE) 
		TransferToDecimalNotation(progData.sourceNotation, progData.wasError, progData.value);
	if (!progData.wasError)
	{
		TransferIntoOtherNotation(progData.destinationNotation, progData.sourceNotation, progData.wasError, progData.value);
		Output(progData.value, progData.sign);
	}
}

int main(int argc, char* argv[]) 
{
	SProgramData progData;
	if (InitProgram(argc, argv, progData))
		Run(progData);
	//system("pause");
    return 0;
}

