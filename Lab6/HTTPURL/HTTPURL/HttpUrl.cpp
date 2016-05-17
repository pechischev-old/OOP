#include "HttpUrl.h"

#include <algorithm>

using namespace std;

CHttpUrl::CHttpUrl(std::string const & url)
{
	tie(m_protocol, m_domain, m_document, m_port) = ParseURL(boost::string_ref(url));
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
	bool isOtherPort = (m_port == 80 || m_port == 443);
	return ToStringProtocol() + "://" + m_domain + (isOtherPort ? "" : ":"+ to_string(m_port)) + m_document;
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

Protocol CHttpUrl::ToProtocol(std::string const & protocolStr) const
{
	if (protocolStr == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocolStr == "https")
	{
		return Protocol::HTTPS;
	}
	throw CUrlParsingError("Invalid protocol");
}

std::string CHttpUrl::ToStringProtocol() const
{
	return ( m_protocol == Protocol::HTTP ? "http" : "https");
}

URLContainer CHttpUrl::ParseURL(boost::string_ref & url)
{
	Protocol protocol = ParseProtocol(url);
	std::string domain = VerifyDomain(ParseDomain(url));
	unsigned short port = ParsePort(url);
	std::string document = VerifyDocument(ParseDocument(url));

	if (port == 0)
	{
		port = (protocol == Protocol::HTTP ? 80 : 443);
	}
	return URLContainer(protocol, domain, document, port);
}

Protocol CHttpUrl::ParseProtocol(boost::string_ref & str)
{
	const string schemeDelimiter = "://";
	auto schemePos = str.find(schemeDelimiter);
	if (schemePos == boost::string_ref::npos)
	{
		throw CUrlParsingError("Protocol parsing error");
	}
	string protocol = str.substr(0, schemePos).to_string();

	str = str.substr(schemePos + schemeDelimiter.size() , str.size() - 1);

	return ToProtocol(protocol);
}

std::string CHttpUrl::ParseDomain(boost::string_ref & url)
{
	auto domainPos = url.find(':');
	if (domainPos == boost::string_ref::npos)
	{
		domainPos = url.find("/");
		domainPos = (domainPos == boost::string_ref::npos ? url.size() : domainPos);
	}
	auto domain = url.substr(0, domainPos).to_string();
	url = url.substr(domainPos, url.size());
	return domain;
}

unsigned short CHttpUrl::ParsePort(boost::string_ref & str)
{
	if (str.front() == ':')
	{
		auto portPos = str.find('/');
		string port;
		if (portPos == boost::string_ref::npos)
		{
			port = str.substr(1, str.size()).to_string();
		}
		else
		{
			port = str.substr(1, portPos - 1).to_string();
		}
		str = str.substr(port.size() + 1, str.size());
		return (port.empty() ? throw CUrlParsingError("Port parsing error") : boost::lexical_cast<unsigned short>(port));
	}
	return  0;
}

std::string CHttpUrl::ParseDocument(boost::string_ref & url)
{
	return url.to_string();
}

std::string CHttpUrl::VerifyDomain(std::string const & domain)
{
	if (domain.empty())
	{
		throw CUrlParsingError("domain name is empty");
	}
	else if (find_if(domain.begin(), domain.end(), [](char ch) { 
		return (isspace(ch) || (ch == '/') || (ch == '\'')); }) != domain.end())
	{
		throw CUrlParsingError("domain name is contain invalid symbols");
	}

	return domain;
}

std::string CHttpUrl::VerifyDocument(std::string const & document)
{
	if (find_if(document.begin(), document.end(), [&](char ch) {
		return (isspace(ch));
	}) != document.end())
	{
		throw CUrlParsingError("Document must not contain any spaces or tabulation.");
	}

	if (document[0] != '/')
	{
		return '/' + document;
	}
	return document;
}

Protocol CHttpUrl::VerifyProtocol(Protocol const & protocol)
{
	if (protocol == Protocol::HTTP || protocol == Protocol::HTTPS) 
	{
		return protocol;
	}
	throw CUrlParsingError("Invalid protocol");
}
