#pragma once

#include <fstream>
#include <iostream>
#include <string>

inline void PrintFailedOpenFile(const std::string& fileName)
{
	std::cout << "Failed to open " << fileName << " file" << std::endl;
}

inline void PrintFailedToReadFromFile(const std::string& fileName)
{
	std::cout << "Failed to read from " << fileName << " file" << std::endl;
}

inline void PrintFileStreamErr(const std::string& fileName)
{
	std::cout << "Something bad with " << fileName << " file" << std::endl;
}

std::ifstream GetInputStream()
{
	std::ifstream fIn;
	std::string fileName;
	std::string tempStr;
	short status = EXIT_FAILURE;

	do
	{
		printf("Please, type correct input file name:\n");
		std::cin >> fileName;
		fIn.open(fileName);
		if (!fIn.is_open())
		{
			PrintFailedOpenFile(fileName);
		}
		else if (!getline(fIn, tempStr))
		{
			PrintFailedToReadFromFile(fileName);
		}
		else
		{
			status = EXIT_SUCCESS;
		}
	} while (status);
	fIn.seekg(0, fIn.beg);

	return fIn;
}

std::ofstream GetOutputStream()
{
	std::ofstream fO;
	std::string fileName;
	short status = EXIT_FAILURE;

	do
	{
		printf("Please, type correct output file name:\n");
		std::cin >> fileName;
		fO.open(fileName);
		if (!fO.is_open())
		{
			PrintFailedOpenFile(fileName);
		}
		else if (!fO)
		{
			PrintFileStreamErr(fileName);
		}
		else
		{
			status = EXIT_SUCCESS;
		}

	} while (status);

	return fO;
}
