#pragma once
#include "stdafx.h"



enum Protocol
{
	HTTP,
	HTTPS
};

using URLContainer = std::tuple<Protocol, std::string, std::string, unsigned short>;

class CHttpUrl
{
public:
	// выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	CHttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
	При недопустимости входных параметров выбрасывает исключение
	std::invalid_argument
	Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol = HTTP,
		unsigned short port = 80);

	// возвращает строковое представление URL-а. Порт, являющийся стандартным для
	// выбранного протокола (80 для http и 443 для https) в URL не должен включаться
	std::string GetURL() const;

	// возвращает доменное имя
	std::string GetDomain() const;

	/*
	Возвращает имя документа. Примеры:
	/
	/index.html
	/images/photo.jpg
	*/
	std::string GetDocument() const;

	// возвращает тип протокола
	Protocol GetProtocol() const;

	// возвращает номер порта
	unsigned short GetPort() const;
private:
	URLContainer ParseURL(boost::string_ref & str);
	std::string ParseDomain(boost::string_ref & str);
	std::string ParseDocument(boost::string_ref & str);
	Protocol ParseProtocol(boost::string_ref & str);

	std::string VerifyDomain(std::string const & domain);
	std::string VerifyDocument(std::string const & document);
	Protocol VerifyProtocol(Protocol const & protocol);
private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};

