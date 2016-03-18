#pragma once
#include <string>
#include <map>
#include <iostream>

std::string ExpandTemplate(std::string const & tpl, std::map<std::string, std::string> const & params);

