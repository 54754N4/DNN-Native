#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <bitset>
#include "..\Exceptions.h"
#include "..\Vector\IVector.h"
#include "..\CRTP.h"
#include "IMatrix.h"
#include "RMMatrix.h"
#include "..\..\DNN\Layers\Transforms.h"

/* Constructors and destructor */

inline RMMatrix::RMMatrix() : IMatrix()
{
	data = nullptr;
}

RMMatrix::RMMatrix(int size) : IMatrix(size), data(new long double[size * size])
{
	initialize(0);
}

RMMatrix::RMMatrix(int row, int col) 
	: IMatrix(row, col), data(new long double[count])
{
	initialize(0);
}

RMMatrix::RMMatrix(int row, int col, const long double initial) 
	: IMatrix(row, col), data(new long double[count])
{
	initialize(initial);
}

RMMatrix::RMMatrix(int row, int col, const long double* results) 
	: IMatrix(row, col), data(new long double[count])
{
	std::copy(results, results + count, data);
}

RMMatrix::~RMMatrix()
{
	if (data != nullptr)
		delete[] data;
}

void RMMatrix::initialize(const long double value)
{
	for (int i = 0; i < count; ++i)
		data[i] = value;
}

/* Move semantics */

RMMatrix& RMMatrix::copyFrom(const RMMatrix& other)
{
	if (this != &other)
	{
		if (count != other.count)	// check if storage cannot be reused
		{
			if (data != nullptr)
				delete[] data;		// free memory
			data = new long double[other.count];
		}
		rows = other.rows;
		cols = other.cols;
		count = other.count;
		std::copy(other.data, other.data + count, data);
	}
	return *this;
}

RMMatrix& RMMatrix::moveFrom(RMMatrix&& other)
{
	if (this != &other)
	{
		if (data != nullptr)	// clear previous data
			delete[] data;
		rows = other.rows;		// steal data
		cols = other.cols;
		count = other.count;
		data = other.data;
		other.rows = 0;			// reset stolen object
		other.cols = 0;
		other.count = 0;
		other.data = nullptr;
	}
	return *this;
}

RMMatrix::RMMatrix(const RMMatrix& matrix)
	: IMatrix(matrix), data(new long double[matrix.count])
{
	std::copy(matrix.data, matrix.data + matrix.count, data);
}

RMMatrix::RMMatrix(RMMatrix&& matrix) noexcept
{
	*this = std::move(matrix);		// calls move assignment operator
}

RMMatrix& RMMatrix::operator=(const RMMatrix& other)
{
	return copyFrom(other);
}

RMMatrix& RMMatrix::operator=(RMMatrix&& other) noexcept
{
	return moveFrom(std::move(other));
}

/* Utility methods */

inline int RMMatrix::asRow(int index)
{
	return index / cols;
}

inline int RMMatrix::asCol(int index)
{
	return index % cols;
}

const bool RMMatrix::isDiagonal(int index)
{
	return index / cols == index % cols;
}

RMMatrix& RMMatrix::indexToCoords(int index, int* outRow, int* outCol)
{
	*outRow = asRow(index);
	*outCol = asCol(index);
	return *this;
}

/* Special operations */

long double& RMMatrix::iGet(int index) const
{
	return data[index];
}

long double& RMMatrix::iGet(int row, int col) const
{
	return data[cols * row + col];
}

//long double RMMatrix::operator()(int row, int col) const  // for const objects
//{
//	return data[cols * row + col];
//}

std::string RMMatrix::iToString() const
{
	std::ostringstream ss;
	for (int i = 0; i < count; ++i)
		ss << data[i] << (((i + 1) % cols == 0) ? "\n" : "\t");
	return ss.str();
}

/* Accessors */

long double* RMMatrix::iGetData() const
{
	return data;
}

bool RMMatrix::iIsDiagonal() const
{
	if (!isSquare())
		throw new NotSquareMatrixError();
	for (int i = 0; i < count; ++i)
		if ((i / cols != i % cols) && data[i] != 0)
			return false;
	return true;
}

/* For the next two methods; since:
- x = i/cols and y = i%cols
- x grows south and y grows east
if all cells where x < y are 0 <==> lower triangular matrix
if all cells where x > y are 0 <==> upper triangular matrix
*/
bool RMMatrix::iIsLowerTriangular() const
{
	if (!isSquare())
		throw new NotSquareMatrixError();
	for (int i = 0; i < count; ++i)
		if (i / cols < i % cols && data[i] != 0)
			return false;
	return true;
}

bool RMMatrix::iIsUpperTriangular() const
{
	if (!isSquare())
		throw new NotSquareMatrixError();
	for (int i = 0; i < count; ++i)
		if (i / cols > i % cols && data[i] != 0)
			return false;
	return true;
}

