#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <windows.h>

#include "boost/algorithm/string.hpp"

using Dictionary = std::map<std::string, std::string>;

void ProcessMap(Dictionary & dict, std::string const & fileName);

void UserInteraction(Dictionary & dict, std::string const & fileName);

bool AddNewWordInDictionary(Dictionary & dict, std::string const & key, std::string const & value);
std::string FindValueOnKey(Dictionary & dict, std::string key);
void WriteNewWordsInFile(Dictionary & dictNewWords, std::string const & fileName);
void WillSave(Dictionary & dictNewWords, std::string const & fileName);
bool IsFileNotEmpty(std::string const & fileName);
void FillDictionary(std::string const & fileName, Dictionary & dict);
