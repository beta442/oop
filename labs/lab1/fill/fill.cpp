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

bool MainFuncParamsValidation(const int argc, char* argv[])
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
	if (!fIn.is_open() || !getline(fIn, tempStr))
	{
		printf("Something bad with input file\n");
		return !status;
	}
	fIn.seekg(0, fIn.beg);

	fOut.open(argv[2]);
	fOut.clear();
	if (!fOut.is_open())
	{
		printf("Something bad with output file\n");
		return !status;
	}

	return status;
}

constexpr auto FIELD_SIZE = 100;
void CopyFileWithFillingMarkedArea(std::ifstream& fIn, std::ofstream& fOut, const char& marker);

int main(int argc, char* argv[])
{
	if (!MainFuncParamsValidation(argc, argv))
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
	void setPoint(const size_t& rowNum, const size_t& columnNum);
};

struct Field
{
	std::vector<std::string> _field;
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
	Field field = GetSizedSquareFieldFromFile(fIn, FIELD_SIZE);

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
	if (_field.size() < FIELD_SIZE)
	{
		_field.push_back(row);
	}
}

size_t Field::size()
{
	return _field.size();
}

std::string Field::at(const size_t& rowIndex)
{
	return _field.at(rowIndex);
}

constexpr auto NOT_VALID_CELL_VALUE = -1;

char Field::getFieldCell(const FieldCellPoint& point)
{
	if (point.rowIndex < FIELD_SIZE && point.columnIndex < FIELD_SIZE && _field.at(point.rowIndex).size())
	{
		return _field.at(point.rowIndex)[point.columnIndex];
	}
	return NOT_VALID_CELL_VALUE;
}

char Field::getFieldCell(const size_t& rowIndex, const size_t& columnIndex)
{
	if (rowIndex < FIELD_SIZE && columnIndex < FIELD_SIZE && _field.at(rowIndex).size())
	{
		return _field.at(rowIndex)[columnIndex];
	}
	return NOT_VALID_CELL_VALUE;
}

void Field::setFieldCell(const FieldCellPoint& point, const char& val)
{
	_field.at(point.rowIndex)[point.columnIndex] = val;
}

void Field::printField(std::ostream& fOut)
{
	for (size_t i = 0; i < _field.size() + 2; i++)
	{
		fOut << "-";
	}
	fOut << std::endl;
	for (size_t i = 0; i < _field.size(); i++)
	{
		fOut << "|" << _field[i] << "|" << std::endl;
	}
	for (size_t i = 0; i < _field.size() + 2; i++)
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
	for (size_t i = 0; i < FIELD_SIZE; i++)
	{
		if (std::getline(fIn, buffer))
		{
			if (buffer.size() < FIELD_SIZE)
			{
				size_t delta = FIELD_SIZE - buffer.size();
				std::string blankDelta;
				blankDelta.assign(delta, EMPTY_MARKER);
				buffer.append(blankDelta);
			}
			buffer = buffer.substr(0, FIELD_SIZE);
		}
		else
		{
			buffer.assign(FIELD_SIZE, EMPTY_MARKER);
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
