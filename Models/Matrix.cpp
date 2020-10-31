#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include "Exceptions.h"
#include "Vector.h"
#include "Matrix.h"
#include "..\DNN\Layers\Transforms.h"

/* Constructors and destructor */

inline Matrix::Matrix() : rows(0), cols(0), count(0)
{
	data = nullptr;
}

Matrix::Matrix(int size) : rows(size), cols(size), count(size* size) 
{
	initialize(0);
}

Matrix::Matrix(int row, int col) : rows(row), cols(col), count(row * col) 
{
	initialize(0);
}

Matrix::Matrix(int row, int col, const long double initial) : rows(row), cols(col), count(row * col)
{
	initialize(initial);
}

Matrix::Matrix(int row, int col, const long double* results) : rows(row), cols(col), count(row * col)
{
	data = new long double[count];
	for (int i = 0; i < count; ++i)
		data[i] = results[i];
}

Matrix::Matrix(const Matrix& matrix) : rows(matrix.rows), cols(matrix.cols), count(matrix.count)
{
	data = new long double[count];
	for (int i = 0; i < count; ++i)
		data[i] = matrix.data[i];
}

Matrix::~Matrix() 
{
	delete[] data;
}

/* Accessors */

bool Matrix::isSquare()
{
	return rows == cols;
}

bool Matrix::isDiagonal() 
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
bool Matrix::isLowerTriangular()
{
	if (!isSquare())
		throw new NotSquareMatrixError();
	for (int i = 0; i < count; ++i)
		if (i / cols < i % cols && data[i] != 0)
			return false;
	return true;
}

bool Matrix::isUpperTriangular()
{
	if (!isSquare())
		throw new NotSquareMatrixError();
	for (int i = 0; i < count; ++i)
		if (i / cols > i % cols && data[i] != 0)
			return false;
	return true;
}

int Matrix::getRows() 
{
	return rows;
}

int Matrix::getCols()
{
	return cols;
}

int Matrix::getCount()
{
	return count;
}

long double* Matrix::getData()
{
	return data;
}

long double Matrix::getTrace()
{
	if (!isSquare())
		throw new NotSquareMatrixError();
	long double sum = 0;
	for (int i = 0; i < rows; ++i)
		sum += data[cols * i + i];	// only iterate over diagonal
	return sum;
}

long double Matrix::getSum()
{
	long double sum = 0;
	for (int i = 0; i < count; ++i)
		sum += data[i];
	return sum;
}

/* Utility methods */

inline int Matrix::asRow(int index) 
{
	return index / cols;
}

inline int Matrix::asCol(int index)
{
	return index % cols;
}

const bool Matrix::isDiagonal(int index) 
{
	return index/cols == index % cols;
}

Matrix& Matrix::indexToCoords(int index, int* outRow, int* outCol) 
{
	*outRow = asRow(index);
	*outCol = asCol(index);
	return *this;
}

void Matrix::initialize(const long double value)
{
	data = new long double[count];
	for (int  i = 0; i < count; ++i)
		data[i] = value;
}

/* Accessors */

Matrix& Matrix::getDimensions(int& rows, int& cols) 
{
	rows = this->rows;
	cols = this->cols;
	return *this;
}

std::string Matrix::toString() 
{
	std::ostringstream ss;
	for (int i = 0; i < count; ++i)
		ss << data[i] << (((i+1)%cols == 0) ? "\n" : "\t");
	return ss.str();
}

inline long double& Matrix::get(int row, int col) const
{
	return data[cols * row + col];
}

long double Matrix::operator()(int row, int col) const  // for const objects
{ 
	return data[cols * row + col];
}

/* Mathematical ops - Row/Col operations */

Matrix& Matrix::plusRow(Vector& row, bool inPlace)
{
	if (row.count != cols)
		throw VectorDimensionError(row.count, cols);
	Matrix* ptr = inPlace ? this : new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = data[i] + row(i % cols);
	return *ptr;
}

Matrix& Matrix::plusCol(Vector& col, bool inPlace)
{
	if (col.count != rows)
		throw VectorDimensionError(col.count, cols);
	Matrix* ptr = inPlace ? this : new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = data[i] + col(i / cols);
	return *ptr;
}

Matrix& Matrix::timesRow(int row, long double multiplier, bool inPlace)
{
	Matrix* ptr = inPlace ? this : new Matrix(rows, cols);
	for (int i = 0; i < count; ++i) 
		ptr->data[i] = data[i] * ((i % cols == row) ? multiplier : 1);
	return *ptr;
}

