#pragma once

#include <stdexcept>
#include <string>

class CHttpUrl
{
public:
	enum class Protocol
	{
		HTTP,
		HTTPS
	};

	class CUrlParsingError : public std::invalid_argument
	{
	};

public:
	// ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
	// ���������� ���������� CUrlParsingError, ���������� ��������� �������� ������
	CHttpUrl(std::string const& url);

	/* �������������� URL �� ������ ���������� ����������.
		��� �������������� ������� ���������� ����������� ����������
		std::invalid_argument
		���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	/* �������������� URL �� ������ ���������� ����������.
		��� �������������� ������� ���������� ����������� ����������
		std::invalid_argument
		���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	// ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
	// ���������� ��������� (80 ��� http � 443 ��� https) � ��� ������
	// �� ������ ����������
	std::string GetURL() const;

	// ���������� �������� ���
	std::string GetDomain() const;

	/*
		���������� ��� ���������. �������:
			/
			/index.html
			/images/photo.jpg
	*/
	std::string GetDocument() const;

	// ���������� ��� ���������
	Protocol GetProtocol() const;

	// ���������� ����� �����
	unsigned short GetPort() const;
};
