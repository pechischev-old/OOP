#pragma once

#include <iostream>
#include <set>
#include <vector>

static const int MAX_NUMBER = 100000000;

std::set<unsigned int> GeneratePrimeNumbersSet(unsigned int upperBound);
void SieveEratosthenes(unsigned int const & N, std::vector<bool> & isSingleNumbers);