float RMMatrix::iGetSparsity() const
{
	int zeros = 0;
	for (int i = 0; i < count; ++i)
		zeros += data[i] == 0;
	return zeros / (float)count;
}

long double RMMatrix::iGetTrace() const
{
	if (!isSquare())
		throw new NotSquareMatrixError();
	long double sum = 0;
	for (int i = 0; i < rows; ++i)
		sum += data[cols * i + i];	// only iterate over diagonal
	return sum;
}

long double RMMatrix::iGetSum() const
{
	long double sum = 0;
	for (int i = 0; i < count; ++i)
		sum += data[i];
	return sum;
}

/* Mathematical ops - Row/Col operations */

RMMatrix& RMMatrix::iPlusRow(IVector& row, bool inPlace)
{
	if (row.count != cols)
		throw VectorDimensionError(row.count, cols);
	RMMatrix* ptr = inPlace ? this : new RMMatrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = data[i] + row(i % cols);
	return *ptr;
}

RMMatrix& RMMatrix::iPlusCol(IVector& col, bool inPlace)
{
	if (col.count != rows)
		throw VectorDimensionError(col.count, cols);
	RMMatrix* ptr = inPlace ? this : new RMMatrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = data[i] + col(i / cols);
	return *ptr;
}

RMMatrix& RMMatrix::iInsertRow(int row, IVector& idata, bool inPlace)
{
	RMMatrix* ptr = inPlace ? this : new RMMatrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = (i / cols == row) ? idata(i % cols) : data[i];
	return *ptr;
}

RMMatrix& RMMatrix::iInsertCol(int col, IVector& idata, bool inPlace)
{
	RMMatrix* ptr = inPlace ? this : new RMMatrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = (i % cols == col) ? idata(i % cols) : data[i];
	return *ptr;
}

RMMatrix& RMMatrix::iTimesRow(int row, long double multiplier, bool inPlace)
{
	RMMatrix* ptr = inPlace ? this : new RMMatrix(rows, cols);
	for (int i = 0; i < count; ++i) 
		ptr->data[i] = data[i] * ((i % cols == row) ? multiplier : 1);
	return *ptr;
}

RMMatrix& RMMatrix::iTimesCol(int row, long double multiplier, bool inPlace)
{
	RMMatrix* ptr = inPlace ? this : new RMMatrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = data[i] * ((i / cols == row) ? multiplier : 1);
	return *ptr;
}

RMMatrix& RMMatrix::iSwapRows(int first, int second)
{
	if (first < 0 || first >= rows)
		throw new IndexOutOfBoundsError(first);
	else if (second < 0 || second >= rows)
		throw new IndexOutOfBoundsError(second);
	else if (first == second)
		throw new DuplicateArgumentError();
	Transforms::sort(first, second);					// make sure first stores smaller int
	long double* ptr = nullptr;
	for (int i = 0; i < count; ++i)
	{
		if (ptr == nullptr && i / cols == first)		// mark first row encounter
			ptr = &data[i];
		else if (ptr != nullptr && i / cols == second)	// on second row match, incrementally swap
			Transforms::swap(*ptr++, data[i]);
	}
	return *this;
}

RMMatrix& RMMatrix::iSwapCols(int first, int second)
{
	if (first < 0 || first >= cols)
		throw new IndexOutOfBoundsError(first);
	else if (second < 0 || second >= cols)
		throw new IndexOutOfBoundsError(second);
	else if (first == second)
		throw new DuplicateArgumentError();
	Transforms::sort(first, second);
	long double* ptr = nullptr;
	for (int i = 0; i < count; ++i)
	{
		if (ptr == nullptr && i % cols == first)		// mark first col encounter
			ptr = &data[i];
		else if (ptr != nullptr && i % cols == second)
		{	// on second col match, incrementally swap
			Transforms::swap(*ptr, data[i]);
			ptr += cols;
		}
	}
	return *this;
}

const bool RMMatrix::iEquals(const RMMatrix& matrix) const
{
	if ((rows != matrix.getRows()) || (cols != matrix.getCols()))
		return false;
	for (int i = 0; i < count; ++i) 
		if (data[i] != matrix[i])
			return false;
	return true;
}

/* Special opeations */

RMMatrix& RMMatrix::iMinor(int row, int col) const
{
	RMMatrix* minor = new RMMatrix(rows - 1, cols - 1);
	for (int i = 0, j = 0, x, y; i < rows; ++j)
	{
		if (j == cols) {
			j = 0;
			++i;
		}
		if (i != row && j != col) {	// ignore deleted row/col
			x = i > row ? i - 1 : i;
			y = j > col ? j - 1 : j;
			minor->data[minor->cols * x + y] = data[cols * i + j];
		}
	}
	return *minor;
}

