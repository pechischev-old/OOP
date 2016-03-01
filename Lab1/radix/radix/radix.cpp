// radix.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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

string FromArrayIntToString(const int & sourceBase, bool & wasError, const arrayInt & numbers, const int & destinationBase)
{
	string newValueStr;
	for (size_t i = 0; i < numbers.size(); ++i) 
	{
		if (numbers[i] >= destinationBase)
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
	if (wasError)
		return "";
	return newValueStr;
}

arrayInt FromStringToArrayInt(const int & sourceBase, const string & value) 
{
	arrayInt arr;
	for (auto symbol : value) 
	{
		if (isdigit(symbol))
			arr.push_back(symbol - SHIFT_CHAR);
		else if (isalpha(symbol))
			arr.push_back(DECIMAL_BASE + char(toupper(symbol)) - FIRST_LETTER);
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

string TransferToDecimalNotation(int & sourceBase, bool & wasError, const string & value) 
{
	arrayInt arrNumbers = FromStringToArrayInt(sourceBase, value); 
	wasError = arrNumbers.empty();
	if (!wasError) 
	{
		int valueDecimal = 0;
		size_t power = arrNumbers.size() - 1;
		for (auto number : arrNumbers)
		{
			valueDecimal += (number * static_cast<int>(pow(sourceBase, power)));
			--power;
		}
		sourceBase = DECIMAL_BASE;
		return TranslationInString(valueDecimal);
	}
	return "";
}

string TransferIntoOtherNotation(const int & destinationBase, const int & sourceBase, bool & wasError,const string & value)
{
	int valueInt = atoi(value.c_str()); 
	int remain;
	vector<int> arrRemain;
	if (valueInt == 0)
		arrRemain.push_back(valueInt);
	while (valueInt > 0)
	{
		remain = valueInt % destinationBase;
		valueInt /= destinationBase;
		arrRemain.insert(arrRemain.begin(), remain);
	}

	return FromArrayIntToString(sourceBase, wasError, arrRemain, destinationBase);
}

void RememberSign(char & sign, string & value) 
{
	sign = !isalnum(value[0]) ? value[0] : '\0';
	value = (sign == '-' || sign == '+') ? value.substr(1, value.length()) : value;
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
			cout << DISPARITY << endl;
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
		cout << NO_ARGUMENTS << endl;
		cout << STRING_FORMAT << endl;
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

bool CheckValue(const int & sourceBase, const string & value)
{
	for (auto symbol : value) 
	{
		if ((isdigit(symbol) && symbol >= (sourceBase + SHIFT_CHAR)) ||
			(isalpha(symbol) && char(toupper(symbol)) >= (FIRST_LETTER + sourceBase - DECIMAL_BASE)))
		{
			cout << EXCESS_ERROR << endl;
			return true;
		}
	}
	return false;
}

void Run(SProgramData & progData) 
{
	progData.wasError = CheckValue(progData.sourceNotation, progData.value);
	if (progData.sourceNotation != DECIMAL_BASE && !progData.wasError)
	{
		progData.value = TransferToDecimalNotation(progData.sourceNotation, progData.wasError, progData.value);
	}
	if (!progData.wasError)
	{
		progData.value = TransferIntoOtherNotation(progData.destinationNotation, progData.sourceNotation, progData.wasError, progData.value);
	}
	if (!progData.wasError)
	{
		Output(progData.value, progData.sign);
	}
	
}

int main(int argc, char* argv[]) 
{
	SProgramData progData;
	if (InitProgram(argc, argv, progData))
		Run(progData);
	else
		return 1;
    return 0;
}

