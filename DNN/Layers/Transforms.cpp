#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include "..\..\Models\Exceptions.h"
#include "..\..\Models\Vector.h"
#include "..\..\Models\Matrix.h"
#include "Transforms.h"

long double max(long double* data, const int count)
{
	long double max = 0;
	for (int i = 0; i < count; ++i)
		if (*(data + i) > max)
			max = *(data + i);
	return max;
}

long double coth(long double x)
{
	return cosh(x) / sinh(x);
}

long double sech(long double x)
{
	return 1 / cosh(x);
}

long double csch(long double x)
{
	return 1 / sinh(x);
}

long double acoth(long double x)
{
	return 1 / 2 * log((x + 1) / (x - 1));
}

long double asech(long double x)
{
	return log(1 / x + sqrt(1 / (x * x) - 1));
}

long double acsch(long double x) 
{
	return log(1 / x + sqrt(1 / (x * x) + 1));
}

long double sinhDerivative(long double x)
{
	return cosh(x);
}

long double coshDerivative(long double x)
{
	return sinh(x);
}

long double tanhDerivative(long double x) 
{
	long double t = tanh(x);
	return 1 - (t * t);
}

long double cothDerivative(long double x)
{
	long double c = coth(x);
	return 1 - (c * c);
}

long double sechDerivative(long double x)
{
	return -tanh(x) * sech(x);
}

long double cschDerivative(long double x)
{
	return -coth(x) * csch(x);
}

long double asinhDerivative(long double x)
{
	return 1 / sqrt(x * x + 1);
}

long double acoshDerivative(long double x)
{
	return 1 / sqrt(x * x - 1);
}

long double atanhDerivative(long double x)
{
	return 1 / (1 - x * x);
}

long double acothDerivative(long double x)
{
	return 1 / (1 - x * x);
}

long double asechDerivative(long double x)
{
	return 1 /(x * sqrt(1 - x * x));
}

long double acschDerivative(long double x)
{
	return 1 / (abs(x) * sqrt(x * x + 1));
}

/* Activation Functions */

long double* softmax(long double* data, const int count)
{
	long double sum = 0, 
		m = max(data, count),
		*result = new long double[count];
	for (int i = 0; i < count; ++i) {
		*(result + i) = exp(*(data + i) - m);
		sum += *(result + i);
	}
	for (int i = 0; i < count; ++i)
		*(result + i) /= sum;
	return result;
}

Matrix& softmaxDerivative(Matrix& matrix)
{
	if (!matrix.isSquare())
		throw NotSquareMatrixError();
	/* Python:
		s = arr.reshape(-1, 1);
		result = np.diagflat(s) -  np.dot(s, s.T)
	*/
	Matrix* s = &matrix.flatten();
	Matrix* sT = &s->transpose();
	Matrix* left = &Matrix::diagonal(matrix.getData(), matrix.count);
	Matrix* right = &s->times(*sT);
	delete s;
	delete sT;
	Matrix* result = &left->minus(*right);
	delete left;
	return *result;
}

long double sigmoid(long double x)
{
	return x / (1 + abs(x));
}

long double sigmoidDerivative(long double x)
{
	return x * (1 - x);
}

long double relu(long double x)
{
	return x > 0 ? x : 0;
}

long double reluDerivative(long double x)
{
	return x > 0 ? 1 : 0;
}

long double leakyRelu(long double x, long double alpha)
{
	return x > 0 ? x : alpha * x;
}

long double leakyReluDerivative(long double x, long double alpha)
{
	return x > 0 ? 1 : alpha;
}

long double relu6(long double x)
{
	if (x <= 0)
		return 0; 
	else if (x >= 6)
		return 6;
	return x;
}

long double relu6Derivative(long double x)
{
	return (x <= 0 || x >= 6) ? 0 : 1;
}

long double elu(long double x, long double alpha)			
{
	return x > 0 ? x : alpha * (exp(x) - 1);
}

long double eluDerivative(long double x, long double alpha)
{
	return x > 0 ? 1 : elu(x, alpha) + alpha;
}

long double selu(long double x, long double alpha, long double lambda)
{
	return lambda * (x > 0 ? x : (alpha * exp(x) - alpha));
}

long double seluDerivative(long double x, long double alpha, long double lambda)
{
	return lambda * (x > 0 ? 1 : (alpha * exp(x)));
}

long double gelu(long double x)
{
	return 0.5 * x * (1 + tanh(sqrt(2 / 3.14) * (x + 0.044715 * x * x * x)));
}

long double geluDerivative(long double x)
{
	long double s = sech(0.0356774 * x * x * x + 0.797885 * x);
	return 0.5 * tanh(0.0356774 * x * x * x + 0.797885 * x) + (0.0535161 * x * x * x + 0.398942 * x) * (s * s) + 0.5;
}

long double cube(long double x)
{
	return x * x * x;
}

long double cubeDerivative(long double x)
{
	return 3 * x * x;
}

long double swish(long double x)
{
	return x * sigmoid(x);
}

long double swishDerivative(long double x)
{
	long double s = sigmoid(x);
	return 2 * s - s * s;
}

long double softsign(long double x)
{
	return x / (1 + abs(x));
}

long double softsignDerivative(long double x)
{
	long double a = abs(x);
	return (1 + a - x * x / a) / ((1 + a) * (1 + a));
}

long double softplus(long double x)
{
	return log(1 + exp(x));
}

long double softplusDerivative(long double x)
{
	return 1 / (1 + exp(-x));
}
