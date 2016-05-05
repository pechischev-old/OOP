#include "MyString.h"
#include <assert.h>

using namespace std;

CMyString::CMyString()
{
}

CMyString::CMyString(const char * pString)
	: m_length(strlen(pString))
	, m_string(new char[m_length + 1])
{
	StrCpy(pString);
}

CMyString::CMyString(const char * pString, size_t length)
	: m_length(length)
	, m_string(new char[m_length + 1])
{
	StrCpy(pString);
}

CMyString::CMyString(CMyString const & other)
	: m_length(other.m_length)
	, m_string(new char[m_length + 1])
{
	StrCpy(other.m_string);
}

CMyString::CMyString(CMyString && other)
	: m_length(other.m_length)
	, m_string(other.m_string)
{
	other.m_length = 0;
	other.m_string = nullptr;
}

CMyString::CMyString(std::string const & stlString)
	: m_length(stlString.length())
	, m_string(new char[m_length + 1])
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
	return m_length;
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
	if (start >= m_length)
	{
		throw std::out_of_range("Out of range");
	}
	else if (!m_string)
	{
		return CMyString();
	}
	else if (length > m_length)
	{
		length = m_length;
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
		m_length = 0;
	}
}

void CMyString::StrCpy(const char * str)
{
	memcpy(m_string, str, m_length);
	m_string[m_length] = '\0';
}

CMyString& CMyString::operator= (CMyString const & str)
{
	if (m_string != str.m_string)
	{
		if (m_string)
		{
			delete[] m_string;
		}
		m_length = str.m_length;
		m_string = new char[m_length + 1];
		StrCpy(str.m_string);
	}
	return *this;
}

CMyString& CMyString::operator= (CMyString && str)
{
	if (m_string != str.m_string)
	{
		swap(m_string, str.m_string);
		m_length = str.m_length;

		delete[] str.m_string;
		str.m_string = nullptr;
		str.m_length = 0;
	}
	return *this;
}

CMyString & CMyString::operator+=(CMyString const & str)
{
	if (str.m_string)
	{
		char *temp = new char[m_length + str.m_length + 1];
		memcpy(temp, m_string, m_length);
		memcpy(&temp[m_length], str.m_string, str.m_length);
		m_length = m_length + str.m_length;

		delete[] m_string;
		m_string = temp;
	}

	return *this;
}

CMyString operator+ (CMyString & str1, CMyString const & str2)
{
	return str1 += str2;
}

CMyString operator+(std::string const & str1, CMyString const & str2)
{
	if (!str2.m_string)
	{
		return CMyString(str1);
	}

	return CMyString(std::string(str1 + str2.m_string));
}

CMyString operator+(const char* str1, CMyString const & str2)
{
	if (!str2.m_string)
	{
		return CMyString(str1);
	}
	CMyString str(str1);
	return str + str2;
}
