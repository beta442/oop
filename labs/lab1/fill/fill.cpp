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

void CopyFileWithFillingMarkedArea(std::ifstream& fIn, std::ofstream& fOut, const char& marker);

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Invalid argument count\n");
		printf("Usage: fill.exe <%s> <%s>\n", INPUT_FILE_PARAM, OUTPUT_FILE_PARAM);
	}

	try
	{
		if (std::strlen(argv[1]) == 0 || std::strlen(argv[2]) == 0)
		{
			throw ERR_CODE_INVALID_PARAM_LENGTH;
		}
	}
	catch (...)
	{
		printf("Invalid arguments value\n");
		printf("Usage: fill.exe <%s> <%s>\n", INPUT_FILE_PARAM, OUTPUT_FILE_PARAM);
		exit(EXIT_FAILURE);
	}

	std::ifstream fIn;
	std::ofstream fOut;

	fIn.open(argv[1]);
	std::string tempStr;
	if (!fIn.is_open() || !getline(fIn, tempStr))
	{
		printf("Something bad with input file\n");
		return EXIT_FAILURE;
	}
	fIn.seekg(0, fIn.beg);

	fOut.open(argv[2]);
	if (!fOut.is_open())
	{
		printf("Something bad with output file\n");
		return EXIT_FAILURE;
	}

	CopyFileWithFillingMarkedArea(fIn, fOut, MARKER);

	return EXIT_SUCCESS;
}

enum class MoveDirection
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
};

constexpr auto MAX_SIZE = 50;

struct FieldCellPoint
{
	size_t rowIndex;
	size_t columnIndex;
	void setPoint(const size_t& rowNum, const size_t& columnNum);
};

struct Field
{
	std::vector<std::string> field;
	size_t size();
	void appendRow(std::string row);
	std::string at(const size_t& rowIndex);
	char getFieldCell(const FieldCellPoint& point);
	char getFieldCell(const size_t& rowIndex, const size_t& columnIndex);
	void setFieldCell(const FieldCellPoint& point, const char& val);
	void printField(std::ostream& fOut);
	void fillFieldCellNeighbors(const FieldCellPoint& point);
};

Field GetSizedSquareFieldFromFile(std::ifstream& fIn, const size_t& size);

void CopyFileWithFillingMarkedArea(std::ifstream& fIn, std::ofstream& fOut, const char& marker)
{
	Field field = GetSizedSquareFieldFromFile(fIn, MAX_SIZE);
	printf("\nFound this map\n");
	field.printField(std::cout);

	std::vector<FieldCellPoint> startPoints{};
	char scanningChar{};
	FieldCellPoint point{};
	for (size_t j = 0; j < field.size(); j++)
	{
		for (size_t k = 0; k < field.at(j).size(); k++)
		{
			scanningChar = field.getFieldCell(j, k);
			if (scanningChar == START_MARKER)
			{
				point.setPoint(j, k);
				startPoints.push_back(point);
			}
		}
	}

	for (size_t i = 0; i < startPoints.size(); i++)
	{
		field.fillFieldCellNeighbors(startPoints[i]);
	}

	field.printField(fOut);
}

void Field::appendRow(std::string row)
{
	if (field.size() < MAX_SIZE)
	{
		field.push_back(row);
	}
}

size_t Field::size()
{
	return field.size();
}

std::string Field::at(const size_t& rowIndex)
{
	return field.at(rowIndex);
}

constexpr auto NOT_VALID_CELL_VALUE = -1;

char Field::getFieldCell(const FieldCellPoint& point)
{
	if (point.rowIndex < MAX_SIZE && point.columnIndex < MAX_SIZE && field.at(point.rowIndex).size())
	{
		return field.at(point.rowIndex)[point.columnIndex];
	}
	return NOT_VALID_CELL_VALUE;
}

char Field::getFieldCell(const size_t& rowIndex, const size_t& columnIndex)
{
	if (rowIndex < MAX_SIZE && columnIndex < MAX_SIZE && field.at(rowIndex).size())
	{
		return field.at(rowIndex)[columnIndex];
	}
	return NOT_VALID_CELL_VALUE;
}

void Field::setFieldCell(const FieldCellPoint& point, const char& val)
{
	field.at(point.rowIndex)[point.columnIndex] = val;
}

void Field::printField(std::ostream& fOut)
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

void FieldCellPoint::setPoint(const size_t& rowNum, const size_t& columnNum)
{
	rowIndex = rowNum;
	columnIndex = columnNum;
}

Field GetSizedSquareFieldFromFile(std::ifstream& fIn, const size_t& size)
{
	std::string buffer;
	Field field;
	for (size_t i = 0; i < MAX_SIZE; i++)
	{
		if (std::getline(fIn, buffer))
		{
			if (buffer.size() < MAX_SIZE)
			{
				size_t delta = MAX_SIZE - buffer.size();
				std::string blankDelta;
				blankDelta.assign(delta, EMPTY_MARKER);
				buffer.append(blankDelta);
			}
			buffer = buffer.substr(0, MAX_SIZE);
		}
		else
		{
			buffer.assign(MAX_SIZE, EMPTY_MARKER);
		}
		field.appendRow(buffer);
	}

	return field;
}

void Field::fillFieldCellNeighbors(const FieldCellPoint& point)
{
	char cellValue = getFieldCell(point);
	if (cellValue == MARKER || cellValue == FILL_MARKER || cellValue == NOT_VALID_CELL_VALUE)
	{
		return;
	}
	if (cellValue == EMPTY_MARKER)
	{
		setFieldCell(point, FILL_MARKER);
	}

	FieldCellPoint nextPoint = {};
	nextPoint.setPoint(point.rowIndex - 1, point.columnIndex);
	fillFieldCellNeighbors(nextPoint);

	nextPoint.setPoint(point.rowIndex + 1, point.columnIndex);
	fillFieldCellNeighbors(nextPoint);

	nextPoint.setPoint(point.rowIndex, point.columnIndex - 1);
	fillFieldCellNeighbors(nextPoint);

	nextPoint.setPoint(point.rowIndex, point.columnIndex + 1);
	fillFieldCellNeighbors(nextPoint);
}
