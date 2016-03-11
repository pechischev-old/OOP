#include "MapProcess.h"

using namespace std;

bool AddNewWordInDictionary(Dictionary & dict, Dictionary & dictNewWords, string const & key, string const & value) 
{
	if (!value.empty())
	{
		// TODO: ������� key
		dict.emplace(move(key), move(value));
		dictNewWords.emplace(move(key), move(value));
		return true;
	}
	return false;
}

string FindValueOnKey(Dictionary & dict, string key)
{
	// TODO: �������
	auto iterator = dict.find(key);
	if (iterator != dict.end())
		return iterator->second;
	return "";
}

void UserInteraction(Dictionary & dict, std::string const & fileName) // TODO: ������� ������ ����������
{ // TODO: ��������� ������ ������
	string inputStr; // TODO: �������������
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
		cout << "����������� ����� �" << inputStr << "�. ������� ������� ��� ������ ������ ��� ������." << endl;
		string value;
		getline(cin, value);
		if (AddNewWordInDictionary(dict, dictNewWords, inputStr, value))
		{
			cout << "����� �" << inputStr << "� ��������� � ������� ��� �" << value << "�" << endl;
			hasAdded = true;
			continue;
		}
		cout << "����� �" << inputStr << "� ���������������." << endl;
	} 
	cout << "ended" << endl;
	if (hasAdded) {
		char change;
		cout << "� ������� ���� ������� ���������. ������� Y ��� N ��� ���������� ����� ������� : ";
		cin >> change;
		if (toupper(change) == 'Y')
		{
			// ������ � ���� dictNewWords, �.�. ���������� � ����� �����
			cout << "��������� ���������. �� ��������." << endl;
		}
	}
}

void ProcessMap(Dictionary & dict, std::string const & fileName)
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	UserInteraction(dict, fileName);

}

