#include "stdafx.h"
#include "VectorProcessor.h"


using namespace std;
using boost::transform;

void ProcessVector(vector<double> & numbers) 
{
	if (!numbers.empty())
	{
		auto IsNegative = [](double number) {return number < 0; };

		double minNumber = *min_element(numbers.begin(), numbers.end());
		double maxNumber = *max_element(numbers.begin(), numbers.end());

		double multiply = minNumber * maxNumber;

		auto MyltiplicationNegativeNumber = [multiply, &IsNegative](double number) 
		{
			return number = IsNegative(number) ? number * multiply : number;
		};
		transform(numbers, numbers.begin(), MyltiplicationNegativeNumber);
	}
}