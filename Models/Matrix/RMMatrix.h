#ifndef RMMATRIX_H
#define RMMATRIX_H

class RMMatrix: public IMatrix<RMMatrix>
{
	friend class IMatrix<RMMatrix>;
	/* Attributes */
	long double* data{ nullptr };
public:
	/* Constructors and destructor */
	RMMatrix();
	explicit RMMatrix(int size);
	RMMatrix(int row, int col);
	RMMatrix(int row, int col, const long double initial);
	RMMatrix(int row, int col, const long double* results);
	template<int r, int c>
	RMMatrix(long double(&data)[r][c]);
	~RMMatrix();
	/* Move semantics */
	RMMatrix(const RMMatrix& matrix);				// copy constructor	
	RMMatrix(RMMatrix&& matrix) noexcept;			// move constructor
	RMMatrix& operator=(const RMMatrix& matrix);	// copy assignment operator
	RMMatrix& operator=(RMMatrix&& matrix) noexcept;			// move assignment operator
	RMMatrix& copyFrom(const RMMatrix& matrix) override;
	RMMatrix& moveFrom(RMMatrix&& matrix) override;
	/* Index utility methods */
	inline int asRow(int index);
	inline int asCol(int index);
	const bool isDiagonal(int index);
	RMMatrix& indexToCoords(int index, int* outRow, int* outCol);
	/* Accessors */
	long double* iGetData() const;
	inline long double& iGet(int index) const;
	inline long double& iGet(int row, int col) const;
	bool iIsDiagonal() const;
	bool iIsLowerTriangular() const;
	bool iIsUpperTriangular() const;
	float iGetSparsity() const;
	long double iGetTrace() const;
	long double iGetSum() const;
	std::string iToString() const;
	/* General operations */
	RMMatrix& iPlusRow(IVector& row, bool inPlace = false);
	RMMatrix& iPlusCol(IVector& col, bool inPlace = false);
	RMMatrix& iInsertRow(int row, IVector& data, bool inPlace = false);
	RMMatrix& iInsertCol(int col, IVector& data, bool inPlace = false);
	RMMatrix& iTimesRow(int row, long double multiplier, bool inPlace = false);
	RMMatrix& iTimesCol(int row, long double multiplier, bool inPlace = false);
	RMMatrix& iSwapRows(int first, int second);
	RMMatrix& iSwapCols(int first, int second);
	const bool iEquals(const RMMatrix& matrix) const;
	inline RMMatrix& iPlus(RMMatrix& matrix, bool inPlace = false);
	inline RMMatrix& iTimes(long double scalar, bool inPlace = false);
	inline RMMatrix& iMinus(RMMatrix& matrix, bool inPlace = false);
	inline RMMatrix& iTimes(RMMatrix& matrix);
	inline RMMatrix& iPower(int exponent);
	inline RMMatrix& iHadamardTimes(RMMatrix& matrix, bool inPlace = false);
	RMMatrix& iInverse();
	inline RMMatrix& iDivide(RMMatrix& matrix);
	/* Special operations */
	long double iDet() const;
	RMMatrix& iMinor(int row, int column) const;
	RMMatrix& iTranspose() const;
	RMMatrix& iCofactor() const;
	RMMatrix& iAdjugate() const;
	RMMatrix& iFlatten(bool col = false, bool inPlace = false);
	///* Operator overloads */
	//RMMatrix& operator+(IVector& vector) override;				// vector row/col addition
	//RMMatrix& operator+(RMMatrix& matrix) override;				// addition
	//RMMatrix& operator*(long double scalar) override;			// scalar multiplication
	//RMMatrix& operator-(RMMatrix& matrix) override;				// substraction
	//RMMatrix& operator*(RMMatrix& matrix) override;				// multiplication
	//RMMatrix& operator^(int exponent) override;					// power
	//RMMatrix& operator^(RMMatrix& matrix) override;				// hadamard
	//RMMatrix& operator/(RMMatrix& matrix) override;				// division
	//RMMatrix& operator+=(IVector& vector) override;
	//RMMatrix& operator+=(RMMatrix& matrix) override;
	//RMMatrix& operator*=(long double scalar) override;
	//RMMatrix& operator-=(RMMatrix& matrix) override;
	//RMMatrix& operator*=(RMMatrix& matrix) override;
	//RMMatrix& operator^=(int exponent) override;
	//RMMatrix& operator^=(RMMatrix& matrix) override;
	//RMMatrix& operator/=(RMMatrix& matrix) override;
	/* Iterators */
	template<class Function>
	RMMatrix& iForEach(Function operation, bool inPlace = false);			// input: double			| output: double
	template<class Function>
	RMMatrix& iForEachIndexed(Function operation, bool inPlace = false);	// input: int, int, double	| output: double
	///* Inline operators */
	//inline const bool operator==(RMMatrix& matrix) { return equals(matrix); };
	//inline const bool operator==(const RMMatrix& matrix) const { return equals(matrix); };
	///* 1D indexing */
	//inline long double& operator()(int index) { return data[index]; };
	//inline long double& operator()(int index) const { return data[index]; };
	//inline long double& operator[](int index) { return data[index]; };
	//inline long double& operator[](int index) const { return data[index]; };
	///* 2D indexing */
	//long double operator()(int row, int col) const override;		// for const objects
	//inline long double& operator()(int row, int col) { return data[cols * row + col]; };
	/* Debug */
	void spit();
	/* Static */
	static RMMatrix& zeros(int size);
	static RMMatrix& zeros(int row, int col);
	static RMMatrix& ones(int size);
	static RMMatrix& ones(int row, int col);
	static RMMatrix& identity(int size);
	static RMMatrix& spiral(int size);
	static RMMatrix& diagonal(long double* data, int count);
private:
	void initialize(const long double value);
};

#include "RMMatrix.tpp"	// Include function template definition

#endif	// !RMMATRIX_H