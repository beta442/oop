#include "Headers\String2Number.h" // ConvertToDouble
#include "cmath" //pow
#include <fstream>

constexpr int DEBUG = 0;

constexpr auto INPUT_FILE = "fileWithMatrix";

constexpr size_t LINE_SIZE = 3;
constexpr size_t MAX_EL_INDEX = LINE_SIZE - 1;

typedef double Matrix2x2[LINE_SIZE - 1][LINE_SIZE - 1];
typedef double Matrix3x3[LINE_SIZE][LINE_SIZE];
typedef double Matrix2x2Row[LINE_SIZE - 1];
typedef double Matrix3x3Row[LINE_SIZE];

struct WrappedMatrix2x2Row
{
	Matrix2x2Row items;
};

struct WrappedMatrix2x2
{
	struct WrappedMatrix2x2Row row[LINE_SIZE];
};

struct WrappedMatrix3x3Row
{
	Matrix3x3Row items;
};

struct WrappedMatrix3x3
{
	WrappedMatrix3x3Row row[LINE_SIZE];
};

WrappedMatrix3x3Row GetDoubleRowFromString(std::string const& str, const char& delim)
{
	WrappedMatrix3x3Row result = {};
	std::stringstream ss(str);

	std::string s;
	size_t index = 0;
	while (index < LINE_SIZE && getline(ss, s, delim))
	{
		result.items[index] = ConvertToDouble(s);
		index++;
	}

	return result;
}

WrappedMatrix3x3 MakeMatrix3x3FromFile(std::ifstream& fIn)
{
	WrappedMatrix3x3 result{};
	size_t row = 0;
	size_t column = 0;

	fIn.seekg(0, fIn.beg);

	std::string strBuff;
	WrappedMatrix3x3Row rowValues = {};
	while (row < LINE_SIZE && getline(fIn, strBuff))
	{
		rowValues = GetDoubleRowFromString(strBuff, ' ');
		result.row[row] = rowValues;
		row++;
	}

	return result;
}

constexpr auto SEP_SYMB = "|";

