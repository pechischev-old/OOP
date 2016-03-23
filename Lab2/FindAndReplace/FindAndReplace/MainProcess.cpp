#include "MainProcess.h"
#include <algorithm>
#include <boost/utility/string_ref.hpp>

using namespace std;


bool StringContainsSubstringAtPosition(boost::string_ref subjectRef, boost::string_ref searchRef, const size_t & index)
{
	if ((subjectRef.length() - index) >= searchRef.length())
	{
		return subjectRef.substr(index, searchRef.length()) == searchRef;
	}
	return false;
}

string FindAndReplace(string const & subject, string const & search, string const & replace)
{
	string outputStr;
	bool canReplace = search.size() > 0;
	if (!canReplace)
	{
		return subject;
	}
	
	boost::string_ref subjectRef(subject);
	boost::string_ref searchRef(search);
	for (size_t index = 0; index < subject.length();)
	{
		if (StringContainsSubstringAtPosition(subjectRef, searchRef, index))
		{
			index += search.size();
			outputStr += replace;
		}
		else
		{
			outputStr += subject[index];
			++index;
		}
	}
	
	return outputStr;
}