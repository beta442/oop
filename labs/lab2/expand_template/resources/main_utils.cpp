#include "../headers/main_utils.h"
#include "../headers/expand_template.h"

void ExpandTemplateFile(std::ifstream& fInS, std::ofstream& fOutS, ExpandTemplateFuncParam params)
{
	if (!fInS.is_open())
	{
		std::cout << "Failed to open input file" << std::endl;
		return;
	}

	if (!fOutS.is_open())
	{
		std::cout << "Failed to open output file" << std::endl;
		return;
	}

	std::string buff;
	while (std::getline(fInS, buff))
	{
		fOutS << ExpandTemplate(buff, params) << std::endl;
		if (fOutS.bad())
		{
			std::cout << "Failed to write in output file" << std::endl;
			break;
		}
	}
	if (!fInS.eof())
	{
		std::cout << "Not all input content was expanded" << std::endl;
	}
}
