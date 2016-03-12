#include "MainProcess.h"

using namespace std;


bool CheckFirstAndLastSymbols(const char & first1, const char & first2, const char & last1, const char & last2) {
	return first1 == first2 && last1 == last2;
}

bool FindSubstr(const string & str, const size_t & index, const string & substr)
{
	if ((str.length() - index) >= substr.size() && substr.size() > 0)
		if (CheckFirstAndLastSymbols(str[index], substr[0], str[index + substr.length() - 1], substr.back()))
			return (str.substr(index, substr.length()) == substr);
	return false;
}

string FindAndReplace(string const & subject, string const & search, string const & replace)
{
	string outputStr;
	bool canReplace = search.size() > 0;
	if (canReplace)
	{
		size_t lenghtSearch = search.size();
		for (size_t i = 0; i < subject.length();)
		{
			if (FindSubstr(subject, i, search))
			{
				i += lenghtSearch;
				outputStr += replace;
			}
			else
			{
				outputStr += subject[i];
				++i;
			}
		}
	}
	else
	{
		return subject;
	}
	return outputStr;
}