Matrix& Matrix::timesCol(int row, long double multiplier, bool inPlace)
{
	Matrix* ptr = inPlace ? this : new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = data[i] * ((i / cols == row) ? multiplier : 1);
	return *ptr;
}

Matrix& Matrix::swapRows(int first, int second)
{
	if (first < 0 || first >= rows)
		throw new IndexOutOfBoundsError(first);
	if (second < 0 || second >= rows)
		throw new IndexOutOfBoundsError(second);
	long double* ptr1 = nullptr, * ptr2 = nullptr;
	for (int i = 0; i < count; ++i)
	{
		if (ptr1 != nullptr && ptr2 != nullptr)
			break;
		else if (ptr1 == nullptr && i / cols == first)
			ptr1 = &data[i];
		else if (ptr2 == nullptr && i / cols == second)
			ptr2 = &data[i];
	}
	for (int i = 0; i < cols; ++i, ++ptr1, ++ptr2)
		Transforms::swap(*ptr1, *ptr2);
	return *this;
}

Matrix& Matrix::swapCols(int first, int second)
{
	if (first < 0 || first >= cols)
		throw new IndexOutOfBoundsError(first);
	if (second < 0 || second >= cols)
		throw new IndexOutOfBoundsError(second);
	long double* ptr1 = nullptr, * ptr2 = nullptr;
	for (int i = 0; i < count; ++i)
	{
		if (ptr1 != nullptr && ptr2 != nullptr)
			break;
		else if (ptr1 == nullptr && i % cols == first)
			ptr1 = &data[i];
		else if (ptr2 == nullptr && i % cols == second)
			ptr2 = &data[i];
	}
	for (int i = 0; i < rows; ++i, ptr1 += cols, ptr2 += cols)
		Transforms::swap(*ptr1, *ptr2);
	return *this;
}

const bool Matrix::equals(const Matrix& matrix) const
{
	if ((rows != matrix.rows) || (cols != matrix.cols))
		return false;
	for (int i = 0; i < count; ++i) 
		if (data[i] != matrix.data[i])
			return false;
	return true;
}

void Matrix::spit() 
{
	for (int i = 0; i < count; ++i) {
		if (i != 0 && i % cols)
			std::cout << std::endl;
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}

/* Special opeations */

Matrix& Matrix::minor(int row, int col) 
{
	Matrix* minor = new Matrix(rows - 1, cols - 1);
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

inline long double Matrix::det()
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
	long double determinant = 0;
	Matrix* ptr;
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
		determinant += data[cols * i] * pow(-1, i) * (*ptr).det();
		delete ptr;
	}
	return determinant;
}

Matrix& Matrix::cofactor() 
{
	if (!isSquare())
		throw new NotSquareMatrixError();
	else if (rows == 1) 
	{
		Matrix& id = identity(rows);
		return (equals(id) ? id : *(new Matrix(rows, cols)));
	}
	else if (rows == 2)
	{
		long double cofactor[2][2] = {
			{ data[3], -data[2] },
			{ -data[1], data[0] }
		};
		return *new Matrix(cofactor);
	}
	Matrix* result = new Matrix(rows, cols), * ptr;
	for (int i = 0; i < count; ++i)
	{
		ptr = &minor(i / cols, i % cols);
		result->data[i] = pow(-1, i) * (*ptr).det();
		delete ptr;
	}
	return *result;
}

Matrix& Matrix::adjugate()
{
	Matrix* temp = &cofactor();
	Matrix& result = temp->transpose();
	delete temp;
	return result;
}

Matrix& Matrix::transpose()
{
	Matrix* result = new Matrix(cols, rows);
	for (int i = 0; i < count; ++i)
		result->data[i] = data[cols * (i % cols) + i / cols];
	return *result;
}

/* Other */

Matrix& Matrix::flatten(bool col)
{
	return col ? *new Matrix(count, 1, data) : *new Matrix(1, count, data);
}

void Matrix::cloneFrom(Matrix& matrix)
{
	rows = matrix.rows; 
	cols = matrix.cols;
	count = matrix.count;
	data = new long double[count];
	for (int i = 0; i < count; ++i)
		data[i] = matrix.data[i];
}

Matrix& Matrix::clone()
{
	Matrix* copy = new Matrix();
	copy->cloneFrom(*this);
	return *copy;
}

/* Mathematical ops */

inline Matrix& Matrix::plus(Matrix& matrix, bool inPlace)
{
	Matrix* ptr = inPlace ? this : new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = data[i] + matrix.data[i];
	return *ptr;
}