void PrintMatrix3x3Formated(WrappedMatrix3x3 matrix)
{
	std::cout << std::endl;
	for (size_t j = 0; j < LINE_SIZE; j++)
	{
		std::cout << SEP_SYMB;
		for (size_t k = 0; k < LINE_SIZE; k++)
		{
			std::printf("%+.4f%s", matrix.row[j].items[k], SEP_SYMB);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void PrintMatrix2x2Formated(WrappedMatrix2x2 matrix)
{
	std::cout << std::endl;
	for (size_t j = 0; j < LINE_SIZE - 1; j++)
	{
		std::cout << SEP_SYMB;
		for (size_t k = 0; k < LINE_SIZE - 1; k++)
		{
			printf("%+.4f%s", matrix.row[j].items[k], SEP_SYMB);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

enum class MoveDirection
{
	BACKWARD = 0,
	FORWARD,
};

struct TwoDimensionalArrPtr
{
	size_t num1;
	size_t num2;
	size_t maxNum;
	TwoDimensionalArrPtr();
	void set(const size_t& val1, const size_t& val2);
	void setMaxNum(const size_t& val);
	void move(const MoveDirection& way);
	void moveDiagonally(const MoveDirection& way);
	void print();
};

TwoDimensionalArrPtr::TwoDimensionalArrPtr()
{
	num1 = 0;
	num2 = 0;
	maxNum = LINE_SIZE;
}

void TwoDimensionalArrPtr::set(const size_t& val1, const size_t& val2)
{
	num1 = val1;
	num2 = val2;
}

void TwoDimensionalArrPtr::setMaxNum(const size_t& val)
{
	maxNum = val;
}

void TwoDimensionalArrPtr::move(const MoveDirection& way)
{
	if (way == MoveDirection::FORWARD)
	{
		num2++;
		if (num2 > maxNum - 1)
		{
			num1++;
			if (num1 > maxNum - 1)
			{
				num1 -= maxNum;
			}
			num2 -= maxNum;
		}
	}
	else
	{
		if (num2 != 0)
		{
			num2--;
		}
		else
		{
			num2 = maxNum - 1;
			if (num1 != 0)
			{
				num1--;
			}
			else
			{
				num1 = maxNum - 1;
			}
		}
	}
}

void TwoDimensionalArrPtr::moveDiagonally(const MoveDirection& way)
{
	num1++;
	if (way == MoveDirection::FORWARD)
	{
		num2++;
	}
	else
	{
		if (num2 != 0)
		{
			num2--;
		}
		else
		{
			num2 = MAX_EL_INDEX;
		}
	}

	if (num1 > maxNum - 1)
	{
		num1 -= maxNum;
	}
	if (num2 > maxNum - 1)
	{
		num2 -= maxNum;
	}
}

void TwoDimensionalArrPtr::print()
{
	std::cout << num1 << " " << num2 << std::endl;
}

double GetDetFromMatrix3x3(WrappedMatrix3x3 matrix)
{
	double det = 0;
	TwoDimensionalArrPtr ptrForward;
	TwoDimensionalArrPtr ptrBackward;
	double positiveDet = 1, negDet = 1;
	if (DEBUG)
	{
		std::cout << "\n####################Calculating Det####################" << std::endl;
	}
	for (size_t j = 0; j < LINE_SIZE; j++)
	{
		positiveDet = 1;
		negDet = 1;
		ptrForward.set(0, j);
		ptrBackward.set(0, MAX_EL_INDEX - j);
		for (size_t k = 0; k < LINE_SIZE; k++)
		{
			if (DEBUG)
			{
				std::cout << "Pos: " << positiveDet << " * " << matrix.row[ptrForward.num1].items[ptrForward.num2] << std::endl;
				std::cout << "Neg: " << negDet << " * " << matrix.row[ptrBackward.num1].items[ptrBackward.num2] << std::endl;
			}
			positiveDet *= matrix.row[ptrForward.num1].items[ptrForward.num2];
			negDet *= matrix.row[ptrBackward.num1].items[ptrBackward.num2];
			ptrForward.moveDiagonally(MoveDirection::FORWARD);
			ptrBackward.moveDiagonally(MoveDirection::BACKWARD);
		}
		if (DEBUG)
		{
			std::cout << "DET BEFORE:" << det << std::endl;
			std::cout << "+" << positiveDet << " -" << negDet << std::endl;
		}

		det += positiveDet - negDet;

		if (DEBUG)
		{
			std::cout << "DET AFTER:" << det << std::endl;
		}
	}
	if (DEBUG)
	{
		std::cout << "RESULT:" << det << std::endl;
		std::cout << "####################Calculating Det####################" << std::endl;
		std::cout << std::endl;
	}

	return det;
}

WrappedMatrix3x3 GetTransposedMatrix3x3(WrappedMatrix3x3 matrix)
{
	if (DEBUG)
	{
		std::cout << std::endl;
		std::cout << "####################Calculating transposed matrix####################";
	}
	WrappedMatrix3x3 tMatrix{};
	for (size_t j = 0; j < LINE_SIZE; j++)
	{
		for (size_t k = 0; k < LINE_SIZE; k++)
		{
			tMatrix.row[j].items[k] = matrix.row[k].items[j];
		}
	}
	if (DEBUG)
	{
		PrintMatrix3x3Formated(tMatrix);
		std::cout << "####################Calculating transposed matrix####################";
		std::cout << std::endl;
	}

	return tMatrix;
}

WrappedMatrix2x2 GetAlgebraicComplement(WrappedMatrix3x3 matrix, const TwoDimensionalArrPtr& ignoredRows)
{
	WrappedMatrix2x2 result{};
	TwoDimensionalArrPtr ptrForMatrix2x2{};
	ptrForMatrix2x2.set(0, 0);
	ptrForMatrix2x2.setMaxNum(2);

	for (size_t j = 0; j < LINE_SIZE; j++)
	{
		for (size_t k = 0; k < LINE_SIZE; k++)
		{
			if (j != ignoredRows.num1 && k != ignoredRows.num2)
			{
				result.row[ptrForMatrix2x2.num1].items[ptrForMatrix2x2.num2] = matrix.row[j].items[k];
				ptrForMatrix2x2.move(MoveDirection::FORWARD);
			}
		}
	}

	return result;
}

WrappedMatrix3x3 GetInvertedMatrix3x3(WrappedMatrix3x3 matrix)
{
	WrappedMatrix3x3 result{};

	double det = GetDetFromMatrix3x3(matrix);

	if (det == 0)
	{
		std::cout << "Det is equal to 0 -> inf amounts of A^-1" << std::endl;
		return result;
	}

	const double invDet = 1 / det;

	const WrappedMatrix3x3 tMatrix = GetTransposedMatrix3x3(matrix);

	if (DEBUG)
	{
		std::cout << std::endl;
		std::cout << "####################Calculating inverted matrix####################";
	}
	double power = 0;
	TwoDimensionalArrPtr ignoredRows{};
	ignoredRows.set(0, 0);
	for (size_t j = 0; j < LINE_SIZE; j++)
	{
		for (size_t k = 0; k < LINE_SIZE; k++)
		{
			ignoredRows.set(j, k);
			WrappedMatrix2x2 algebraicCompl = GetAlgebraicComplement(tMatrix, ignoredRows);
			if (DEBUG)
			{
				std::cout << "\nIgnored those row_column: '" << j << " " << k << "'\n";
				std::cout << "Got matrix:" << std::endl;
				PrintMatrix2x2Formated(algebraicCompl);
				std::cout << std::endl;
			}
			power = pow(-1, j + 1 + k + 1);
			double res = (algebraicCompl.row[0].items[0] * algebraicCompl.row[1].items[1] -
				algebraicCompl.row[0].items[1] * algebraicCompl.row[1].items[0]);
			if (DEBUG)
			{
				std::cout << "RES: " << invDet * power * res << std::endl;
			}
			result.row[j].items[k] = invDet * power * res;
		}
	}
	if (DEBUG)
	{
		std::cout << "####################Calculating inverted matrix####################";
		std::cout << std::endl;
	}

	return result;
}

int main(int argc, char* argv[])
{
	std::ifstream fIn;

	if (argc != 2)
	{
		printf("Invalid argument count\n");
		printf("Usage: replace.exe <%s>\n", INPUT_FILE);

		return EXIT_FAILURE;
	}
	
	fIn.open(argv[1]);
	std::string tempStr;
	if (!fIn.is_open() || !getline(fIn, tempStr))
	{
		return EXIT_FAILURE;
	}
	fIn.seekg(0, fIn.beg);

	WrappedMatrix3x3 matrix = MakeMatrix3x3FromFile(fIn);
	PrintMatrix3x3Formated(matrix);

	WrappedMatrix3x3 invMatrix = GetInvertedMatrix3x3(matrix);
	PrintMatrix3x3Formated(invMatrix);

	return EXIT_SUCCESS;
}