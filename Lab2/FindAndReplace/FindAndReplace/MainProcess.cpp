#include "MainProcess.h"
#include <algorithm>
#include <boost/utility/string_ref.hpp>

using namespace std;


bool StringContainsSubstringAtPosition(const boost::string_ref & subjectRef, const string & substr, const size_t & index)
{
	if ((subjectRef.length() - index) >= substr.size() && substr.size() > 0)
	{
		return subjectRef.substr(index, substr.length()) == substr;
	}
	return false;
}

string FindAndReplace(string const & subject, string const & search, string const & replace)
{
	string outputStr;
	bool canReplace = search.size() > 0;
	if (canReplace)
	{
		size_t lenghtSearch = search.size();
		boost::string_ref subjectRef(subject);
		for (size_t index = 0; index < subject.length();)
		{
			if (StringContainsSubstringAtPosition(subjectRef, search, index))
			{
				index += lenghtSearch;
				outputStr += replace;
			}
			else
			{
				outputStr += subject[index];
				++index;
			}
		}
	}
	else
	{
		return subject;
	}
	return outputStr;
}