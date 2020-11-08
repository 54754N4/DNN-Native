#ifndef IMATRIX_H
#define IMATRIX_H

template<typename I> 
class IMatrix: public CRTP< I >
{
protected:
	int rows{ 0 }, cols{ 0 }, count{ 0 };
public:
	/* Constructors and destructor */
	IMatrix();
	explicit IMatrix(int size);	// explicit to avoid it being used as implicit convertion ctor
	IMatrix(int row, int col);
	IMatrix(const I& matrix);
	virtual ~IMatrix() {};
	/* Move semantics */
	IMatrix(const I& matrix);				// copy constructor	
	IMatrix(I&& matrix) noexcept;			// move constructor
	I& operator=(const I& matrix);			// copy assignment operator
	I& operator=(I&& matrix) noexcept;		// move assignment operator
	virtual I& copyFrom(const I& matrix) = 0;
	virtual I& moveFrom(I&& matrix) = 0;
	/* Accessors */
	I& getDimensions(int& rows, int& cols);
	bool isSquare() const;
	int getRows() const;
	int getCols() const;
	int getCount() const;
	long double* getData() const;
	/* Special operations */
	std::string toString() ;
	bool isDiagonal() const;
	bool isLowerTriangular() const;
	bool isUpperTriangular() const;
	float getSparsity() const;
	long double getTrace() const;
	long double getSum() const;
	inline long double det() const;
	I& minor(int row, int column) const;
	I& transpose() const;
	I& cofactor() const;
	I& adjugate() const;
	I& flatten(bool col = false, bool inPlace = false);
	/* Math operations */
	I& plusRow(IVector& row, bool inPlace = false);
	I& plusCol(IVector& col, bool inPlace = false);
	I& insertRow(int row, IVector& data, bool inPlace = false);
	I& insertCol(int col, IVector& data, bool inPlace = false);
	I& swapRows(int first, int second);
	I& swapCols(int first, int second);
	I& timesRow(int row, long double multiplier, bool inPlace = false);
	I& timesCol(int row, long double multiplier, bool inPlace = false);
	I& plus(I& matrix, bool inPlace = false);
	I& times(long double scalar, bool inPlace = false);
	I& minus(I& matrix, bool inPlace = false);
	I& times(I& matrix);
	I& power(int exponent);
	I& hadamardTimes(I& matrix, bool inPlace = false);
	I& inverse();
	I& divide(I& matrix);
	const bool equals(const I& matrix) const;
	/* Operator overloads */
	I& operator+(IVector& vector);
	I& operator+(I& matrix);				// addition
	I& operator*(long double scalar);		// scalar multiplication
	I& operator-(I& matrix);				// substraction
	I& operator*(I& matrix);				// multiplication
	I& operator^(int exponent);				// power
	I& operator^(I& matrix);				// hadamard
	I& operator/(I& matrix);				// division
	I& operator+=(IVector& vector);
	I& operator+=(I& matrix);
	I& operator*=(long double scalar);
	I& operator-=(I& matrix);
	I& operator*=(I& matrix);
	I& operator^=(int exponent);
	I& operator^=(I& matrix);
	I& operator/=(I& matrix);
	/* Inline operators */
	inline long double& get(int row, int col) const;
	inline long double& get(int index) const;
	inline const bool operator==(I& matrix);
	inline const bool operator==(const I& matrix) const;
	/* 1D indexing */
	inline long double& operator()(int index);
	inline long double& operator()(int index) const;
	inline long double& operator[](int index);
	inline long double& operator[](int index) const;
	/* 2D indexing */
	inline long double& operator()(int row, int col);
	inline long double operator()(int row, int col) const;
	
	/* Constructors cannot be virtual*/
	//IMatrix(int row, int col, const long double initial);
	//IMatrix(int row, int col, const long double* results);
	//IMatrix(const I& matrix);
	//template<int r, int c> IMatrix(long double(&data)[r][c]);
	//IMatrix(const I& matrix);	// copy constructor

	/* Iterator function templates*/
	template<class Function>
	I& forEach(Function operation, bool inPlace = false)			// input: double			| output: double
	{
		return CRTP<I>::self->iForEach(operation, inPlace);
	};

	template<class Function>
	I& forEachIndexed(Function operation, bool inPlace = false)		// input: int, int, double	| output: double
	{
		return CRTP<I>::self->iForEachIndexed(operation, inPlace);
	};

	/* Static functions (using static polymorphism) */
	static I& zeros(int size);
	static I& zeros(int row, int col);
	static I& ones(int size);
	static I& ones(int row, int col);
	static I& identity(int size);
	static I& spiral(int size);
	static I& diagonal(long double* data, int count);
};

#include "IMatrix.tpp"

#endif