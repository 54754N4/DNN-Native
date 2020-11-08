#ifndef RMMATRIX_TPP
#define RMMATRIX_TPP

#ifndef RMMATRIX_H
#error __FILE__ should only be included from RMMatrix.h
#endif 

/* Consutructor */

template<int r, int c> 
RMMatrix::RMMatrix(long double(&matrix)[r][c]) : IMatrix(r, c), data(new long double[r*c])
{
	for (int i=0; i<count; ++i)
		data[cols * (i / cols) + (i % cols)] = matrix[i / cols][i % cols];
}

/* Iterators */

template<class Function>
RMMatrix& RMMatrix::iForEach(Function operation, bool inPlace)
{
	RMMatrix* ptr = inPlace ? this : new RMMatrix(*this);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = operation(data[i]);
	return *ptr;
}

template<class Function>
RMMatrix& RMMatrix::iForEachIndexed(Function operation, bool inPlace)
{
	RMMatrix* ptr = inPlace ? this : new RMMatrix(*this);
	for (int i = 0; i < count; ++i)
		ptr->data[i] = operation(asRow(i), asCol(i), data[i]);
	return *ptr;
}
#endif // !RMMATRIX_H