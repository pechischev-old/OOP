#pragma once

#include <iostream>
#include <set>
#include <vector>

static const int MAX_NUMBER = 100000000;

std::set<unsigned> GeneratePrimeNumbersSet(unsigned upperBound);
void SieveEratosthenes(unsigned const & N, std::vector<bool> & isSingleNumbers);