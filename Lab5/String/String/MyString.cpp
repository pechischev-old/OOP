#include "MyString.h"
#include <assert.h>

using namespace std;

CMyString::CMyString()
{
}

CMyString::CMyString(const char * pString)
	: m_lenght(strlen(pString))
	, m_string(new char[m_lenght + 1])
{
	StrCpy(pString);
}

CMyString::CMyString(const char * pString, size_t length)
	: m_lenght(length)
	, m_string(new char[m_lenght + 1])
{
	StrCpy(pString);
}

CMyString::CMyString(CMyString const & other)
	: m_lenght(other.m_lenght)
	, m_string(new char[m_lenght + 1])
{
	StrCpy(other.m_string);
}

CMyString::CMyString(CMyString && other)
	: m_lenght(other.m_lenght)
	, m_string(other.m_string)
{
	other.m_lenght = 0;
	other.m_string = nullptr;
}

CMyString::CMyString(std::string const & stlString)
	: m_lenght(stlString.length())
	, m_string(new char[m_lenght + 1])
{
	StrCpy(stlString.c_str());
}

CMyString::~CMyString()
{
	if (m_string)
	{
		delete[] m_string;
	}
}

size_t CMyString::GetLength() const
{
	return m_lenght;
}

const char * CMyString::GetStringData() const
{
	if (!m_string)
	{
		return "\0";
	}
	return m_string;
}

CMyString const CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_lenght)
	{
		throw std::out_of_range("Out of range");
	}
	else if (!m_string)
	{
		return CMyString();
	}
	else if (length > m_lenght)
	{
		length = m_lenght;
	}
	return CMyString(&m_string[start], length);
}

void CMyString::Clear()
{
	if (m_string)
	{
		delete[] m_string;
		m_string = new char[1];
		m_string[0] = '\0';
	}
}

void CMyString::StrCpy(const char * str)
{
	memcpy(m_string, str, m_lenght);
	m_string[m_lenght] = '\0';
}
