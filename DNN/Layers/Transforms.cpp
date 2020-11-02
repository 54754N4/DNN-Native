#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include "..\..\Models\Exceptions.h"
#include "..\..\Models\Vector.h"
#include "..\..\Models\Matrix.h"
#include "Transforms.h"

void Transforms::swap(long double& a, long double& b)
{
	long double temp = a;
	a = b;
	b = temp;
}

long double Transforms::max(long double* data, const int count)
{
	long double max = 0;
	for (int i = 0; i < count; ++i)
		if (data[i] > max)
			max = data[i];
	return max;
}

void Transforms::sort(int& a, int& b)
{
	if (a > b) {
		int temp = a;
		a = b;
		b = temp;
	}
}

long double Transforms::identity(long double x)
{
	return x;
}

Matrix& Transforms::identitym(Matrix& x)
{
	return x;
}

long double Transforms::identityDerivative(long double x)
{
	return 1;
}

Matrix& Transforms::identityDerivativem(Matrix& x)
{
	return x.forEach(identityDerivative);
}

long double Transforms::logCosh(long double x)
{
	return log(cosh(x));
}

long double Transforms::coth(long double x)
{
	return cosh(x) / sinh(x);
}

long double Transforms::sech(long double x)
{
	return 1 / cosh(x);
}

long double Transforms::csch(long double x)
{
	return 1 / sinh(x);
}

long double Transforms::acoth(long double x)
{
	return 1 / 2 * log((x + 1) / (x - 1));
}

long double Transforms::asech(long double x)
{
	return log(1 / x + sqrt(1 / (x * x) - 1));
}

long double Transforms::acsch(long double x)
{
	return log(1 / x + sqrt(1 / (x * x) + 1));
}

long double Transforms::sinhDerivative(long double x)
{
	return cosh(x);
}

long double Transforms::coshDerivative(long double x)
{
	return sinh(x);
}

long double Transforms::tanhDerivative(long double x)
{
	long double t = tanh(x);
	return 1 - (t * t);
}

long double Transforms::cothDerivative(long double x)
{
	long double c = coth(x);
	return 1 - (c * c);
}

long double Transforms::sechDerivative(long double x)
{
	return -tanh(x) * sech(x);
}

long double Transforms::cschDerivative(long double x)
{
	return -coth(x) * csch(x);
}

long double Transforms::asinhDerivative(long double x)
{
	return 1 / sqrt(x * x + 1);
}

long double Transforms::acoshDerivative(long double x)
{
	return 1 / sqrt(x * x - 1);
}

long double Transforms::atanhDerivative(long double x)
{
	return 1 / (1 - x * x);
}

long double Transforms::acothDerivative(long double x)
{
	return 1 / (1 - x * x);
}

long double Transforms::asechDerivative(long double x)
{
	return 1 /(x * sqrt(1 - x * x));
}

long double Transforms::acschDerivative(long double x)
{
	return 1 / (abs(x) * sqrt(x * x + 1));
}

/* Activation Functions */

long double* Transforms::softmax(long double* data, const int count)
{
	long double sum = 0, 
		m = max(data, count),
		*result = new long double[count];
	for (int i = 0; i < count; ++i) {
		result[i] = exp(data[i] - m);
		sum += result[i];
	}
	for (int i = 0; i < count; ++i)
		result[i] /= sum;
	return result;
}

Matrix& Transforms::softmaxDerivative(Matrix& matrix)
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

long double Transforms::sigmoid(long double x)
{
	return x / (1 + abs(x));
}

Matrix& Transforms::sigmoidm(Matrix& x)
{
	return x.forEach(sigmoid);
}

long double Transforms::sigmoidDerivative(long double x)
{
	return x * (1 - x);
}

Matrix& Transforms::sigmoidDerivativem(Matrix& x)
{
	return x.forEach(sigmoidDerivative);
}

long double Transforms::relu(long double x)
{
	return x > 0 ? x : 0;
}

Matrix& Transforms::relum(Matrix& x)
{
	return x.forEach(relu);
}

long double Transforms::reluDerivative(long double x)
{
	return x > 0 ? 1 : 0;
}

Matrix& Transforms::reluDerivativem(Matrix& x)
{
	return x.forEach(reluDerivative);
}

long double Transforms::leakyRelu(long double x)
{
	return x > 0 ? x : LEAKY_RELU_ALPHA * x;
}

Matrix& Transforms::leakyRelum(Matrix& x)
{
	return x.forEach(leakyRelu);
}

long double Transforms::leakyReluDerivative(long double x)
{
	return x > 0 ? 1 : LEAKY_RELU_ALPHA;
}

Matrix& Transforms::leakyReluDerivativem(Matrix& x)
{
	return x.forEach(leakyReluDerivative);
}

long double Transforms::relu6(long double x)
{
	if (x <= 0)
		return 0; 
	else if (x >= 6)
		return 6;
	return x;
}

Matrix& Transforms::relu6m(Matrix& x)
{
	return x.forEach(relu6);
}

long double Transforms::relu6Derivative(long double x)
{
	return (x <= 0 || x >= 6) ? 0 : 1;
}

