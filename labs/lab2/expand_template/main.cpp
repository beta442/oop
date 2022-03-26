#include "headers/expand_template.h"

using ExpandTemplateFuncParam = std::map<std::string, std::string>;
using ExpandTemplateFuncParamUnit = std::pair<std::string, std::string>;

struct ProgramArgs
{
	std::string sInName;
	std::string sOutName;
	ExpandTemplateFuncParam expandTemplateParams;
};

std::optional<ProgramArgs> ParseParams(int argc, char* argv[]);
void ExpandTemplateFile(std::string fIn, std::string fOut, ExpandTemplateFuncParam params);

int main(int argc, char* argv[])
{
	std::optional<ProgramArgs> oArgs = ParseParams(argc, argv);
	if (!oArgs)
	{
		return 1;
	}
	ProgramArgs args = oArgs.value();

	ExpandTemplateFile(args.sInName, args.sOutName, args.expandTemplateParams);

	return 0;
}

std::optional<ProgramArgs> ParseParams(int argc, char* argv[])
{
	if (argc < 3)
	{
		return std::nullopt;
	}

	for (char** arg = argv; *arg; arg++)
	{
		if (!std::strlen(*arg))
		{
			return std::nullopt;
		}
	}

	ProgramArgs args;
	args.sInName = argv[1];
	args.sOutName = argv[2];

	ExpandTemplateFuncParamUnit expandTemplateParamsUnit;
	for (char** arg = argv + 3; *arg; arg++)
	{
		if (std::distance(argv, arg) % 2 != 0)
		{
			expandTemplateParamsUnit.first = *arg;
		}
		else
		{
			expandTemplateParamsUnit.second = *arg;
			args.expandTemplateParams.emplace(expandTemplateParamsUnit);
		}
	}

	return args;
}

void ExpandTemplateFile(std::string fIn, std::string fOut, ExpandTemplateFuncParam params)
{
	std::ifstream fInS{ fIn };
	if (!fInS.is_open())
	{
		std::cout << "Failed to open input file" << std::endl;
		return;
	}

	std::ofstream fOutS{ fOut };
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
