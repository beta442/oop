#pragma once

#include "std_libs.h"

using ExpandTemplateFuncParam = std::map<std::string, std::string>;
using ExpandTemplateFuncParamUnit = std::pair<std::string, std::string>;

struct ProgramArgs
{
	std::string sInName;
	std::string sOutName;
	ExpandTemplateFuncParam expandTemplateParams;
};


void ExpandTemplateFile(std::ifstream& fInS, std::ofstream& fOutS, ExpandTemplateFuncParam params);
