#ifndef IMATRIX_TPP
#define IMATRIX_TPP

#ifndef IMATRIX_H
#error __FILE__ should only be included from Matrix.h
#endif 

/* Constructors */

template<class I>
IMatrix<I>::IMatrix() {}
template<class I>
IMatrix<I>::IMatrix(int size)
	: rows(size), cols(size), count(size* size) {}
template<class I>
IMatrix<I>::IMatrix(int row, int col)
	: rows(row), cols(col), count(row* col) {}
template<class I>
IMatrix<I>::IMatrix(const I& matrix)
	: rows(matrix.rows), cols(matrix.cols), count(matrix.count) {}

/* Accessors */
template<class I>
I& IMatrix<I>::getDimensions(int& rows, int& cols)
{
	rows = this->rows;
	cols = this->cols;
	return CRTP<I>::self();
}

template<class I>
bool IMatrix<I>::isSquare() const
{
	return rows == cols;
}

template<class I>
int IMatrix<I>::getRows() const
{
	return rows;
}

template<class I>
int IMatrix<I>::getCols() const
{
	return cols;
}

template<class I>
int IMatrix<I>::getCount() const
{
	return count;
}

/* Move semantics */
template<class I>
IMatrix<I>::IMatrix(const I& matrix)				// copy constructor	
	: rows(matrix.rows), cols(matrix.cols), count(matrix.count) 
{
	CRTP<I>::self->copyFrom(matrix);
}

template<class I>
IMatrix<I>::IMatrix(I&& matrix) noexcept			// move constructor
	: rows(matrix.rows), cols(matrix.cols), count(matrix.count)
{
	CRTP<I>::self->moveFrom(matrix);
}

template<class I>
I& IMatrix<I>::operator=(const I& matrix)			// copy assignment operator
{
	return CRTP<I>::self->copyFrom(matrix);
}

template<class I>
I& IMatrix<I>::operator=(I&& matrix) noexcept		// move assignment operator
{
	return CRTP<I>::self->moveFrom(matrix);
}

/* CRTP Interface methods */
template<typename I>
long double* IMatrix<I>::getData() const{
	return CRTP<I>::self()->iGetData();
}

/* Special operations */
template<typename I>
std::string IMatrix<I>::toString(){
	return CRTP<I>::self()->iToString();
}

template<typename I>
bool IMatrix<I>::isDiagonal() const{
	return CRTP<I>::self()->iIsDiagonal();
}

template<typename I>
bool IMatrix<I>::isLowerTriangular() const{
	return CRTP<I>::self()->iIsLowerTriangular();
}

template<typename I>
bool IMatrix<I>::isUpperTriangular() const{
	return CRTP<I>::self()->iIsUpperTriangular();
}

template<typename I>
float IMatrix<I>::getSparsity() const{
	return CRTP<I>::self()->iGetSparsity();
}

template<typename I>
long double IMatrix<I>::getTrace() const{
	return CRTP<I>::self()->iGetTrace();
}

template<typename I>
long double IMatrix<I>::getSum() const{
	return CRTP<I>::self()->iGetSum();
}

template<typename I>
long double IMatrix<I>::det() const{
	return CRTP<I>::self()->iDet();
}

template<typename I>
I& IMatrix<I>::minor(int row, int col) const{
	return CRTP<I>::self()->iMinor(row, col);
}

template<typename I>
I& IMatrix<I>::transpose() const{
	return CRTP<I>::self()->iTranspose();
}

template<typename I>
I& IMatrix<I>::cofactor() const{
	return CRTP<I>::self()->iCofactor();
}

template<typename I>
I& IMatrix<I>::adjugate() const{
	return CRTP<I>::self()->iAdjugate();
}

template<typename I>
I& IMatrix<I>::flatten(bool col, bool inPlace){
	return CRTP<I>::self()->iFlatten(col, inPlace);
}

/* Math operations */
template<typename I>
I& IMatrix<I>::plusRow(IVector& row, bool inPlace){
	return CRTP<I>::self()->iPlusRow(row, inPlace);
}

template<typename I>
I& IMatrix<I>::plusCol(IVector& col, bool inPlace){
	return CRTP<I>::self()->iPlusCol(col, inPlace);
}

template<typename I>
I& IMatrix<I>::insertRow(int row, IVector& data, bool inPlace){
	return CRTP<I>::self()->iInsertRow(row, data, inPlace);
}

template<typename I>
I& IMatrix<I>::insertCol(int col, IVector& data, bool inPlace){
	return CRTP<I>::self()->iInsertCol(col, data, inPlace);
}

template<typename I>
I& IMatrix<I>::swapRows(int first, int second){
	return CRTP<I>::self()->iSwapRows(first, second);
}

template<typename I>
I& IMatrix<I>::swapCols(int first, int second){
	return CRTP<I>::self()->iSwapCols(first, second);
}

template<typename I>
I& IMatrix<I>::timesRow(int row, long double multiplier, bool inPlace){
	return CRTP<I>::self()->iTimesRow(row, multiplier, inPlace);
}

template<typename I>
I& IMatrix<I>::timesCol(int row, long double multiplier, bool inPlace){
	return CRTP<I>::self()->iTimesCol(row, multiplier, inPlace);
}

