#ifndef MATRIX_TPP
#define MATRIX_TPP

#ifndef MATRIX_H
#error __FILE__ should only be included from Matrix.h
#endif 

template<int r, int c> 
Matrix::Matrix(double (&matrix)[r][c]) : rows(r), cols(c), count(r * c) {
	data = new double[rows * cols];
	for (int x = 0; x < rows; x++)
		for (int y = 0; y < cols; y++)
			*(data + cols * x + y) = matrix[x][y];
}
#endif 