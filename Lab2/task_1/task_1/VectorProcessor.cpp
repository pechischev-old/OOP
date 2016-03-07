#include "stdafx.h"
#include "VectorProcessor.h"
#include <iterator>
#include <iostream>

using namespace std;

void ProcessVector(vector<double> & numbers) {

	if (!numbers.empty()) {
		auto IsNegative = [](double number) {return number < 0; };

		double minNumber = *min_element(numbers.begin(), numbers.end());
		double maxNumber = *max_element(numbers.begin(), numbers.end());

		double multiply = minNumber * maxNumber;

		// заменить функцией STL
		for (auto &number : numbers) {
			if (IsNegative(number)) {
				number *= multiply;
			}
		}
	}
}