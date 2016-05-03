﻿#pragma once

/*
Класс, моделирующий рациональное число
*/
class CRational final
{
public:
	CRational(int numerator = 0, int denominator = 1);

	// Возвращает числитель
	int GetNumerator() const;

	// Возвращает знаменатель
	int GetDenominator() const;

	double ToDouble() const;

	CRational operator+ () const;

	CRational operator- () const;

	CRational operator+=(CRational const & right);

	CRational operator-=(CRational const & right);
	//////////////////////////////////////////////////////////////////////////
	// TODO: 6. Реализовать оператор -=
	// Выполняет уменьшение рационального числа на величину второго рационального либо целого числа :
	// (1/2) -= (1/6)  → (1/3)
	// (1/2) -= 1      → (-1/2)
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// TODO: 7. Реализовать оператор *
	// Возвращает результат произведения рациональных чисел, 
	//	рационального и целого, либо целого и рационального :
	//	(1/2) * (2/3) = (1/3)
	//	(1/2) * (-3)  = (-3/2)
	//	(7*2) / 3     = (14/3)
	//////////////////////////////////////////////////////////////////////////





	//////////////////////////////////////////////////////////////////////////
	// TODO: 8. Реализовать оператор /
	// Возвращает частное двух рациональных чисел, 
	//	рационального и целого, целого и рационального :
	//	(1/2) ⁄ (2/3) = (3/4)
	//	(1/2) ⁄ 5     = (1/10)
	//	7 ⁄ (2/3)     = (21/2)
	//////////////////////////////////////////////////////////////////////////





	//////////////////////////////////////////////////////////////////////////
	// TODO: 9. Реализовать оператор *=
	// Умножает значение первого рационального числа на другое рациональное, 
	//	либо целое:
	//	(1/2) *= (2/3) → (1/3)
	//	(1/2) *= 3     → (3/2)
	//////////////////////////////////////////////////////////////////////////





	//////////////////////////////////////////////////////////////////////////
	// TODO: 10. Реализовать оператор /=
	// Делит первое рациональное число на другое рациональное, 
	//	либо целое:
	//	(1/2) /= (2/3) → (3/4)
	//	(1/2) /= 3     → (1/6)
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// TODO: 11. Реализовать операторы == и !=
	// Проверяют равенство (и неравенство) двух рациональных чисел, 
	//	целого и рационального, рационального и целого:
	//	(1/2) == (1/2) → true
	//	(4/1) == 4     → true
	//	3 == (3/1)     → true
	//	(1/2) != (2/3) → true
	//	(1/2) != 7     → true
	//	3 != (2/3)     → true
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// TODO: 12. Реализовать операторы <, >, <=, >=
	// Сравнивают два рациональных числа, рациональное с целым, 
	//	целое с рациональным:
	//	(1/2) >= (1/3) → true
	//	(1/2) <= (1/3) → false
	//	(3/1) > 2      → true
	//	(1/2) < 7      → true
	//	3 <= (7/2)     → true
	//	3 >= (8/2)     → false
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
	//	std::ostream в формате <числитель>/<знаменатель>, 
	//	например: 7/15
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
	//	std::istream в формате <числитель>/<знаменатель>, 
	//	например: 7/15
	//////////////////////////////////////////////////////////////////////////
private:
	int m_numerator;
	int m_denominator;

	// Нормализует рациональное число
	void Normalize();
};

// Вычисляет наибольший общий знаменатель чисел a и b
unsigned GCD(unsigned a, unsigned b);

CRational operator+ (CRational const &rational1, CRational const &rational2);

CRational operator- (CRational const &rational1, CRational const &rational2);