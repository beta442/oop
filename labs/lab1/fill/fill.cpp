#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr auto INPUT_FILE_PARAM = "input file";
constexpr auto OUTPUT_FILE_PARAM = "output file";
constexpr auto ERR_CODE_INVALID_PARAM_LENGTH = 2;

constexpr auto MARKER = '#';
constexpr auto START_MARKER = 'O';
constexpr auto FILL_MARKER = '.';
constexpr auto EMPTY_MARKER = ' ';

using Field = std::vector<std::string>;

bool ArgsValidation(const int argc, char* argv[])
{
	bool status = true;
	if (argc != 3)
	{
		printf("Invalid argument count\n");
		printf("Usage: fill.exe <%s> <%s>\n", INPUT_FILE_PARAM, OUTPUT_FILE_PARAM);

		status = false;
		return status;
	}

	for (char** arg = argv; *arg; ++arg)
	{
		if (!std::strlen(*arg))
		{
			printf("Invalid arguments value\n");
			printf("Usage: fill.exe <%s> <%s>\n", INPUT_FILE_PARAM, OUTPUT_FILE_PARAM);
			printf("One of the arguments is empty\n");

			status = false;
			break;
		}
	}

	return status;
}

bool InitArgs(std::ifstream& fIn, std::ofstream& fOut, char* argv[])
{
	bool status = true;

	fIn.open(argv[1]);
	std::string tempStr;
	if (!fIn.is_open()) //TODO check reading access
	{
		printf("Something bad with input file\n");
		return !status;
	}

	fOut.open(argv[2]);
	if (!fOut.is_open())
	{
		printf("Something bad with output file\n");
		return !status;
	}

	return status;
}

constexpr auto FIELD_SIZE = 100;
void CopyFileWithFillingMarkedArea(std::istream& fIn, std::ostream& fOut, char marker);

int main(int argc, char* argv[])
{
	if (!ArgsValidation(argc, argv))
	{
		return EXIT_FAILURE;
	}

	std::ifstream fIn;
	std::ofstream fOut;

	if (!InitArgs(fIn, fOut, argv))
	{
		return EXIT_FAILURE;
	}

	CopyFileWithFillingMarkedArea(fIn, fOut, MARKER);

	return EXIT_SUCCESS;
}

struct FieldCellPoint
{
	size_t rowIndex;
	size_t columnIndex;
};

Field GetSizedSquareFieldFromFile(std::istream& fIn, size_t size);

constexpr auto NOT_VALID_CELL_VALUE = -1;

char GetFieldCell(const Field& field, size_t rowIndex, size_t columnIndex);
void FillFieldCellNeighbors(Field& field, const FieldCellPoint& point);
void PrintField(const Field& field, std::ostream& fOut);

void CopyFileWithFillingMarkedArea(std::istream& fIn, std::ostream& fOut, char marker) //remove const
{
	Field field = GetSizedSquareFieldFromFile(fIn, FIELD_SIZE);

	std::vector<FieldCellPoint> startPoints{};
	char scanningChar;
	FieldCellPoint point{};
	for (size_t j = 0; j < field.size(); j++)
	{
		for (size_t k = 0; k < field.at(j).size(); k++)
		{
			scanningChar = GetFieldCell(field, j, k);
			if (scanningChar == START_MARKER)
			{
				point = { j, k };
				startPoints.push_back(point);
			}
		}
	}

	for (size_t i = 0; i < startPoints.size(); i++)
	{
		FillFieldCellNeighbors(field, startPoints[i]);
	}

	PrintField(field, fOut);
}

char GetFieldCell(const Field& field, size_t rowIndex, size_t columnIndex)
{
	if (rowIndex < FIELD_SIZE && columnIndex < FIELD_SIZE && field.at(rowIndex).size())
	{
		return field.at(rowIndex)[columnIndex];
	}
	return NOT_VALID_CELL_VALUE;
}

void SetFieldCell(Field& field, const FieldCellPoint& point, char val)
{
	field.at(point.rowIndex)[point.columnIndex] = val;
}

void PrintField(const Field& field, std::ostream& fOut)
{
	for (size_t i = 0; i < field.size() + 2; i++)
	{
		fOut << "-";
	}
	fOut << std::endl;
	for (size_t i = 0; i < field.size(); i++)
	{
		fOut << "|" << field[i] << "|" << std::endl;
	}
	for (size_t i = 0; i < field.size() + 2; i++)
	{
		fOut << "-";
	}
	fOut << std::endl;
}

Field GetSizedSquareFieldFromFile(std::istream& fIn, size_t size)
{
	std::string buffer;
	Field field;
	for (size_t i = 0; i < size; i++)
	{
		if (std::getline(fIn, buffer))
		{
			if (buffer.size() < size)
			{
				size_t delta = size - buffer.size();
				std::string blankDelta;
				blankDelta.assign(delta, EMPTY_MARKER);
				buffer.append(blankDelta);
			}
			buffer = buffer.substr(0, size);
		}
		else
		{
			buffer.assign(size, EMPTY_MARKER);
		}
		field.push_back(buffer);
	}

	return field;
}

void FillFieldCellNeighbors(Field& field, const FieldCellPoint& point)
{
	char cellValue = GetFieldCell(field, point.rowIndex, point.columnIndex);
	if (cellValue == MARKER || cellValue == FILL_MARKER || cellValue == NOT_VALID_CELL_VALUE)
	{
		return;
	}
	if (cellValue == EMPTY_MARKER)
	{
		SetFieldCell(field, point, FILL_MARKER);
	}

	FieldCellPoint nextPoint = {};
	nextPoint = { point.rowIndex - 1, point.columnIndex };
	FillFieldCellNeighbors(field, nextPoint);

	nextPoint = { point.rowIndex + 1, point.columnIndex };
	FillFieldCellNeighbors(field, nextPoint);

	nextPoint = { point.rowIndex, point.columnIndex - 1 };
	FillFieldCellNeighbors(field, nextPoint);

	nextPoint = { point.rowIndex, point.columnIndex + 1 };
	FillFieldCellNeighbors(field, nextPoint);
}
