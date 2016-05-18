#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"

class CMyString
{
public:
	// конструктор по умолчанию
	CMyString();

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	CMyString(const char * pString);

	// конструктор, инициализирующий строку данными из 
	// символьного массива заданной длины
	CMyString(const char * pString, size_t length);

	// конструктор копирования
	CMyString(CMyString const & other);

	// перемещающий конструктор (для компиляторов, совместимых с C++11)
	//  реализуется совместно с перемещающим оператором присваивания 
	CMyString(CMyString && other);

	// конструктор, инициализирующий строку данными из 
	// строки стандартной библиотеки C++
	CMyString(std::string const & stlString);

	// деструктор класса - освобождает память, занимаемую символами строки
	~CMyString();

	// возвращает длину строки (без учета завершающего нулевого символа)
	size_t GetLength() const;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая
	const char* GetStringData()const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	CMyString const SubString(size_t start, size_t length = SIZE_MAX) const;

	// очистка строки (строка становится снова нулевой длины)
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


