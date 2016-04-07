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

string DigitsToString(bool & wasError, arrayInt digits, int destinationBase)
{
	string newValueStr;
	for (size_t i = 0; i < digits.size(); ++i) 
	{
		if (digits[i] >= destinationBase)
		{
			wasError = true;
			cout << EXCESS_ERROR << endl;
			break;
		}
		else if (digits[i] >= DECIMAL_BASE) 
			newValueStr += FIRST_LETTER + digits[i] - DECIMAL_BASE;
		else 
			newValueStr += digits[i] + SHIFT_CHAR;
	}
	if (wasError)
		return "";
	return newValueStr;
}

arrayInt StringToDigitsArray(int sourceBase, string value) 
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

string TranslationInString(int valueDecimal) {
	string valueStr;
	std::stringstream str;
	str << valueDecimal;
	str >> valueStr;
	return valueStr;
}

string TransferToDecimalNotation(int & sourceBase, bool & wasError, string value) 
{
	arrayInt arrDigits = StringToDigitsArray(sourceBase, value); 
	wasError = arrDigits.empty();
	if (!wasError) 
	{
		int valueDecimal = 0;
		size_t power = arrDigits.size() - 1;
		for (auto number : arrDigits)
		{
			valueDecimal += (number * static_cast<int>(pow(sourceBase, power)));
			--power;
		}
		sourceBase = DECIMAL_BASE;
		return TranslationInString(valueDecimal);
	}
	return "";
}

string TransferIntoOtherNotation(int destinationBase, bool & wasError, string value)
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

	return DigitsToString(wasError, arrRemain, destinationBase);
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
			progData.wasError = true;
			return false;
		}
		if (!(MIN_NOTATION <= atoi(argv[1]) && atoi(argv[1]) <= MAX_NOTATION))
		{	
			cout << DISPARITY << endl;
			progData.wasError = true;
			return false;
		}
		if (!(MIN_NOTATION <= atoi(argv[2]) && atoi(argv[2]) <= MAX_NOTATION))
		{
			cout << DISPARITY << endl; 
			progData.wasError = true;
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

bool CheckValue(int sourceBase, string value)
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

void RunProgram(SProgramData & progData) 
{
	progData.wasError = CheckValue(progData.sourceNotation, progData.value);
	if (progData.sourceNotation != DECIMAL_BASE && !progData.wasError)
	{
		progData.value = TransferToDecimalNotation(progData.sourceNotation, progData.wasError, progData.value);
	}
	if (!progData.wasError)
	{
		progData.value = TransferIntoOtherNotation(progData.destinationNotation, progData.wasError, progData.value);
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
		RunProgram(progData);
	if (progData.wasError)
		return 1;
    return 0;
}