inline long double RMMatrix::iDet() const
{
	if (!isSquare())
		throw new NotSquareMatrixError();
	if (rows == 2) {				// recursion stop condition
		long double a = data[0],	// data[0][0]
			b = data[1],			// data[0][1]
			c = data[2],			// data[1][0]
			d = data[3];			// data[1][1]
		return a * d - b * c;
	}
	/** Recursively calculate the matrix's determinant */
	long double det = 0;
	RMMatrix* ptr;
	for (int i = 0; i < rows; ++i) 
	{
		/* we'll use the first column as pivot, and the following formula : det(A) = sigma(sign*pivot*det(minor))
		 * where	sigma = sum of
					sign = (-1)^i
		 *			i = current pivot row
		 *			pivot = the i'th coefficient from the first column
		 *			minor = submatrix (after removing the pivot's row and col)
		*/
		ptr = &minor(i, 0);
		det += data[cols * i] * pow(-1, i) * ptr->det();
		delete ptr;
	}
	return det;
}

RMMatrix& RMMatrix::iCofactor() const
{
	if (!isSquare())
		throw new NotSquareMatrixError();
	else if (rows == 1) 
	{
		RMMatrix& id = identity(rows);
		return (equals(id) ? id : *(new RMMatrix(rows, cols)));
	}
	else if (rows == 2)
	{
		long double cofactor[2][2] = {
			{ data[3], -data[2] },
			{ -data[1], data[0] }
		};
		return *new RMMatrix(cofactor);
	}
	RMMatrix* result = new RMMatrix(rows, cols), *ptr;
	for (int i = 0; i < count; ++i)
	{
		ptr = &minor(i / cols, i % cols);
		result->data[i] = pow(-1, i) * ptr->det();
		delete ptr;
	}
	return *result;
}

RMMatrix& RMMatrix::iAdjugate() const
{
	RMMatrix& result = cofactor();
	result = std::move(result.transpose());
	return result;
}

RMMatrix& RMMatrix::iTranspose() const
{
	RMMatrix* result = new RMMatrix(cols, rows);
	for (int i = 0; i < count; ++i)
		result->data[i] = data[cols * (i % cols) + i / cols];
	return *result;
}

/* Other */

RMMatrix& RMMatrix::iFlatten(bool col, bool inPlace)
{
	if (inPlace) {
		rows = col ? count : 1;
		cols = col ? 1 : count;
		return *this;
	} else
		return col ? *new RMMatrix(count, 1, data) : *new RMMatrix(1, count, data);
}

/* Mathematical ops */

inline RMMatrix& RMMatrix::iPlus(RMMatrix& matrix, bool inPlace)
{
	RMMatrix* ptr = inPlace ? this : new RMMatrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = data[i] + matrix[i];
	return *ptr;
}

inline RMMatrix& RMMatrix::iTimes(long double scalar, bool inPlace)
{
	RMMatrix* ptr = inPlace ? this : new RMMatrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = data[i] * scalar;
	return *ptr;
}

inline RMMatrix& RMMatrix::iMinus(RMMatrix& matrix, bool inPlace)
{
	RMMatrix* ptr = inPlace ? this : new RMMatrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = data[i] - matrix[i];
	return *ptr;
}

inline RMMatrix& RMMatrix::iTimes(RMMatrix& matrix)
{
	if (cols != matrix.getRows())
		throw new MatricesDifferentDimensionError(rows, cols, matrix.getRows(), matrix.getCols());
	RMMatrix* result = new RMMatrix(rows, matrix.getCols());
	for (int x = 0, y = 0, z = 0, mcols = matrix.getCols(); x < rows; z++)	// single loop multiplication
	{
		if (z == cols) {
			z = 0;
			y++;
		}
		if (y == matrix.getCols()) {
			y = 0;
			x++;
		}
		result->data[result->cols * x + y] += data[cols * x + z] * matrix[mcols * z + y];
	}	
	return *result;
}

inline RMMatrix& RMMatrix::iPower(int exponent)
{
	if (exponent <= 0)
		throw new InvalidExponentError(exponent);
	RMMatrix& result = *new RMMatrix(rows, cols, data);
	for (int i = 1; i < exponent; i++)
		result = std::move(result.times(*this));
	return result;
}

inline RMMatrix& RMMatrix::iHadamardTimes(RMMatrix& matrix, bool inPlace)
{
	RMMatrix* ptr = inPlace ? this : new RMMatrix(rows, cols);
	for (int i = 0; i < count; ++i)
		(*ptr)[i] = data[i] * matrix[i];
	return *ptr;
}

