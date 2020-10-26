#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
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
	inline bool isSquare();
	inline int getRows();
	inline int getCols();
	inline int getCount();
	Matrix* getDimensions(int* rows, int* cols);
	inline double& get(int row, int col) const;
	/* Iterators */
	inline Matrix* forEach(double (*operation)(double));
	inline Matrix* forEachIndexed(double (*operation)(int, int, double));
	/* Utility methods */
	Matrix* indexToCoords(int index, int* outRow, int* outCol);
	std::string toString();
	/* Math operations */
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
	/* 1D indexing */
	inline double& operator()(int index) { return *(data + index); };		
	inline double& operator()(int index) const { return *(data + index); };
	inline double& operator[](int index) { return *(data + index); };
	inline double& operator[](int index) const { return *(data + index); };
	/* 2D indexing */
	double operator()(int row, int col) const;		// for const objects
	inline double& operator()(int row, int col) { return *(data + cols * row + col); };
	/* Static */
	static Matrix& identity(int size);
private:
	int rows, cols, count;
	double* data;

	void initialize(const double value);
	inline int asRow(int index);
	inline int asCol(int index);
	std::string cryOutOfRange(int row, int col, int rows, int cols);
};

#include "Matrix.tpp"	// Include function template definition

#endif	// !MATRIX_H