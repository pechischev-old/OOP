#include "HttpUrl.h"

CHttpUrl::CHttpUrl(std::string const & url)
{

}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port)
	: m_domain(domain)
	, m_document(document)
	, m_protocol(protocol)
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

URLContainer CHttpUrl::ParseURL(std::string const & url)
{
	Protocol protocol;
	std::string domain;
	std::string document;
	unsigned short port;
	return URLContainer(protocol, domain, document, port);
}