Matrix& Transforms::relu6Derivativem(Matrix& x)
{
	return x.forEach(relu6Derivative);
}

long double Transforms::elu(long double x)
{
	return x > 0 ? x : ELU_ALPHA * (exp(x) - 1);
}

Matrix& Transforms::elum(Matrix& x)
{
	return x.forEach(elu);
}

long double Transforms::eluDerivative(long double x)
{
	return x > 0 ? 1 : elu(x) + ELU_ALPHA;
}

Matrix& Transforms::eluDerivativem(Matrix& x)
{
	return x.forEach(eluDerivative);
}

long double Transforms::selu(long double x)
{
	return SELU_LAMBDA * (x > 0 ? x : (SELU_ALPHA * exp(x) - SELU_ALPHA));
}

Matrix& Transforms::selum(Matrix& x)
{
	return x.forEach(selu);
}

long double Transforms::seluDerivative(long double x)
{
	return SELU_LAMBDA * (x > 0 ? 1 : (SELU_ALPHA * exp(x)));
}

Matrix& Transforms::seluDerivativem(Matrix& x)
{
	return x.forEach(seluDerivative);
}

long double Transforms::gelu(long double x)
{
	return 0.5 * x * (1 + tanh(sqrt(2 / 3.14) * (x + 0.044715 * x * x * x)));
}

Matrix& Transforms::gelum(Matrix& x)
{
	return x.forEach(gelu);
}

long double Transforms::geluDerivative(long double x)
{
	long double val = 0.0356774 * x * x * x + 0.797885 * x, s = sech(val),
		m = (0.0535161 * x * x * x + 0.398942 * x) * (s * s);
	return 0.5 * tanh(val) + m + 0.5;
}

Matrix& Transforms::geluDerivativem(Matrix& x)
{
	return x.forEach(geluDerivative);
}

long double Transforms::cube(long double x)
{
	return x * x * x;
}

Matrix& Transforms::cubem(Matrix& x)
{
	return x.forEach(cube);
}

long double Transforms::cubeDerivative(long double x)
{
	return 3 * x * x;
}

Matrix& Transforms::cubeDerivativem(Matrix& x)
{
	return x.forEach(cubeDerivative);
}

long double Transforms::swish(long double x)
{
	return x * sigmoid(x);
}

Matrix& Transforms::swishm(Matrix& x)
{
	return x.forEach(swish);
}

long double Transforms::swishDerivative(long double x)
{
	long double s = sigmoid(x);
	return s*(2-s);
}

Matrix& Transforms::swishDerivativem(Matrix& x)
{
	return x.forEach(swishDerivative);
}

long double Transforms::softsign(long double x)
{
	return x / (1 + abs(x));
}

Matrix& Transforms::softsignm(Matrix& x)
{
	return x.forEach(softsign);
}

long double Transforms::softsignDerivative(long double x)
{
	long double a = abs(x), app = 1 + a;
	return (app - x * x / a) / (app * app);
}

Matrix& Transforms::softsignDerivativem(Matrix& x)
{
	return x.forEach(softsignDerivative);
}

long double Transforms::softplus(long double x)
{
	return log(1 + exp(x));
}

Matrix& Transforms::softplusm(Matrix& x)
{
	return x.forEach(softplus);
}

long double Transforms::softplusDerivative(long double x)
{
	long double e = exp(x);
	return e / (e + 1);				// 1 / (1 + exp(-x)) <===> exp(x)/(exp(x)+1)
}

Matrix& Transforms::softplusDerivativem(Matrix& x)
{
	return x.forEach(softplusDerivative);
}

Matrix& Transforms::softmax(Matrix& x)
{
	throw new NotYetImplementedError();
}

/* Loss Functions */

long double Transforms::meanSquareLoss(Matrix& y, Matrix& truth)
{
	long double mse;
	Matrix* result = &truth.minus(y);
	result->forEach([](long double v) -> long double { return v * v; }, true);
	mse = result->getSum() / result->count;
	delete result;
	return mse;
}

long double Transforms::meanAbsoluteLoss(Matrix& y, Matrix& truth)
{
	long double mse;
	Matrix* result = &truth.minus(y);
	result->forEach([](long double v) -> long double { return abs(v); }, true);
	mse = result->getSum() / result->count;
	delete result;
	return mse;
}

long double Transforms::smoothMeanAbsoluteLoss(Matrix& y, Matrix& truth)
{
	long double mse;
	const long double t = Transforms::SMAE_DELTA;
	Matrix* result = &truth.minus(y);
	result->forEach([&t](long double v) -> long double {
		long double a = abs(v);
		return (a <= t) ? 
			1 / 2 * v * v :
			t * a - 1 / 2 * t * t;
	}, true);
	mse = result->getSum() / result->count;
	delete result;
	return mse;
}

long double Transforms::logCoshLoss(Matrix& y, Matrix& truth)
{
	Matrix* result = &truth.minus(y);
	long double mse = result->forEach(logCosh, true).getSum() / result->count;
	delete result;
	return mse;
}

long double Transforms::crossEntropyLoss(Matrix& y, Matrix& truth)
{
	return -y.forEach(log2l).hadamardTimes(truth, true).getSum() / y.count;
}
