#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include "Exceptions.h"
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

inline bool Matrix::isSquare()
{
	return rows == cols;
}

inline int Matrix::getRows() 
{
	return rows;
}

inline int Matrix::getCols()
{
	return cols;
}

inline int Matrix::getCount()
{
	return count;
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

Matrix* Matrix::indexToCoords(int index, int* outRow, int* outCol) 
{
	*outRow = asRow(index);
	*outCol = asCol(index);
	return this;
}

void Matrix::initialize(const double value) 
{
	data = new double[count];
	for (int  i = 0; i < count; i++)
		*(data + i) = value;
}

/* Accessors */

Matrix* Matrix::getDimensions(int* rows, int* cols) 
{
	*rows = this->rows;
	*cols = this->cols;
	return this;
}

std::string Matrix::toString() 
{
	std::ostringstream ss;
	for (int i = 0; i < count; i++)
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

/* Iterators */

inline Matrix* Matrix::forEach(double (*operation)(double)) 
{
	for (int i = 0; i < count; i++)
		*(data + i) = operation(*(data + i));
	return this;
}

inline Matrix* Matrix::forEachIndexed(double (*operation)(int, int, double))
{
	for (int i = 0; i < count; i++)
		*(data + i) = operation(asRow(i), asCol(i), *(data + i));
	return this;
}

/* Mathematical ops */

Matrix& Matrix::operator+(Matrix& matrix) 
{
	Matrix* result = new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		(*result)[i] = *(data+i) + *(matrix.data+i);
	return *result;
}

Matrix& Matrix::operator*(double value)
{
	Matrix* result = new Matrix(rows, cols);
	for (int i = 0; i < count; ++i)
		*(result->data + i) = *(data + i);
	return *result;
}

Matrix& Matrix::operator-(Matrix& matrix)
{
	return *this + (matrix * (-1));
}

Matrix& Matrix::operator*(Matrix& matrix)
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

Matrix& Matrix::operator^(int exponent)
{
	if (exponent <= 0)
		throw new InvalidExponentError(exponent);
	Matrix* result = new Matrix(rows, cols, data), * temp = 0;
	for (int i = 1; i < exponent; i++) {
		temp = &(*result * *this);
		delete result;	// delete intermediary matrices
		result = temp;
	}
	return *result;
}
//NYI <=======
Matrix& Matrix::operator/(Matrix& matrix)
{
	return *this;
}

Matrix& Matrix::operator^(Matrix& matrix)
{
	return *this;
}