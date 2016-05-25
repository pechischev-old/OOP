#pragma once
#include "stdafx.h"
#include <functional>

template<typename T>
bool FindMax(std::vector<T>const & arr, T & maxValue)
{
	return FindMax(arr, maxValue, std::less<T>());
}


template<typename T, typename Less>
bool FindMax(std::vector<T>const & arr, T & maxValue, Less const &less)
{
	if (arr.empty())
	{
		return false;
	}
	T value = arr.front();
	for (auto i = 1u; i < arr.size(); ++i)
	{
		if (less(value, arr[i]))
		{
			value = arr[i];
		}
	}
	maxValue = value;

	return true;
}