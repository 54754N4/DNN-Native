#ifndef MATRIX_TPP
#define MATRIX_TPP

#ifndef MATRIX_H
#error __FILE__ should only be included from Matrix.h
#endif 

/* Consutructor */

template<int r, int c> 
Matrix::Matrix(long double(&matrix)[r][c]) : rows(r), cols(c), count(r * c)
{
	data = new long double[count];
	for (int i=0; i<count; ++i)
			*(data + cols * (i / cols) + (i % cols)) = matrix[i / cols][i % cols];
}

/* Iterators */

template<class Function>
Matrix& Matrix::forEach(Function operation)
{
	for (int i = 0; i < count; i++)
		*(data + i) = operation(*(data + i));
	return *this;
}

template<class Function>
Matrix& Matrix::forEachIndexed(Function operation)
{
	for (int i = 0; i < count; i++)
		*(data + i) = operation(asRow(i), asCol(i), *(data + i));
	return *this;
}
#endif 