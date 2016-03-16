#include "MapProcess.h"

using namespace std;

bool CheckWord(string word)
{
	/*for (auto letter : word) {
		bool isRussianLetter = 'А' <= toupper(int(letter)) && toupper(int(letter)) <= 'Я';
		bool isEnglishLetter = 'A' <= toupper(int(letter)) && toupper(int(letter)) <= 'Z';
		if (!isRussianLetter && !isEnglishLetter) 
			return false;
	}
	return true;*/
	return all_of(word.begin(), word.end(), [](char letter) 
	{ 
		bool isRussianLetter = 'А' <= toupper(letter) && toupper(letter) <= 'Я';
		bool isEnglishLetter = 'A' <= toupper(int(letter)) && toupper(int(letter)) <= 'Z';
		return isEnglishLetter && isRussianLetter;
	});
}

bool AddNewWordInDictionary(Dictionary & dict, string const & key, string const & value) 
{
	if ((!value.empty()) && (!key.empty()))
	{
		// TODO: регистр key
		dict.emplace(move(key), move(value));
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

void UserInteraction(Dictionary & dict, std::string const & fileName) // TODO: слишком кривая реализация
{ 
	string inputStr; // TODO: переименовать
	Dictionary dictNewWords;
	bool wasAdd = false;
	
	while (cout << ">" && getline(cin, inputStr))
	{
		if (inputStr == "...")
		{
			break;
		}
		else if (inputStr.empty())
		{
			continue;
		}
		//--
		string findedValue = FindValueOnKey(dict, inputStr);
		if (!findedValue.empty()) 
		{
			cout << findedValue << endl;
			continue;
		}
		
		cout << "Неизвестное слово “" << inputStr << "”. Введите перевод или пустую строку для отказа." << endl;
		string value;
		getline(cin, value);
		if (AddNewWordInDictionary(dict, inputStr, value))
		{
			AddNewWordInDictionary(dictNewWords, inputStr, value);
			cout << "Слово “" << inputStr << "” сохранено в словаре как “" << value << "”" << endl;
			wasAdd = true;
			continue;
		}
		cout << "Слово “" << inputStr << "” проигнорировано." << endl;
		//------
	} 
	if (wasAdd) {
		WillSave(dictNewWords, fileName);
	}
}

void WriteNewWordsInFile(Dictionary & dictNewWords, std::string const & fileName)
{
	ofstream fout(fileName, ios_base::app);
	for (auto it : dictNewWords)
	{
		fout << it.first << ":" << it.second << endl;
	}
}

void WillSave(Dictionary & dictNewWords, std::string const & fileName)
{
	char change;
	cout << "В словарь были внесены изменения. Введите Y или N для сохранения перед выходом: ";
	cin >> change;
	if (toupper(change) == 'Y')
	{
		WriteNewWordsInFile(dictNewWords, fileName);
		cout << "Изменения сохранены. До свидания." << endl;
	}
}

void ProcessMap(Dictionary & dict, std::string const & fileName)
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	UserInteraction(dict, fileName);
}

bool IsFileNotEmpty(string const & fileName)
{
	ifstream fin(fileName);
	if (fin.is_open())
	{
		fin.seekg(0, std::ios::end);
		size_t size = static_cast<size_t>(fin.tellg());
		fin.seekg(0, std::ios::beg);
		return size != 0;
	}
	return false;
}

void FillDictionary(string const & fileName, Dictionary & dict)
{
	if (IsFileNotEmpty(fileName))
	{
		ifstream fin(fileName);
		string inputString;
		while (getline(fin, inputString))
		{
			vector<string> pairDict;
			boost::split(pairDict, inputString, boost::is_any_of(":"));
			dict.emplace(move(pairDict[0]), move(pairDict[1]));
		}
	}
}