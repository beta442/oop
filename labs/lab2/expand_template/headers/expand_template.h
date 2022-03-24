#pragma once

#include "std_libs.h"

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params);
