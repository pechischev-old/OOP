#include "MapProcess.h"
#include <boost/algorithm/string.hpp>

using namespace std;

static bool CheckWord(string const & word)
{
	std::locale loc("");
	return all_of(word.begin(), word.end(), [&](char letter) 
	{
		return std::isalpha(letter, loc);
	});
}

bool AddNewWordToDictionary(Dictionary & dict, string key, string const & value) 
{
	if ((!value.empty() && CheckWord(value)) && (!key.empty() && CheckWord(key)))
	{
		boost::to_lower(key);
		dict.emplace(move(key), move(value));
		return true;
	}
	return false;
}

string FindValueByKey(Dictionary & dict, string key)
{
	boost::to_lower(key);
	auto iterator = dict.find(key);
	if (iterator != dict.end())
	{
		return iterator->second;
	}
	return "";
}

void OutputFindedValue(string const & value)
{
	cout << value << endl;
}

string InputValue(string const & key)
{
	cout << "Неизвестное слово “" << key << "”. Введите перевод или пустую строку для отказа." << endl;
	string value;
	getline(cin, value);
	return value;
}

void InterectWithValue(string const & key, bool & wasAdd, Dictionary & dict, Dictionary & dictNewWords, string value)
{
	if (AddNewWordToDictionary(dict, key, value))
	{
		AddNewWordToDictionary(dictNewWords, key, value);
		cout << "Слово “" << key << "” сохранено в словаре как “" << value << "”" << endl;
		wasAdd = true;
	}
	else
	{
		cout << "Слово “" << key << "” проигнорировано." << endl;
	}
}

void UserInteraction(Dictionary & dict, std::string const & fileName) 
{ 
	string inputStr; 
	Dictionary dictNewWords;
	bool wasAdd = false;
	
	while ((cout << ">") && getline(cin, inputStr))
	{
		if (inputStr == "...")
		{
			break;
		}
		else if (inputStr.empty())
		{
			continue;
		}
		string findedValue = FindValueByKey(dict, inputStr);
		if (!findedValue.empty()) 
		{
			OutputFindedValue(findedValue);
		}
		else
		{
			InterectWithValue(inputStr, wasAdd, dict, dictNewWords, InputValue(inputStr));
		}
	} 
	if (wasAdd) 
	{
		AskForSaveBeforeExit(dictNewWords, fileName);
	}
}

void WriteNewWordsToFile(Dictionary & dictNewWords, std::string const & fileName)
{
	ofstream fout(fileName, ios_base::app);
	for (auto it : dictNewWords)
	{
		fout << it.first << ":" << it.second << endl;
	}
}

void AskForSaveBeforeExit(Dictionary & dictNewWords, std::string const & fileName)
{
	char change = 0;
	cout << "В словарь были внесены изменения. Введите Y или N для сохранения перед выходом: ";
	cin >> change;
	if (toupper(change) == 'Y' )
	{
		WriteNewWordsToFile(dictNewWords, fileName);
		cout << "Изменения сохранены. До свидания." << endl;
	}
}

void ProcessMap(Dictionary & dict, std::string const & fileName)
{
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