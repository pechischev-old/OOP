#include "HttpUrl.h"
#include <algorithm>

using namespace std;

CHttpUrl::CHttpUrl(std::string const & url)
{

}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port)
	: m_domain(VerifyDomain(domain))
	, m_document(VerifyDocument(document))
	, m_protocol(VerifyProtocol(protocol))
	, m_port(port)
{
}

std::string CHttpUrl::GetURL() const
{
	return GetProtocol() + "://" + m_domain + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

URLContainer CHttpUrl::ParseURL(boost::string_ref  & url)
{
	Protocol protocol = ParseProtocol(url);
	std::string domain = ParseDomain(url);
	unsigned short port;
	std::string document = ParseDocument(url);
	
	return URLContainer(protocol, domain, document, port);
}

std::string CHttpUrl::ParseDomain(boost::string_ref & url)
{
	return std::string();
}

std::string CHttpUrl::ParseDocument(boost::string_ref & url)
{
	return std::string();
}

Protocol CHttpUrl::ParseProtocol(boost::string_ref & str)
{
	return Protocol();
}

std::string CHttpUrl::VerifyDomain(std::string const & domain)
{
	if (domain.empty())
	{
		throw invalid_argument("domain name is empty");
	}
	else if (find_if(domain.begin(), domain.end(), [](char ch) { // TODO: проверять маской
		return (isspace(ch) || (ch == '/') || (ch == '\'')); }) != domain.end())
	{
		throw invalid_argument("domain name is contain invalid symbols");
	}

	return domain;
}

std::string CHttpUrl::VerifyDocument(std::string const & document)
{
	if (find_if(document.begin(), document.end(), [&](char ch) {
		return (isspace(ch));
	}) != document.end())
	{
		throw invalid_argument("Document must not contain any spaces or tabulation.");
	}

	if (document[0] != '/')
	{
		return '/' + document;
	}
	return document;
}

Protocol CHttpUrl::VerifyProtocol(Protocol const & protocol)
{
	return protocol;
}
