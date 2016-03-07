// task_1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

#include "VectorProcessor.h"

using namespace std;

int main()
{
	vector<double> numbers;
	copy(istream_iterator<double>(cin), istream_iterator<double>(), back_inserter(numbers));
	ProcessVector(numbers);
	sort(numbers.begin(), numbers.end());
	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, ", "));

    return 0;
}

