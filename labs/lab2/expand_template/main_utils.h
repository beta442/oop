#pragma once

#include "headers/std_libs.h"

using ExpandTemplateFuncParamUnit = std::pair<std::string, std::string>;
using ExpandTemplateFuncParam = std::map<std::string, std::string>;

struct ProgramArgs
{
	std::string sInName;
	std::string sOutName;
	ExpandTemplateFuncParam expandTemplateParams;
};

void ExpandTemplateFile(std::ifstream& fInS, std::ofstream& fOutS, ExpandTemplateFuncParam params);