RMMatrix& RMMatrix::iInverse()
{
	if (!isSquare())
		throw NotSquareMatrixError();
	if (det() == 0)
		throw NullMatrixDeterminantError();
	return adjugate().times(1 / det(), true);
}

inline RMMatrix& RMMatrix::iDivide(RMMatrix& matrix)
{
	if (!isSquare() || !matrix.isSquare())
		throw NotSquareMatrixError();
	RMMatrix& result = matrix.inverse();				// allocates memory
	result = std::move(times(result));					// transfers data
	return result;
}

//RMMatrix& RMMatrix::operator+(RMMatrix& matrix)
//{
//	return plus(matrix);
//}
//
//RMMatrix& RMMatrix::operator+(IVector& vector)
//{
//	return vector.isRow() ? plusRow(vector) : plusCol(vector);
//}
//
//RMMatrix& RMMatrix::operator*(long double value)
//{
//	return times(value);
//}
//
//RMMatrix& RMMatrix::operator-(RMMatrix& matrix)
//{
//	return minus(matrix);
//}
//
//RMMatrix& RMMatrix::operator*(RMMatrix& matrix)
//{
//	return times(matrix);
//}
//
//RMMatrix& RMMatrix::operator^(int exponent)
//{
//	return power(exponent);
//}
//
//RMMatrix& RMMatrix::operator^(RMMatrix& matrix)
//{
//	return hadamardTimes(matrix);
//}
//
//RMMatrix& RMMatrix::operator/(RMMatrix& matrix)
//{
//	return divide(matrix);
//}
//
//RMMatrix& RMMatrix::operator+=(RMMatrix& matrix)
//{
//	return plus(matrix, true);
//}
//
//RMMatrix& RMMatrix::operator+=(IVector& vector)
//{
//	return vector.isRow() ? plusRow(vector, true) : plusCol(vector, true);
//}
//
//RMMatrix& RMMatrix::operator*=(long double scalar)
//{
//	return times(scalar, true);
//}
//
//RMMatrix& RMMatrix::operator-=(RMMatrix& matrix)
//{
//	return minus(matrix, true);
//}
//
//RMMatrix& RMMatrix::operator*=(RMMatrix& matrix)
//{
//	return *this = std::move(times(matrix));
//}
//
//RMMatrix& RMMatrix::operator^=(int exponent)
//{
//	return *this = std::move(power(exponent));
//}
//
//RMMatrix& RMMatrix::operator^=(RMMatrix& matrix)
//{
//	return *this = std::move(times(matrix));
//}
//
//RMMatrix& RMMatrix::operator/=(RMMatrix& matrix)
//{
//	return *this = std::move(divide(matrix));
//}

/* Static */

RMMatrix& RMMatrix::zeros(int size)
{
	return zeros(size, size);
}

RMMatrix& RMMatrix::zeros(int row, int col)
{
	return *new RMMatrix(row, col, (long double) 0);
}

RMMatrix& RMMatrix::ones(int size)
{
	return ones(size, size);
}

RMMatrix& RMMatrix::ones(int row, int col)
{
	return *new RMMatrix(row, col, (long double) 1);
}

RMMatrix& RMMatrix::identity(int size)
{
	RMMatrix* result = new RMMatrix(size);
	for (int i = 0, cols = result->cols, count = result->count; i < count; ++i)
		result->data[i] = (i/cols == i%cols) ? 1 : 0;
	return *result;
}

RMMatrix& RMMatrix::diagonal(long double* data, int count)
{
	RMMatrix* result = new RMMatrix(count, count);
	for (int i = 0, k = 0; i < count * count; ++i)
		result->data[i] = (i / count == i % count) ? data[k++] : 0;
	return *result;
}

RMMatrix& RMMatrix::spiral(int size)
{
	RMMatrix* result = new RMMatrix(size, size);
	for (int i = 0, n = size, layer, x, y; i < result->count; ++i)
	{
		x = i / result->cols;
		y = i % result->cols;
		layer = std::min(std::min(x, y), std::min(n - 1 - x, n - 1 - y));
		result->data[i] = (x <= y) ?
			(n - 2 * layer) * (n - 2 * layer) - (x - layer) - (y - layer) :			// upper right triangle of matrix
			(n - 2 * layer - 2) * (n - 2 * layer - 2) + (x - layer) + (y - layer);	// lower left triangle of matrix
	}
	return *result;
}

void RMMatrix::spit()
{
	for (int i = 0; i < count; ++i) {
		if (i != 0 && i % cols)
			std::cout << std::endl;
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}