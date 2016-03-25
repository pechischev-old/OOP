#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <windows.h>
#include <locale>

#include <boost/algorithm/string.hpp>

using Dictionary = std::map<std::string, std::string>;

void ProcessMap(Dictionary & dict, std::string const & fileName);

void UserInteraction(Dictionary & dict, std::string const & fileName);

bool AddNewWordToDictionary(Dictionary & dict, std::string key, std::string const & value);
std::string FindValueByKey(Dictionary & dict, std::string key);
void WriteNewWordsToFile(Dictionary & dictNewWords, std::string const & fileName);
void AskForSaveBeforeExit(Dictionary & dictNewWords, std::string const & fileName);
bool IsFileNotEmpty(std::string const & fileName);
void FillDictionary(std::string const & fileName, Dictionary & dict);
