#pragma once

#include <iostream>
#include <set>
#include <vector>


std::set<int> GeneratePrimeNumbersSet(int upperBound);
void SieveEratosthenes(int N, std::vector<bool> & isSingleNumbers);