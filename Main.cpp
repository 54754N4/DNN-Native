#include <stdexcept>
#include <string>
#include <iostream>
#include "Models/Vector.h"
#include "Models/Exceptions.h"
#include "Models/Matrix.h"

int main(char* args) {
	double data[4][4] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16}
	};
	Matrix matrix(data);
	Matrix matrix1(data);
	//std::cout << matrix.toString() << std::endl;
	/* Test Dimensions */
	/*long rows, cols;
	matrix.getDimensions(&rows, &cols);
	std::cout << "Rows: " << rows << std::endl;
	std::cout << "Cols: " << cols << std::endl;*/
	
	/* Test indexing */
	//std::cout << matrix(0l, 1l) << std::endl;
	
	/* Test iterators */
	/*auto printConsumer = [](double value) -> double {
		std::cout << value << std::endl;
		return value;
	};
	matrix.forEach(printConsumer);*/

	auto lambdaConsumer = [&](int row, int col, double value) -> double {		// use & default-capture for references
		if (row != 0 && col == 0) std::cout << std::endl;
		//std::cout << "Element at (" << row << "," << col << ") = " << value << std::endl;
		std::cout << row << "," << col << "=" << row * matrix.cols + col << "\t";
		return value;	// return same value to avoid changing it 
	};
	matrix.forEachIndexed(lambdaConsumer);
	std::cout << std::endl;

	/*auto incrementor = [](double value) { return value + 1; };
	matrix.forEach(incrementor);
	std::cout << matrix.toString() << std::endl;*/

	/* Test vectors */
	/*double datav[3] = { 1,2,3 },
		datav1[4] = {1,2,3,4};
	Vector v1(datav);
	Vector v2(datav);*/
	/*vector.transpose();*/
	/*std::cout << v1.toString() << std::endl;
	std::cout << v1.getLength() << std::endl;*/

	/* Test vector indexing */
	//std::cout << vector(2) << std::endl;
	/*vector(2) = 4;
	std::cout << vector.toString() << std::endl;*/

	/*try {
		std::cout << (v1 - v2).toString() << std::endl;
	} catch (VectorsDifferentDimension& ex) {
		std::cout << ex.what() << std::endl;
	}*/
	
	//std::cout << v1.hadamardProduct(v2).toString() << std::endl;

	/*std::cout << (matrix + matrix).toString() << std::endl;
	std::cout << (matrix * matrix1).toString() << std::endl;
	std::cout << (matrix^2).toString() << std::endl;*/
	
	/*std::cout << matrix.plus(matrix).toString() << std::endl;
	std::cout << matrix.times(matrix1).toString() << std::endl;
	std::cout << matrix.power(2).toString() << std::endl;
	
	std::cout << (Matrix::identity(10) ^ 2).toString() << std::endl;*/
	
	double data2[] = { 1,2,3,4,5 };
	Vector b(data2);
	std::cout << Matrix::identity(5).plusRow(b).toString() << std::endl;
}