template<typename I>
I& IMatrix<I>::plus(I& matrix, bool inPlace){
	return CRTP<I>::self()->iPlus(matrix, inPlace);
}

template<typename I>
I& IMatrix<I>::times(long double scalar, bool inPlace){
	return CRTP<I>::self()->iTime(scalar, inPlace);
}

template<typename I>
I& IMatrix<I>::minus(I& matrix, bool inPlace){
	return CRTP<I>::self()->iMinus(matrix, inPlace);
}

template<typename I>
I& IMatrix<I>::times(I& matrix){
	return CRTP<I>::self()->iTimes(matrix);
}

template<typename I>
I& IMatrix<I>::power(int exponent){
	return CRTP<I>::self()->iPower(exponent);
}

template<typename I>
I& IMatrix<I>::hadamardTimes(I& matrix, bool inPlace){
	return CRTP<I>::self()->iHadamardTimes(matrix, inPlace);
}

template<typename I>
I& IMatrix<I>::inverse(){
	return CRTP<I>::self()->iInverse();
}

template<typename I>
I& IMatrix<I>::divide(I& matrix){
	return CRTP<I>::self()->iDivide(matrix);
}

template<typename I>
const bool IMatrix<I>::equals(const I& matrix) const{
	return CRTP<I>::self()->iEquals(matrix);
}

/* Operator overloads */
template<typename I>
I& IMatrix<I>::operator+(IVector& vector){
	return plus(vector);
}

template<typename I>
I& IMatrix<I>::operator+(I& matrix){
	return plus(matrix);
}

template<typename I>
I& IMatrix<I>::operator*(long double scalar){
	return times(scalar);
}

template<typename I>
I& IMatrix<I>::operator-(I& matrix){
	return minus(matrix);
}

template<typename I>
I& IMatrix<I>::operator*(I& matrix){
	return times(matrix);
}

template<typename I>
I& IMatrix<I>::operator^(int exponent){
	return power(exponent);
}

template<typename I>
I& IMatrix<I>::operator^(I& matrix){
	return hadamardTimes(matrix);
}

template<typename I>
I& IMatrix<I>::operator/(I& matrix){
	return divide(matrix);
}

template<typename I>
I& IMatrix<I>::operator+=(IVector& vector){
	return vector.isRow() ? plusRow(vector, true) : plusCol(vector, true);
}

template<typename I>
I& IMatrix<I>::operator+=(I& matrix){
	return plus(matrix, true);
}

template<typename I>
I& IMatrix<I>::operator*=(long double scalar){
	return times(scalar, true);
}

template<typename I>
I& IMatrix<I>::operator-=(I& matrix){
	return minus(matrix, true);
}

template<typename I>
I& IMatrix<I>::operator*=(I& matrix){
	return *this = std::move(times(matrix));
}

template<typename I>
I& IMatrix<I>::operator^=(int exponent){
	return *this = std::move(power(exponent));
}

template<typename I>
I& IMatrix<I>::operator^=(I& matrix){
	return *this = std::move(times(matrix));
}

template<typename I>
I& IMatrix<I>::operator/=(I& matrix){
	return *I = std::move(divide(matrix));	// wtf
}

/* Inline operators */
template<typename I>
long double& IMatrix<I>::get(int row, int col) const{
	return CRTP<I>::self()->iGet(row, col);
}

template<typename I>
long double& IMatrix<I>::get(int index) const {
	return CRTP<I>::self()->iGet(index);
}

template<typename I>
const bool IMatrix<I>::operator==(I& matrix){
	return equals(matrix);
}

template<typename I>
const bool IMatrix<I>::operator==(const I& matrix) const{
	return equals(matrix);
}

/* 1D indexing */
template<typename I>
long double& IMatrix<I>::operator()(int index){
	return get(index);
}

template<typename I>
long double& IMatrix<I>::operator()(int index) const{
	return get(index);
}

template<typename I>
long double& IMatrix<I>::operator[](int index){
	return get(index);
}

template<typename I>
long double& IMatrix<I>::operator[](int index) const{
	return get(index);
}

/* 2D indexing */
template<typename I>
long double& IMatrix<I>::operator()(int row, int col){
	return get(row, col);
}

template<typename I>
long double IMatrix<I>::operator()(int row, int col) const{
	return get(row, col);
}

/* Static polymorphism */
template<class I>
static I& IMatrix<I>::zeros(int size)
{
	return I::zeros(size);
}

template<class I>
static I& IMatrix<I>::zeros(int row, int col)
{
	return I::zeros(row, col);
}

template<class I>
static I& IMatrix<I>::ones(int size)
{
	return I::ones(size);
}

template<class I>
static I& IMatrix<I>::ones(int row, int col)
{
	return I::ones(row, col);
}

template<class I>
static I& IMatrix<I>::identity(int size)
{
	return I::identity(size);
}

template<class I>
static I& IMatrix<I>::spiral(int size)
{
	return I::spiral(size);
}

template<class I>
static I& IMatrix<I>::diagonal(long double* data, int count)
{
	return I::diagonal(data, count);
}

#endif