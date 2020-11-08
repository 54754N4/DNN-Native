#include <stdexcept>
#include <string>
#include <iostream>
#include "Models\CRTP.h"
#include "Models\Exceptions.h"
#include "Models\Vector\IVector.h"
#include "Models\Vector\Vector.h"
#include "Models\Matrix\IMatrix.h"
#include "Models\Matrix\RMMatrix.h"
#include "DNN\Layers\Transforms.h"
#include "DNN\Layers\Layers.h"

int main(char* args) 
{

	/* Test vectors */
	long double datav[3] = { 1,2,3 },
		datav1[4] = { 1,2,3,4 };
	Vector v1(datav);
	Vector v2(datav);
	
	v1.transpose();
	std::cout << "Vector: " << std::endl << v1.toString() << std::endl; 
	std::cout << "Length v1: " << v1.getLength() << std::endl;
	std::cout << "Length v2: " << v2.getLength() << std::endl;

	/* Test vector indexing */
	std::cout << v1(2) << std::endl;
	v1(2) = 4;
	std::cout << v1.toString() << std::endl;
	
	try {
		std::cout << (v1 - v2).toString() << std::endl;
	}
	catch (VectorsDifferentDimensionError& ex) {
		std::cout << ex.what() << std::endl;
	}

	std::cout << v1.hadamardProduct(v2).toString() << std::endl;

	/* Test Matrices */
	long double data[4][4] = {
		{1,2,3,4},
		{5,7,6,8},
		{9,10,12,11},
		{16,14,15,13}
	};
	RMMatrix matrix(data);
	RMMatrix matrix1(data);

	std::cout << matrix.toString() << std::endl;
	
	/* Test Dimensions */
	int rows, cols;
	matrix.getDimensions(rows, cols);
	std::cout << "Rows: " << rows << std::endl;
	std::cout << "Cols: " << cols << std::endl;
	
	/* Test indexing */
	std::cout << matrix(0, 1) << std::endl;
	
	/* Test iterators */
	auto printConsumer = [](long double value) -> long double {
		std::cout << value << std::endl;
		return value;
	};
	matrix.forEach(printConsumer);

	auto lambdaConsumer = [&](int row, int col, long double value) -> long double {		// use & default-capture for references
		if (row != 0 && col == 0) std::cout << std::endl;
		//std::cout << "Element at (" << row << "," << col << ") = " << value << std::endl;
		std::cout << row << "," << col << "=" << row * matrix.getCols() + col << "\t";
		return value;	// return same value to avoid changing it 
	};
	matrix.forEachIndexed(lambdaConsumer);
	std::cout << std::endl;

	auto incrementor = [](long double value) { return value + 1; };
	std::cout << matrix.forEach(incrementor).toString() << std::endl;

	std::cout << (matrix + matrix).toString() << std::endl;
	std::cout << (matrix * matrix1).toString() << std::endl;
	std::cout << (matrix^2).toString() << std::endl;
	
	std::cout << matrix.plus(matrix).toString() << std::endl;
	std::cout << matrix.times(matrix1).toString() << std::endl;
	std::cout << matrix.power(2).toString() << std::endl;
	
	std::cout << (RMMatrix::identity(10) ^ 2).toString() << std::endl;
	
	long double data2[] = { 1,2,3,4,5 };
	Vector b(data2);
	std::cout << RMMatrix::identity(5).plusRow(b).toString() << std::endl;

	std::cout << matrix.timesRow(1, 5).toString() << std::endl;

	std::cout << RMMatrix::identity(5).minor(1, 0).toString() << std::endl;

	std::cout << matrix.toString() << std::endl;
	std::cout << (matrix.det() == -126 ? "True" : "False") << std::endl;				// should print -126 

	long double cofactorData[3][3] = {
		{1,2,3},
		{0,4,5},
		{1,0,6}
	};
	RMMatrix cofm(cofactorData);
	std::cout << cofm.toString() << std::endl;
	std::cout << (cofm.det() == 22 ? "True" : "False") << std::endl;
	std::cout << cofm.cofactor().toString() << std::endl;

	long double transposeData[3][3] = {
		{ 1,2,3 },
		{ 4,5,6 },
		{ 7,8,9 }
	};
	RMMatrix transm(transposeData);
	std::cout << transm.toString() << std::endl;
	std::cout << transm.transpose().toString() << std::endl;

	long double inverseData[2][2] = {
		{ 4,7 },
		{ 2,6 }
	};
	RMMatrix invm(inverseData);
	std::cout << invm.toString() << std::endl;
	std::cout << invm.cofactor().toString() << std::endl;
	std::cout << invm.cofactor().transpose().toString() << std::endl;
	std::cout << invm.cofactor().transpose().times(1 / invm.det()).toString() << std::endl;
	std::cout << invm.inverse().toString() << std::endl;
	std::cout << invm.times(invm.inverse()).toString() << std::endl;
	std::cout << invm.times(invm.inverse()).toString() << std::endl;
	std::cout << (invm.times(invm.inverse()) == RMMatrix::identity(2)) << std::endl; // doesn't work due to precision
	std::cout << RMMatrix::identity(2).toString() << std::endl;

	std::cout << RMMatrix::identity(5).isUpperTriangular() << std::endl;

	std::cout << RMMatrix::diagonal(data2, 5).toString() << std::endl;

	RMMatrix mrow(1, 4, datav1);
	RMMatrix mcol(4, 1, datav1);
	std::cout << mrow.toString() << std::endl << mcol.toString() << std::endl;
	std::cout << (mcol * mrow).toString() << std::endl;

	long double softmaxData[3][3] = {
		{1,2,3},
		{4,5,6},
		{7,8,9}
	};
	long double biasData[3] = { 1, 2, 3 };
	RMMatrix weights(softmaxData);
	RMMatrix x(weights);
	Vector biases(biasData);

	/* Test swapping + inserting */
	std::cout << weights.toString() << std::endl;
	std::cout << weights.swapCols(2, 0).toString() << std::endl;
	std::cout << RMMatrix::spiral(3).toString() << std::endl;
	std::cout << biases.toString() << std::endl;
	std::cout << weights.insertCol(0, biases).toString() << std::endl;
	std::cout << "Det=" << RMMatrix::spiral(3).det() << std::endl;		// should be -72
	std::cout << weights.flatten().toString() << std::endl;

	/* Test transforms */
	/*long double* result = Transforms::softmax(datav, 3);
		for (int i = 0; i < 3; i++)
			std::cout << result[i] << " ";*/

	//std::cout << Transforms::identitym(weights).toString() << std::endl;

	/* Test Layers */
	/*biases.transpose(true);
	std::cout << (weights + weights).toString() << std::endl;
	std::cout << ((weights + weights) == weights * 2 ? "True" : "False") << std::endl;
	std::cout << biases.toString() << std::endl;
	std::cout << (weights + biases).toString() << std::endl;
	std::cout << RMMatrix::zeros(3).insertCol(0, biases).getSparsity() << std::endl;*/

	/*Layers::Sigmoid<RMMatrix> layer1(4, 4, weights, biases);
	Layers::NOP<RMMatrix> layer2(4, 4, weights, biases);*/
	/*std::cout << layer1.inputs << "," << layer1.neurons << std::endl;
	std::cout << weights.flatten().toString() << std::endl;
	std::cout << x.toString() << std::endl;
	std::cout << layer1.applyActivation(x).toString() << std::endl;
	std::cout << layer2.applyActivation(x).toString() << std::endl;*/
}