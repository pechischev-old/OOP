// HTTPURL.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "HttpUrl.h"


using namespace std;

vector<string> ParseArg(string const & inputStr)
{
	string arg;
	istringstream strm(inputStr);
	vector<string> args;

	while (strm >> arg)
	{
		args.push_back(arg);
	}

	return args;
}

shared_ptr<CHttpUrl> MakePtrUrl(string const & inputStr)
{
	auto args = ParseArg(inputStr);

	shared_ptr<CHttpUrl> url;

	switch (args.size())
	{
	case (1) :
		url = make_shared<CHttpUrl>(args[0]);
		break;
	case (2) :
		url = make_shared<CHttpUrl>(args[0], args[1]);
		break;
	case (3) :
		url = make_shared<CHttpUrl>(args[0], args[1], url->ToProtocol(args[2]));
		break;
	case (4) :
		url = make_shared<CHttpUrl>(args[0], args[1], url->ToProtocol(args[2]), boost::lexical_cast<unsigned short>(args[3]));
		break;
	}
	if (!url)
	{
		throw invalid_argument("Invalid arguments count.");
	}
	return url;
}

void OutputInformationAboutURL(shared_ptr<CHttpUrl> const & url)
{
	cout << "//////////////////////" << endl;
	cout << "URL " << url->GetURL() << endl;
	cout << "Protocol " << url->ToStringProtocol() << endl;
	cout << "Domain " << url->GetDomain() << endl;
	cout << "Port " << url->GetPort() << endl;
	cout << "Document " << url->GetDocument() << endl;
	cout << "//////////////////////" << endl;
}

void UserInteraction()
{
	string inputURL;
	while ((std::cout << "> ") && getline(cin, inputURL))
	{
		try
		{
			if (inputURL.empty())
			{
				throw invalid_argument("The input string is empty");
			}
			auto url = MakePtrUrl(inputURL);
			OutputInformationAboutURL(url);
		}
		catch (invalid_argument const & exception)
		{
			cout << exception.what() << endl;
		}
		catch (...)
		{
			cout << "Unknow error type" << endl;
		}
	}
}

int main()
{
	UserInteraction();
    return 0;
}

