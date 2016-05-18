#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"

class CMyString
{
public:
	// ����������� �� ���������
	CMyString();

	// �����������, ���������������� ������ ������� ������
	// � ����������� ������� ��������
	CMyString(const char * pString);

	// �����������, ���������������� ������ ������� �� 
	// ����������� ������� �������� �����
	CMyString(const char * pString, size_t length);

	// ����������� �����������
	CMyString(CMyString const & other);

	// ������������ ����������� (��� ������������, ����������� � C++11)
	//  ����������� ��������� � ������������ ���������� ������������ 
	CMyString(CMyString && other);

	// �����������, ���������������� ������ ������� �� 
	// ������ ����������� ���������� C++
	CMyString(std::string const & stlString);

	// ���������� ������ - ����������� ������, ���������� ��������� ������
	~CMyString();

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength() const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������
	const char* GetStringData()const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString const SubString(size_t start, size_t length = SIZE_MAX) const;

	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();

	CMyString& operator= (CMyString const & str);
	CMyString& operator= (CMyString && str);

	CMyString& operator+= (CMyString const & str);
	friend CMyString operator+(std::string const & str1, CMyString const & str2);
	friend CMyString operator+(const char* str1, CMyString const & str2);
	friend CMyString operator+(CMyString & str1, CMyString const & str2);

	int Compare(CMyString const & str) const; 

	bool operator== ( CMyString const & str2);
	bool operator!= (CMyString const & str2);
	bool operator< (CMyString const & str2);
	bool operator> (CMyString const & str2);
	bool operator<= (CMyString const & str2);
	bool operator>= (CMyString const & str2);

	const char &operator[](size_t index) const;
	char &operator[](size_t index);
private:
	CMyString(size_t length);
	void Reallocate(size_t length);
	void ToCopyString(const char * str, size_t length);

	size_t m_length;
	char* m_string;
};

std::ostream & operator<<(std::ostream & strm, CMyString const & str);
std::istream & operator>>(std::istream & strm, CMyString & str);


