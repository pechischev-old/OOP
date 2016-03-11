#include "MapProcess.h"

using namespace std;

bool AddNewWordInDictionary(Dictionary & dict, Dictionary & dictNewWords, string const & key, string const & value) 
{
	if (!value.empty())
	{
		// TODO: регистр key
		dict.emplace(move(key), move(value));
		dictNewWords.emplace(move(key), move(value));
		return true;
	}
	return false;
}

string FindValueOnKey(Dictionary & dict, string key)
{
	// TODO: регистр
	auto iterator = dict.find(key);
	if (iterator != dict.end())
		return iterator->second;
	return "";
}

void UserInteraction(Dictionary & dict, std::string const & fileName) // TODO: слишком крива€ реализаци€
{ // TODO: учитывает пустую строку
	string inputStr; // TODO: переименовать
	Dictionary dictNewWords;
	bool hasAdded = false;
	
	while (getline(cin, inputStr))
	{
		if (inputStr == "...")
		{
			break;
		}
		string findedValue = FindValueOnKey(dict, inputStr);
		if (!findedValue.empty()) 
		{
			cout << findedValue << endl;
			continue;
		}
		cout << "Ќеизвестное слово У" << inputStr << "Ф. ¬ведите перевод или пустую строку дл€ отказа." << endl;
		string value;
		getline(cin, value);
		if (AddNewWordInDictionary(dict, dictNewWords, inputStr, value))
		{
			cout << "—лово У" << inputStr << "Ф сохранено в словаре как У" << value << "Ф" << endl;
			hasAdded = true;
			continue;
		}
		cout << "—лово У" << inputStr << "Ф проигнорировано." << endl;
	} 
	cout << "ended" << endl;
	if (hasAdded) {
		char change;
		cout << "¬ словарь были внесены изменени€. ¬ведите Y или N дл€ сохранени€ перед выходом : ";
		cin >> change;
		if (toupper(change) == 'Y')
		{
			// запись в файл dictNewWords, т.е. добавление в конец файла
			cout << "»зменени€ сохранены. ƒо свидани€." << endl;
		}
	}
}

void ProcessMap(Dictionary & dict, std::string const & fileName)
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	UserInteraction(dict, fileName);

}