inline Matrix& Matrix::times(long double scalar, bool inPlace)
{
	Matrix* ptr = inPlace ? this : new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = data[i] * scalar;
	return *ptr;
}

inline Matrix& Matrix::minus(Matrix& matrix, bool inPlace)
{
	Matrix* ptr = inPlace ? this : new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = data[i] - matrix.data[i];
	return *ptr;
}

inline Matrix& Matrix::times(Matrix& matrix)
{
	if (cols != matrix.rows)
		throw new MatricesDifferentDimensionError(rows, cols, matrix.rows, matrix.cols);
	Matrix* result = new Matrix(rows, matrix.cols);
	for (int x = 0, y = 0, z = 0; x < rows; z++)	// single loop multiplication
	{
		if (z == cols) {
			z = 0;
			y++;
		}
		if (y == matrix.cols) {
			y = 0;
			x++;
		}
		result->data[result->cols * x + y] += data[cols * x + z] * matrix.data[matrix.cols * z + y];
	}
	return *result;
}

inline Matrix& Matrix::power(int exponent)
{
	if (exponent <= 0)
		throw new InvalidExponentError(exponent);
	Matrix* result = new Matrix(rows, cols, data), * temp = nullptr;
	for (int i = 1; i < exponent; i++) {
		temp = &(*result * *this);
		delete result;	// delete intermediary matrices
		result = temp;
	}
	return *result;
}

inline Matrix& Matrix::hadamardTimes(Matrix& matrix, bool inPlace)
{
	Matrix* ptr = inPlace ? this : new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		(*ptr)[i] = data[i] * matrix.data[i];
	return *ptr;
}

Matrix& Matrix::inverse()
{
	if (rows != cols)
		throw NotSquareMatrixError();
	if (det() == 0)
		throw NullMatrixDeterminantError();
	Matrix* temp = &adjugate();
	Matrix& result = temp->times(1 / det());
	delete temp;
	return result;
}

inline Matrix& Matrix::divide(Matrix& matrix)
{
	if ((rows != cols) || (matrix.rows != matrix.cols))
		throw NotSquareMatrixError();
	Matrix* temp = &matrix.inverse();
	Matrix& result = times(*temp);
	delete temp;
	return times(matrix.inverse());
}

Matrix& Matrix::operator+(Matrix& matrix) 
{
	return plus(matrix);
}

Matrix& Matrix::operator*(long double value)
{
	return times(value);
}

Matrix& Matrix::operator-(Matrix& matrix)
{
	return minus(matrix);
}

Matrix& Matrix::operator*(Matrix& matrix)
{
	return times(matrix);
}

Matrix& Matrix::operator^(int exponent)
{
	return power(exponent);
}

Matrix& Matrix::operator^(Matrix& matrix)
{
	return hadamardTimes(matrix);
}

Matrix& Matrix::operator/(Matrix& matrix)
{
	return divide(matrix);
}

Matrix& Matrix::operator+=(Matrix& matrix)
{
	return plus(matrix, true);
}

Matrix& Matrix::operator*=(long double scalar)
{
	return times(scalar, true);
}

Matrix& Matrix::operator-=(Matrix& matrix)
{
	return minus(matrix, true);
}

Matrix& Matrix::operator*=(Matrix& matrix)
{
	Matrix* result = &times(matrix);
	cloneFrom(*result);
	delete result;
	return *this;
}

Matrix& Matrix::operator^=(int exponent)
{
	Matrix* result = &power(exponent);
	cloneFrom(*result);
	delete result;
	return *this;
}

Matrix& Matrix::operator^=(Matrix& matrix)
{
	Matrix* result = &times(matrix);
	cloneFrom(*result);
	delete result;
	return *this;
}

Matrix& Matrix::operator/=(Matrix& matrix)
{
	Matrix* result = &divide(matrix);
	cloneFrom(*result);
	delete result;
	return *this;
}

/* Static */

Matrix& Matrix::identity(int size) 
{
	Matrix* result = new Matrix(size);
	for (int i = 0, cols = result->cols, count = result->count; i < count; ++i)
		result->data[i] = (i/cols == i%cols) ? 1 : 0;
	return *result;
}

Matrix& Matrix::diagonal(long double* data, int count)
{
	Matrix* result = new Matrix(count, count);
	for (int i = 0, k=0; i < count * count; ++i)
		result->data[i] = (i / count == i % count) ? data[k++] : 0;
	return *result;
}