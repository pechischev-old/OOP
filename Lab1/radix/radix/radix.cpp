// radix.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

static const int MAX_AMOUNT_ARGUMENTS = 4;
static const string NOT_ARGUMENT = "no required arguments";
static const string FORMAT_STRING = "MyProgram.exe sourceNotation destinationNotation value";

typedef vector<int> arrayInt;

struct  SProgramData {
	int sourceNotation;
	int destinationNotation;
	string value;
	bool wasError;
};

void IntToString(SProgramData & progData, const arrayInt & numbers) {
	string newValueStr;
	for (size_t i = 0; i < numbers.size(); ++i) {
		if (numbers[i] == progData.sourceNotation) {
			progData.wasError = true;
			//TODO: output warnings
			break;
		}
		else if (numbers[i] >= 10) {
			newValueStr += 'A' + numbers[i] - 10;
		}
		else {
			newValueStr += numbers[i] + 48;
		}
	}
	progData.value = newValueStr;
}

arrayInt StringToInt(SProgramData & progData) {
	char letter = 'A';
	int base = progData.sourceNotation;
	arrayInt arr;
	for (size_t i = 0; i < progData.value.size(); ++i) {
		if (isdigit(progData.value[i])) {
			arr.push_back(progData.value[i] - 48);
		}
		else if (progData.value[i] < (letter + base - 10)) {
			arr.push_back(10 + progData.value[i] - letter);
		}
		else {
			progData.wasError = true;
			//TODO: output warnings
			break;
		}
	}
	return arr;
}

void TransferToDecimalNotation(SProgramData & progData) {
	int base = progData.sourceNotation;
	size_t len = progData.value.length();
	int newValue = 0;
	int power = len - 1;
	arrayInt arrNumbers = StringToInt(progData); // TODO: проверить на пустоту
	for (size_t i = 0; i < len; ++i) { 
		newValue += arrNumbers[i] * static_cast<int>(pow(base, power));
		--power;
	}
	progData.sourceNotation = 10;
	// TODO: перевод в string
	std::stringstream ss;
	ss << newValue;
	ss >> progData.value ;

}

void TransferIntoOtherNotation(SProgramData & progData) {
	int base = progData.destinationNotation;
	int valueInt = atoi(progData.value.c_str()); 
	int remain;
	vector<int> arrRemain;  // TODO: ошибка
	if (valueInt == 0)
		arrRemain.push_back(valueInt);
	while (valueInt > 0) {
		remain = valueInt % base;
		valueInt /= base;
		arrRemain.insert(arrRemain.begin(), remain);
	}
	IntToString(progData, arrRemain);
}

bool InitProgram(int argc, char* argv[], SProgramData & progData) {
	
	progData.sourceNotation = 15;
	progData.destinationNotation = 3;
	progData.value = "0121";
	progData.wasError = false;
	/*if (argc == MAX_AMOUNT_ARGUMENTS) { // TODO: вынести в константы строки
		if (argv[1] == argv[2]) 
		{
			cout << "Совпадение систем счисления" << endl;
			return false;
		}
		else if (!(2 <= argv[1] && argv[1] <= 36)) // вынести в отдельную функцию
		{	
			cout << "сс не соответсвует условию задачи" <<endl;
			return false;
		}
		else if (!(2 <= argv[2] && argv[1] <= 36))
		{
			cout << "сс не соответсвует условию задачи" <<endl; 
			return false;
		}
		progData.sourceNotation = atoi(argv[1]);
		progData.destinationNotation = atoi(argv[2]);
		progData.value = argv[3];
		progData.wasError = false;
	}
	else {
		cout << NOT_ARGUMENT << endl;
		cout << FORMAT_STRING << endl;
		return false;
	}*/
	return true;
}

void Output(string value) {
	cout << value << endl;
}

void Run(SProgramData & progData) {
	if (progData.sourceNotation != 10) {
		TransferToDecimalNotation(progData);
	}
	if (!progData.wasError) {
		TransferIntoOtherNotation(progData);
		cout << endl; // delete string
		Output(progData.value);
	}
}

int main(int argc, char* argv[]) {
	SProgramData progData;
	if (InitProgram(argc, argv, progData))
		Run(progData);
	system("pause");
    return 0;
}

