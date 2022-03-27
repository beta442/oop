#include "headers/main_utils.h"
#include "headers/expand_template.h"

std::optional<ProgramArgs> ParseParams(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	/*std::optional<ProgramArgs> oArgs = ParseParams(argc, argv);
	if (!oArgs)
	{
		return 1;
	}
	ProgramArgs args = oArgs.value();

	std::ifstream fInS{ args.sInName };
	std::ofstream fOutS{ args.sOutName };
	ExpandTemplateFile(fInS, fOutS, args.expandTemplateParams);*/
	using ParamsMap = std::map<std::string, std::string>;

	std::string tpl = "1 123 1234 CCC12345lm CCC12345k CCCB 789012345678901234"; // 12345612345678hk
	ParamsMap paramsExampleFourth{
		{ "1ab", "[!AB]" },
		{ "1abc", "[!ABC]" },
		{ "1ad", "[!AD]" },
		{ "1adef", "[!ADEF]" },
		{ "12ab", "[!@AB]" },
		{ "12abc", "[!@ABC]" },
		{ "12ad", "[!@AD]" },
		{ "12adef", "[!@ADEF]" },
		{ "1234", "[!@#$]" },
		{ "123456", "[!@#$%^]" },
		{ "123456g", "[!@#$%^G]" },
		{ "12345678", "[!@#$%^&*]" },
		{ "12345678hk", "[!@#$%^&*HK]" },
		{ "1234567890", "[!@#$%^&*()]" },
		{ "7890123", "[&*()!@#]" },
		{ "2ab", "[2AB]" },
		{ "2abc", "[@ABC]" },
		{ "2ad", "[@AD]" },
		{ "2adef", "[@ADEF]" },
		{ "234", "[@#$]" },
		{ "2345lm", "[@#$%LM]" },
		{ "23456", "[@#$%^]" },
		{ "23456g", "[@#$%^G]" },
		{ "2345678", "[@#$%^&*]" },
		{ "2345678hk", "[@#$%^&*HK]" },
		{ "234567890", "[@#$%^&*()]" },
		{ "CCCC", "[cccc]" },
		{ "C", "[c]" },
		{ "B", "[b]" },
	};

	std::cout << ExpandTemplate(tpl, paramsExampleFourth) << std::endl;

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
