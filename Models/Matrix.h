#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
	/* Attributes */
	long double* data;
	int rows, cols, count;
public:
	/* Constructors and destructor */
	inline Matrix();
	Matrix(int size);
	Matrix(int row, int col);
	Matrix(int row, int col, const long double initial);
	Matrix(int row, int col, const long double* results);
	Matrix(const Matrix& matrix);
	template<int r, int c>
	Matrix(long double(&data)[r][c]);
	~Matrix();
	/* Accessors */
	bool isSquare() const;
	bool isDiagonal() const;
	bool isLowerTriangular() const;
	bool isUpperTriangular() const;
	float getSparsity() const;
	int getRows() const;
	int getCols() const;
	int getCount() const;
	long double getTrace() const;
	long double getSum() const;
	long double* getData() const;
	Matrix& getDimensions(int& rows, int& cols);
	inline long double& get(int row, int col) const;
	/* Iterators */
	template<class Function>
	Matrix& forEach(Function operation, bool inPlace = false);			// input: double			| output: double
	template<class Function>
	Matrix& forEachIndexed(Function operation, bool inPlace = false);	// input: int, int, double	| output: double
	/* Special operations */
	Matrix& minor(int row, int column) const;
	inline long double det() const;
	Matrix& transpose() const;
	Matrix& cofactor() const;
	Matrix& adjugate() const;
	/* Other */
	Matrix& flatten(bool col = false, bool inPlace = false);
	/* Utility methods */
	void cloneFrom(Matrix& matrix);
	Matrix& clone();
	const bool isDiagonal(int index);
	Matrix& indexToCoords(int index, int* outRow, int* outCol);
	std::string toString();
	/* General operations */
	const bool equals(const Matrix& matrix) const;
	Matrix& plusRow(Vector& row, bool inPlace = false);
	Matrix& plusCol(Vector& col, bool inPlace = false);
	Matrix& insertRow(int row, Vector& data, bool inPlace = false);
	Matrix& insertCol(int col, Vector& data, bool inPlace = false);
	Matrix& swapRows(int first, int second);
	Matrix& swapCols(int first, int second);
	Matrix& timesRow(int row, long double multiplier, bool inPlace = false);
	Matrix& timesCol(int row, long double multiplier, bool inPlace = false);
	inline Matrix& plus(Matrix& matrix, bool inPlace = false);
	inline Matrix& times(long double scalar, bool inPlace = false);
	inline Matrix& minus(Matrix& matrix, bool inPlace = false);
	inline Matrix& times(Matrix& matrix);
	inline Matrix& power(int exponent);
	inline Matrix& hadamardTimes(Matrix& matrix, bool inPlace = false);
	Matrix& inverse();								// should i inline
	inline Matrix& divide(Matrix& matrix);
	Matrix& operator+(Vector& vector);
	Matrix& operator+(Matrix& matrix);				// addition
	Matrix& operator*(long double scalar);			// scalar multiplication
	Matrix& operator-(Matrix& matrix);				// substraction
	Matrix& operator*(Matrix& matrix);				// multiplication
	Matrix& operator^(int exponent);				// power
	Matrix& operator^(Matrix& matrix);				// hadamard
	Matrix& operator/(Matrix& matrix);				// division
	Matrix& operator+=(Vector& vector);
	Matrix& operator+=(Matrix& matrix);				
	Matrix& operator*=(long double scalar);			
	Matrix& operator-=(Matrix& matrix);				
	Matrix& operator*=(Matrix& matrix);				
	Matrix& operator^=(int exponent);				
	Matrix& operator^=(Matrix& matrix);				
	Matrix& operator/=(Matrix& matrix);				
	/* Inline operators */
	inline const bool operator==(Matrix& matrix) { return equals(matrix); };
	inline const bool operator==(const Matrix& matrix) const { return equals(matrix); };
	/* 1D indexing */
	inline long double& operator()(int index) { return data[index]; };
	inline long double& operator()(int index) const { return data[index]; };
	inline long double& operator[](int index) { return data[index]; };
	inline long double& operator[](int index) const { return data[index]; };
	/* 2D indexing */
	long double operator()(int row, int col) const;		// for const objects
	inline long double& operator()(int row, int col) { return data[cols * row + col]; };
	/* Debug */
	void spit();
	/* Static */
	static Matrix& zeros(int size);
	static Matrix& zeros(int row, int col);
	static Matrix& ones(int size);
	static Matrix& ones(int row, int col);
	static Matrix& identity(int size);
	static Matrix& spiral(int size);
	static Matrix& diagonal(long double* data, int count);
private:
	void initialize(const long double value);
	inline int asRow(int index);
	inline int asCol(int index);
};

#include "Matrix.tpp"	// Include function template definition

#endif	// !MATRIX_H