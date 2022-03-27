#include "headers/expand_template.h"
#include "headers/main_utils.h"

std::optional<ProgramArgs> ParseParams(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	std::optional<ProgramArgs> oArgs = ParseParams(argc, argv);
	if (!oArgs)
	{
		return 1;
	}
	ProgramArgs args = oArgs.value();

	std::ifstream fInS{ args.sInName };
	std::ofstream fOutS{ args.sOutName };
	ExpandTemplateFile(fInS, fOutS, args.expandTemplateParams);

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
