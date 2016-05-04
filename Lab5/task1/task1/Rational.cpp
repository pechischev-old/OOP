#include "stdafx.h"
#include "Rational.h"
#include <utility>
#include <stdexcept>


CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	if (abs(m_numerator) > m_denominator)
	{
		int integerPart = m_numerator / m_denominator;
		int numerator = m_numerator - (m_denominator * integerPart);
		return std::pair<int, CRational>(integerPart, CRational(numerator, m_denominator));
	}
	return std::pair<int, CRational>(0, *this);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
//////////////////////////////////////////////////////////////////////////

double CRational::ToDouble() const
{
	return double(m_numerator) / double(m_denominator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
//////////////////////////////////////////////////////////////////////////
CRational CRational::operator+ () const
{
	return *this;
}

CRational CRational::operator- () const
{
	return CRational(-m_numerator, m_denominator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
//////////////////////////////////////////////////////////////////////////
CRational operator+ (CRational const &rational1, CRational const &rational2)
{
	return (CRational((rational1.GetNumerator() * rational2.GetDenominator()) +
		(rational2.GetNumerator() * rational1.GetDenominator()),
		rational1.GetDenominator() * rational2.GetDenominator()));
}

//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
//////////////////////////////////////////////////////////////////////////
CRational operator-(CRational const & rational1, CRational const & rational2)
{
	return (CRational((rational1.GetNumerator() * rational2.GetDenominator()) -
	(rational2.GetNumerator() * rational1.GetDenominator()),
	rational1.GetDenominator() * rational2.GetDenominator()));
}

//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
//////////////////////////////////////////////////////////////////////////
CRational& CRational::operator+=(CRational const & right)
{
	*this = *this + right;
	return *this;
}


//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
//////////////////////////////////////////////////////////////////////////

CRational& CRational::operator-=(CRational const & right)
{
	*this = *this - right;
	return *this;
}


//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
//////////////////////////////////////////////////////////////////////////

CRational operator*(CRational const & rational1, CRational const & rational2)
{
	return CRational(rational1.GetNumerator() * rational2.GetNumerator(), 
		rational1.GetDenominator() * rational2.GetDenominator());
}

//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
//////////////////////////////////////////////////////////////////////////
CRational operator/ (CRational const &rational1, CRational const &rational2)
{
	return CRational(rational1.GetNumerator() * rational2.GetDenominator(), 
		rational1.GetDenominator() * rational2.GetNumerator());
}



//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
//////////////////////////////////////////////////////////////////////////

CRational& CRational::operator*=(CRational const & right)
{
	*this = *this * right;
	return *this;
}


//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
//////////////////////////////////////////////////////////////////////////

CRational& CRational::operator/=(CRational const & right)
{
	*this = *this / right;
	return *this;
}


//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
//////////////////////////////////////////////////////////////////////////

bool const operator== (CRational const &rational1, CRational const &rational2)
{
	return (rational1.GetNumerator() == rational2.GetNumerator()) && 
		(rational1.GetDenominator() == rational2.GetDenominator());
}

bool const operator!= (CRational const &rational1, CRational const &rational2)
{
	return !(rational1 == rational2);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
//////////////////////////////////////////////////////////////////////////

bool const operator< (CRational const &rational1, CRational const &rational2)
{
	return (rational1.GetNumerator() * rational2.GetDenominator() < rational2.GetNumerator() * rational1.GetDenominator());
}

bool const operator> (CRational const &rational1, CRational const &rational2)
{
	return (rational1.GetNumerator() * rational2.GetDenominator() > rational2.GetNumerator() * rational1.GetDenominator());
}

bool const operator<= (CRational const &rational1, CRational const &rational2)
{
	return (rational1.GetNumerator() * rational2.GetDenominator() <= rational2.GetNumerator() * rational1.GetDenominator());
}

bool const operator>= (CRational const &rational1, CRational const &rational2)
{
	return (rational1.GetNumerator() * rational2.GetDenominator() >= rational2.GetNumerator() * rational1.GetDenominator());
}


//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//////////////////////////////////////////////////////////////////////////

std::ostream & operator << (std::ostream  & strm, CRational const &rational)
{
	return (strm << rational.GetNumerator() << '/' << rational.GetDenominator());
}

//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//////////////////////////////////////////////////////////////////////////

std::istream & operator>> (std::istream & strm, CRational &rational)
{
	int numerator;
	int denominator;
	auto pos = strm.tellg();
	if (strm >> numerator && strm.get() == '/' && strm >> denominator)
	{
		rational = CRational(numerator, denominator);
		return strm;
	}
	strm.seekg(pos);
	return strm;
}

