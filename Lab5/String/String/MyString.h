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
private:
	void StrCpy(const char * str);
	size_t m_length = 0;
	char* m_string = nullptr;
};

CMyString operator+ (CMyString & str1, CMyString const & str2);
CMyString operator+(std::string const & str1, CMyString const & str2);
CMyString operator+(const char* str1, CMyString const & str2);

