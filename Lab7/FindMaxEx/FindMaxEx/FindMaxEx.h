#pragma once
#include "stdafx.h"


template<typename T, typename Less>
bool FindMax(std::vector<T>const & arr, T & maxValue, Less const & less)
{
	if (arr.empty())
	{
		return false;
	}
	maxValue = arr.front();
	for (auto i = 1u; i < arr.size(); ++i)
	{
		if (less(maxValue, arr[i]))
		{
			maxValue = arr[i];
		}
	}

	return true;
}