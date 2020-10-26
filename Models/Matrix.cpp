#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include "Exceptions.h"
#include "Vector.h"
#include "Matrix.h"

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

Matrix::Matrix(int row, int col, const double initial) : rows(row), cols(col), count(row * col) 
{
	initialize(initial);
}

Matrix::Matrix(int row, int col, const double* results) : rows(row), cols(col), count(row * col) 
{
	data = new double[count];
	for (int i = 0; i < count; i++)
		*(data + i) = *(results + i);
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

double Matrix::getTrace()
{
	if (!isSquare())
		throw new NotSquareMatrixError();
	double sum = 0;
	for (int i = 0; i < rows; ++i)
		sum += *(data + cols * i + i);	// only iterate over diagonal
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

Matrix& Matrix::indexToCoords(int index, int* outRow, int* outCol) 
{
	*outRow = asRow(index);
	*outCol = asCol(index);
	return *this;
}

void Matrix::initialize(const double value) 
{
	data = new double[count];
	for (int  i = 0; i < count; ++i)
		*(data + i) = value;
}

/* Accessors */

Matrix& Matrix::getDimensions(int* rows, int* cols) 
{
	*rows = this->rows;
	*cols = this->cols;
	return *this;
}

std::string Matrix::toString() 
{
	std::ostringstream ss;
	for (int i = 0; i < count; ++i)
		ss << *(data + i) << (((i+1)%cols == 0) ? "\n" : "\t");
	return ss.str();
}

inline double& Matrix::get(int row, int col) const 
{
	return *(data + cols * row + col);
}

double Matrix::operator()(int row, int col) const  // for const objects
{ 
	return *(data + cols * row + col);
}

/* Mathematical ops - Row/Col operations */

Matrix& Matrix::plusRow(Vector& row) 
{
	if (row.count != cols)
		throw VectorDimensionError(row.count, cols);
	Matrix* result = new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		*(result->data + i) = *(data + i) + row(i % cols);
	return *result;
}

Matrix& Matrix::plusCol(Vector& col)
{
	if (col.count != rows)
		throw VectorDimensionError(col.count, cols);
	Matrix* result = new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		*(result->data + i) = *(data + i) + col(i / cols);
	return *result;
}

Matrix& Matrix::timesRow(int row, double multiplier)
{
	Matrix* result = new Matrix(rows, cols);
	for (int i = 0; i < count; ++i) 
		*(result->data + i) = *(data + i) * ((i % cols == row) ? multiplier : 1);
	return *result;
}

Matrix& Matrix::timesCol(int row, double multiplier)
{
	Matrix* result = new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		*(result->data + i) = *(data + i) * ((i / cols == row) ? multiplier : 1);
	return *result;
}

Matrix& Matrix::swapRows(int first, int second)
{
	throw new NotYetImplementedError();
}

Matrix& Matrix::swapCols(int first, int second)
{
	throw new NotYetImplementedError();
}

/* Extra opeations */

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
			*(minor->data + minor->cols * x + y) = *(data + cols * i + j);
		}
	}
	return *minor;
}

double Matrix::det()
{
	if (!isSquare())
		throw new NotSquareMatrixError();
	if (rows == 2) {				// stop condition
		double a = *(data),			// [0][0]
			b = *(data + 1),		// [0][1]
			c = *(data + cols),		// [1][0]
			d = *(data + cols + 1);	// [1][1]
		return a * d - b * c;
	}
	/** Recursively calculate the matrix's determinant */
	double determinant = 0;
	for (int i = 0; i < rows; ++i)
		/* we'll use the first column as pivot, and the following formula : det(A) = sigma(sign*pivot*det(minor))
		 * where	sigma = sum of
					sign = (-1)^i
		 *			i = current pivot row
		 *			pivot = the i'th coefficient from the first column
		 *			minor = submatrix (after removing the pivot's row and col)
		*/
		determinant += *(data + cols * i) * pow(-1, i) * minor(i, 0).det();
	return determinant;
}

/* Mathematical ops */

inline Matrix& Matrix::plus(Matrix& matrix)
{
	Matrix* result = new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		*(result->data + i) = *(data + i) + *(matrix.data + i);
	return *result;
}

inline Matrix& Matrix::times(double scalar)
{
	Matrix* result = new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		*(result->data + i) = *(data + i);
	return *result;
}

inline Matrix& Matrix::minus(Matrix& matrix)
{
	return plus(matrix.times(-1));
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
		// Clean version: result.data[x][y] += data[x][z] * matrix.data[z][y] 
		*(result->data + cols * x + y) += *(data + cols * x + z) * *(matrix.data + cols * z + y);
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

inline Matrix& Matrix::hadamardTimes(Matrix& matrix)
{
	Matrix* result = new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		(*result)[i] = *(data + i) * *(matrix.data + i);
	return *result;
}

inline Matrix& Matrix::divide(Matrix& matrix)
{
	throw new NotYetImplementedError();
}

Matrix& Matrix::operator+(Matrix& matrix) 
{
	return plus(matrix);
}

Matrix& Matrix::operator*(double value)
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
	throw new NotYetImplementedError();
}

/* Static */

Matrix& Matrix::identity(int size) 
{
	Matrix* result = new Matrix(size);
	for (int i = 0, cols = result->cols, count = result->count; i < count; i++)
		*(result->data + i) = (i/cols == i%cols) ? 1 : 0;
	return *result;
}