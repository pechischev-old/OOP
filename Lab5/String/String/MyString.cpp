#include "MyString.h"
#include <assert.h>
#include <algorithm>

using namespace std;

CMyString::CMyString()
	: m_length(0)
	, m_string(nullptr)
{
}

CMyString::CMyString(const char * pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const char * pString, size_t length)
{
	ToCopyString(pString, length);
}

CMyString::CMyString(CMyString const & other)
	: CMyString(other.m_string, other.m_length)
{
}

CMyString::CMyString(std::string const & stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::CMyString(CMyString && other)
	: m_length(other.m_length)
{
	swap(m_string, other.m_string);
	other.m_length = 0;
	other.m_string = nullptr;
}

CMyString::~CMyString()
{
	delete[] m_string;
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
	assert(start <= m_length);
	if (!m_string)
	{
		return CMyString("");
	}
	else if (length > m_length)
	{
		length = m_length;
	}
	return CMyString(&m_string[start], length);
}

void CMyString::Reallocate(size_t length)
{
	m_length = length;
	m_string = new char[m_length + 1];
}

void CMyString::Clear()
{
	if (m_string)
	{
		delete[] m_string;
		Reallocate(0);
		m_string[0] = '\0';
	}
}

void CMyString::ToCopyString(const char * str, size_t length)
{
	Reallocate(length);
	memcpy(m_string, str, m_length);
	m_string[m_length] = '\0';
}

CMyString& CMyString::operator= (CMyString const & str)
{
	if (m_string != str.m_string)
	{
		delete[] m_string;
		ToCopyString(str.m_string, str.m_length);
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
		char *temp = new char[m_length + str.GetLength() + 1];
		memcpy(temp, this->GetStringData(), m_length);
		memcpy(&temp[m_length], str.GetStringData(), str.GetLength());
		
		delete[] m_string;
		m_string = temp;
		m_length += str.GetLength();
		m_string[m_length] = '\0';		
	}

	return *this;
}

CMyString::CMyString(size_t length)
{
	Reallocate(length);
	m_string[length] = '\0';
}

CMyString operator+ (CMyString & str1, CMyString const & str2)
{
	if (!str2.m_string)
	{
		return CMyString(str1);
	}
	return str1 += str2;
}

CMyString operator+(std::string const & str1, CMyString const & str2)
{
	if (!str2.m_string)
	{
		return CMyString(str1);
	}
	auto lhsLen = str1.size();
	auto rhsLen = str2.GetLength();
	CMyString tmp(lhsLen + rhsLen);
	memcpy(tmp.m_string, str1.c_str(), lhsLen);
	memcpy(tmp.m_string + lhsLen, str2.GetStringData(), rhsLen);
	tmp.m_string[tmp.m_length] = '\0';
	return tmp;
}

CMyString operator+(const char* str1, CMyString const & str2)
{
	CMyString str(str1);
	return str + str2;
}

std::ostream & operator<<(std::ostream & strm, CMyString const & str)
{
	strm << str.GetStringData();
	return strm;
}

std::istream & operator>>(std::istream & strm, CMyString & str)
{
	auto pos = strm.tellg();
	std::string temp;
	if (strm >> temp)
	{
		str = CMyString(temp);
		return strm;
	}
	strm.seekg(pos);
	return strm;
}

int CMyString::Compare(CMyString const & str) const
{
	int compare = strncmp(m_string, str.m_string, min(m_length, str.m_length));
	return (compare != 0 ? compare : int(m_length - str.m_length));
}

bool CMyString::operator== (CMyString const & str2)
{
	return Compare(str2) == 0;
}

bool CMyString::operator!= (CMyString const & str2)
{
	return !(*this == str2);
}

bool CMyString::operator< (CMyString const & str2)
{
	return Compare(str2) < 0;
}

bool  CMyString::operator> (CMyString const & str2)
{
	return Compare(str2) > 0;
}

bool  CMyString::operator<= (CMyString const & str2)
{
	return Compare(str2) <= 0;
}

bool CMyString::operator>= (CMyString const & str2)
{
	return Compare(str2) >= 0;
}

const char & CMyString::operator[](size_t index) const
{
	assert(index < m_length);
	return m_string[index];
}

char & CMyString::operator[](size_t index) 
{
	assert(index < m_length);
	return m_string[index];
}
