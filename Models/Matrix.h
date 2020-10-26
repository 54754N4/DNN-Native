#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
	/* Attributes */
	const int rows, cols, count;

	/* Constructors and destructor */
	inline Matrix();
	Matrix(int size);
	Matrix(int row, int col);
	Matrix(int row, int col, const double initial);
	Matrix(int row, int col, const double* results);
	template<int r, int c>
	Matrix(double (&data)[r][c]);
	~Matrix();
	/* Accessors */
	bool isSquare();
	int getRows();
	int getCols();
	int getCount();
	double getTrace();
	Matrix& getDimensions(int* rows, int* cols);
	inline double& get(int row, int col) const;
	/* Iterators */
	template<class Function>
	Matrix& forEach(Function operation);		// input: double			| output: double
	template<class Function>
	Matrix& forEachIndexed(Function operation);	// input: int, int, double	| output: double
	/* Utility methods */
	Matrix& indexToCoords(int index, int* outRow, int* outCol);
	std::string toString();
	/* General operations */
	Matrix& plusRow(Vector& row);
	Matrix& plusCol(Vector& col);
	Matrix& swapRows(int first, int second);
	Matrix& swapCols(int first, int second);
	Matrix& timesRow(int row, double multiplier);
	Matrix& timesCol(int row, double multiplier);
	inline Matrix& plus(Matrix& matrix);
	inline Matrix& times(double scalar);
	inline Matrix& minus(Matrix& matrix);
	inline Matrix& times(Matrix& matrix);
	inline Matrix& power(int exponent);
	inline Matrix& hadamardTimes(Matrix& matrix);
	inline Matrix& divide(Matrix& matrix);
	Matrix& operator+(Matrix& matrix);				// addition
	Matrix& operator*(double scalar);				// scalar multiplication
	Matrix& operator-(Matrix& matrix);				// substraction
	Matrix& operator*(Matrix& matrix);				// multiplication
	Matrix& operator^(int exponent);				// power
	Matrix& operator^(Matrix& matrix);				// hadamard
	Matrix& operator/(Matrix& matrix);				// division
	/* Static */
	static Matrix& identity(int size);
	/* Special operations */
	Matrix& minor(int row, int column);
	double det();
	/* 1D indexing */
	inline double& operator()(int index) { return *(data + index); };		
	inline double& operator()(int index) const { return *(data + index); };
	inline double& operator[](int index) { return *(data + index); };
	inline double& operator[](int index) const { return *(data + index); };
	/* 2D indexing */
	double operator()(int row, int col) const;		// for const objects
	inline double& operator()(int row, int col) { return *(data + cols * row + col); };
private:
	double* data;

	void initialize(const double value);
	inline int asRow(int index);
	inline int asCol(int index);
};

#include "Matrix.tpp"	// Include function template definition

#endif	// !MATRIX_H