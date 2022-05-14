#pragma once

#include <string>

#include "CUrlParsingError.h"

class HttpUrl
{
public:
	enum class Protocol
	{
		HTTP = 0,
		HTTPS,
	};

public:
	// выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
	// выбрасыват исключение UrlParsingError, содержащее текстовое описание ошибки
	HttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
		ѕри недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	HttpUrl(std::string const& domain, std::string const& document, Protocol protocol = Protocol::HTTP);

	/* инициализирует URL на основе переданных параметров.
		ѕри недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	HttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port);

	// возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
	// выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
	// не должен включатьс€
	std::string GetURL() const;

	// возвращает доменное им€
	std::string GetDomain() const;

	/*
		¬озвращает им€ документа. ѕримеры:
			/
			/index.html
			/images/photo.jpg
	*/
	std::string GetDocument() const;

	Protocol GetProtocol() const;

	unsigned short GetPort() const;

private:
	unsigned short m_port;
	Protocol m_protocol;
	std::string m_document;
	std::string m_domain;
	std::string m_url;
};
