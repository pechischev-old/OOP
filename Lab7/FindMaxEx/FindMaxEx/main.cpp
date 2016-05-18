// FindMaxEx.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "FindMaxEx.h"

using namespace std;


struct Athlete
{
	string name;
	string surname;
	string middleName;
	double weight;
	double growth;
};

void PrintInfoAboutAthlete(Athlete const & athlete)
{
	cout << "Name " << athlete.name << endl;
	cout << "Middle name " << athlete.middleName << endl;
	cout << "Surname " << athlete.surname << endl;
	cout << "Weight" << athlete.weight << endl;
	cout << "Growth " << athlete.growth << endl;;
}

Athlete SetAthlete(string const & str)
{
	istringstream strm(str);
	Athlete athlete;

	strm >> athlete.name;
	strm >> athlete.middleName;
	strm >> athlete.surname;
	strm >> athlete.weight;
	strm >> athlete.growth;
	return athlete;
}

int main()
{
	vector<Athlete> athletes;
	string inputStr;
	while (getline(cin, inputStr))
	{
		athletes.push_back(SetAthlete(inputStr));
	}

	Athlete athleteWithMaxWeight;
	if (FindMax(athletes, athleteWithMaxWeight, [](Athlete const & lhs, Athlete const & rhs) {
		return lhs.weight < rhs.weight;
	}))
	{
		PrintInfoAboutAthlete(athleteWithMaxWeight);
	}

	Athlete athleteWithMaxGrowth;
	if (FindMax(athletes, athleteWithMaxGrowth, [](Athlete const & lhs, Athlete const & rhs) {
		return lhs.growth < rhs.growth;
	}))
	{
		PrintInfoAboutAthlete(athleteWithMaxGrowth);
	}
    return 0;
}

