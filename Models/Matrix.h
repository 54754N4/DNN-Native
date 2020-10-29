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
	Matrix(int row, int col, const long double initial);
	Matrix(int row, int col, const long double* results);
	template<int r, int c>
	Matrix(long double(&data)[r][c]);
	~Matrix();
	/* Accessors */
	bool isSquare();
	bool isDiagonal();
	bool isLowerTriangular();
	bool isUpperTriangular();
	int getRows();
	int getCols();
	int getCount();
	long double getTrace();
	long double* getData();
	Matrix& getDimensions(int& rows, int& cols);
	inline long double& get(int row, int col) const;
	/* Iterators */
	template<class Function>
	Matrix& forEach(Function operation);		// input: double			| output: double
	template<class Function>
	Matrix& forEachIndexed(Function operation);	// input: int, int, double	| output: double
	/* Utility methods */
	const bool isDiagonal(int index);
	Matrix& indexToCoords(int index, int* outRow, int* outCol);
	std::string toString();
	/* General operations */
	const bool equals(const Matrix& matrix) const;
	Matrix& plusRow(Vector& row);
	Matrix& plusCol(Vector& col);
	Matrix& swapRows(int first, int second);
	Matrix& swapCols(int first, int second);
	Matrix& timesRow(int row, long double multiplier);
	Matrix& timesCol(int row, long double multiplier);
	inline Matrix& plus(Matrix& matrix);
	inline Matrix& times(long double scalar);
	inline Matrix& minus(Matrix& matrix);
	inline Matrix& times(Matrix& matrix);
	inline Matrix& power(int exponent);
	inline Matrix& hadamardTimes(Matrix& matrix);
	Matrix& inverse();								// should i inline
	inline Matrix& divide(Matrix& matrix);
	Matrix& operator+(Matrix& matrix);				// addition
	Matrix& operator*(long double scalar);			// scalar multiplication
	Matrix& operator-(Matrix& matrix);				// substraction
	Matrix& operator*(Matrix& matrix);				// multiplication
	Matrix& operator^(int exponent);				// power
	Matrix& operator^(Matrix& matrix);				// hadamard
	Matrix& operator/(Matrix& matrix);				// division
	/* Static */
	static Matrix& identity(int size);
	static Matrix& diagonal(long double* data, int count);
	/* Special operations */
	Matrix& minor(int row, int column);
	inline long double det();
	Matrix& transpose();
	Matrix& cofactor();
	Matrix& adjugate();
	/* Other */
	Matrix& flatten(bool col=true);
	/* Inline operators */
	inline const bool operator==(Matrix& matrix) { return equals(matrix); };
	inline const bool operator==(const Matrix& matrix) const { return equals(matrix); };
	/* 1D indexing */
	inline long double& operator()(int index) { return *(data + index); };
	inline long double& operator()(int index) const { return *(data + index); };
	inline long double& operator[](int index) { return *(data + index); };
	inline long double& operator[](int index) const { return *(data + index); };
	/* 2D indexing */
	long double operator()(int row, int col) const;		// for const objects
	inline long double& operator()(int row, int col) { return *(data + cols * row + col); };
	/* Debug */
	void spit();
private:
	long double* data;

	void initialize(const long double value);
	inline int asRow(int index);
	inline int asCol(int index);
};

#include "Matrix.tpp"	// Include function template definition

#endif	// !MATRIX_H