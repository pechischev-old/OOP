#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <windows.h>


using Dictionary = std::map<std::string, std::string>;

void ProcessMap(Dictionary & dict, std::string const & fileName);
void UserInteraction(Dictionary & dict, std::string const & fileName);
bool AddNewWordInDictionary(Dictionary & dict, Dictionary & dictNewWords, std::string const & key, std::string const & value);
std::string FindValueOnKey(Dictionary & dict, std::string key);

