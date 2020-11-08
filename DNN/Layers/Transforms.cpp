#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include "..\..\Models\Exceptions.h"
#include "..\..\Models\Vector\IVector.h"
#include "..\..\Models\Matrix\IMatrix.h"
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

long double Transforms::identity(long double x)
{
	return x;
}

template<class T>
IMatrix<T>& Transforms::identitym(IMatrix<T>& x)
{
	return x;
}

long double Transforms::identityDerivative(long double x)
{
	return 1;
}

template<class T>
IMatrix<T>& Transforms::identityDerivativem(IMatrix<T>& x)
{
	return x.forEach(identityDerivative);
}

//long double Transforms::sigmoid(long double x)
//{
//	return x / (1 + abs(x));
//}
//
//template<class T>
//IMatrix<T>& Transforms::sigmoidm(IMatrix<T>& x)
//{
//	return x.forEach(sigmoid);
//}
//
//long double Transforms::sigmoidDerivative(long double x)
//{
//	return x * (1 - x);
//}
//
//template<class T>
//IMatrix<T>& Transforms::sigmoidDerivativem(IMatrix<T>& x)
//{
//	return x.forEach(sigmoidDerivative);
//}
//
//long double Transforms::relu(long double x)
//{
//	return x > 0 ? x : 0;
//}
//
//template<class T>
//IMatrix<T>& Transforms::relum(IMatrix<T>& x)
//{
//	return x.forEach(relu);
//}
//
//long double Transforms::reluDerivative(long double x)
//{
//	return x > 0 ? 1 : 0;
//}
//
//template<class T>
//IMatrix<T>& Transforms::reluDerivativem(IMatrix<T>& x)
//{
//	return x.forEach(reluDerivative);
//}
//
//long double Transforms::leakyRelu(long double x)
//{
//	return x > 0 ? x : LEAKY_RELU_ALPHA * x;
//}
//
//template<class T>
//IMatrix<T>& Transforms::leakyRelum(IMatrix<T>& x)
//{
//	return x.forEach(leakyRelu);
//}
//
//long double Transforms::leakyReluDerivative(long double x)
//{
//	return x > 0 ? 1 : LEAKY_RELU_ALPHA;
//}
//
//template<class T>
//IMatrix<T>& Transforms::leakyReluDerivativem(IMatrix<T>& x)
//{
//	return x.forEach(leakyReluDerivative);
//}
//
//long double Transforms::relu6(long double x)
//{
//	if (x <= 0)
//		return 0; 
//	else if (x >= 6)
//		return 6;
//	return x;
//}
//
//template<class T>
//IMatrix<T>& Transforms::relu6m(IMatrix<T>& x)
//{
//	return x.forEach(relu6);
//}
//
//long double Transforms::relu6Derivative(long double x)
//{
//	return (x <= 0 || x >= 6) ? 0 : 1;
//}
//
//template<class T>
//IMatrix<T>& Transforms::relu6Derivativem(IMatrix<T>& x)
//{
//	return x.forEach(relu6Derivative);
//}
//
//long double Transforms::elu(long double x)
//{
//	return x > 0 ? x : ELU_ALPHA * (exp(x) - 1);
//}
//
//template<class T>
//IMatrix<T>& Transforms::elum(IMatrix<T>& x)
//{
//	return x.forEach(elu);
//}
//
//long double Transforms::eluDerivative(long double x)
//{
//	return x > 0 ? 1 : elu(x) + ELU_ALPHA;
//}
//
//template<class T>
//IMatrix<T>& Transforms::eluDerivativem(IMatrix<T>& x)
//{
//	return x.forEach(eluDerivative);
//}
//
//long double Transforms::selu(long double x)
//{
//	return SELU_LAMBDA * (x > 0 ? x : (SELU_ALPHA * exp(x) - SELU_ALPHA));
//}
//
//template<class T>
//IMatrix<T>& Transforms::selum(IMatrix<T>& x)
//{
//	return x.forEach(selu);
//}
//
//long double Transforms::seluDerivative(long double x)
//{
//	return SELU_LAMBDA * (x > 0 ? 1 : (SELU_ALPHA * exp(x)));
//}
//
//template<class T>
//IMatrix<T>& Transforms::seluDerivativem(IMatrix<T>& x)
//{
//	return x.forEach(seluDerivative);
//}
//
//long double Transforms::gelu(long double x)
//{
//	return 0.5 * x * (1 + tanh(sqrt(2 / 3.14) * (x + 0.044715 * x * x * x)));
//}
//
//template<class T>
//IMatrix<T>& Transforms::gelum(IMatrix<T>& x)
//{
//	return x.forEach(gelu);
//}
//
//long double Transforms::geluDerivative(long double x)
//{
//	long double val = 0.0356774 * x * x * x + 0.797885 * x, s = sech(val),
//		m = (0.0535161 * x * x * x + 0.398942 * x) * (s * s);
//	return 0.5 * tanh(val) + m + 0.5;
//}
//
//template<class T>
//IMatrix<T>& Transforms::geluDerivativem(IMatrix<T>& x)
//{
//	return x.forEach(geluDerivative);
//}
//
//long double Transforms::cube(long double x)
//{
//	return x * x * x;
//}
//
//template<class T>
//IMatrix<T>& Transforms::cubem(IMatrix<T>& x)
//{
//	return x.forEach(cube);
//}
//
//long double Transforms::cubeDerivative(long double x)
//{
//	return 3 * x * x;
//}
//
//template<class T>
//IMatrix<T>& Transforms::cubeDerivativem(IMatrix<T>& x)
//{
//	return x.forEach(cubeDerivative);
//}
//
//long double Transforms::swish(long double x)
//{
//	return x * sigmoid(x);
//}
//
//template<class T>
//IMatrix<T>& Transforms::swishm(IMatrix<T>& x)
//{
//	return x.forEach(swish);
//}
//
//long double Transforms::swishDerivative(long double x)
//{
//	long double s = sigmoid(x);
//	return s*(2-s);
//}
//
//template<class T>
//IMatrix<T>& Transforms::swishDerivativem(IMatrix<T>& x)
//{
//	return x.forEach(swishDerivative);
//}
//
//long double Transforms::softsign(long double x)
//{
//	return x / (1 + abs(x));
//}
//
//template<class T>
//IMatrix<T>& Transforms::softsignm(IMatrix<T>& x)
//{
//	return x.forEach(softsign);
//}
//
//long double Transforms::softsignDerivative(long double x)
//{
//	long double a = abs(x), app = 1 + a;
//	return (app - x * x / a) / (app * app);
//}
//
//template<class T>
//IMatrix<T>& Transforms::softsignDerivativem(IMatrix<T>& x)
//{
//	return x.forEach(softsignDerivative);
//}
//
//long double Transforms::softplus(long double x)
//{
//	return log(1 + exp(x));
//}
//
//template<class T>
//IMatrix<T>& Transforms::softplusm(IMatrix<T>& x)
//{
//	return x.forEach(softplus);
//}
//
//long double Transforms::softplusDerivative(long double x)
//{
//	long double e = exp(x);
//	return e / (e + 1);				// 1 / (1 + exp(-x)) <===> exp(x)/(exp(x)+1)
//}
//
//template<class T>
//IMatrix<T>& Transforms::softplusDerivativem(IMatrix<T>& x)
//{
//	return x.forEach(softplusDerivative);
//}
//
//long double* Transforms::softmax(long double* data, const int count)
//{
//	long double sum = 0,
//		m = max(data, count),
//		* result = new long double[count];
//	for (int i = 0; i < count; ++i) {
//		result[i] = exp(data[i] - m);
//		sum += result[i];
//	}
//	for (int i = 0; i < count; ++i)
//		result[i] /= sum;
//	return result;
//}
//
//template<class T>
//IMatrix<T>& Transforms::softmax(IMatrix<T>& x)
//{
//	throw new NotYetImplementedError();
//}
//
///* Python:
//		s = arr.reshape(-1, 1);
//		result = np.diagflat(s) -  np.dot(s, s.T)
//*/
//template<class T>
//IMatrix<T>& Transforms::softmaxDerivative(IMatrix<T>& matrix)
//{
//	if (!matrix.isSquare())
//		throw NotSquareMatrixError();
//	IMatrix<T>* s = matrix.flatten(),
//		* sT = s->transpose(),
//		* left = T::diagonal(matrix.getData(), matrix.getCount());
//	IMatrix<T>* right = std::move(s->times(*sT));
//	delete s;
//	delete sT;
//	IMatrix<T>* result = &left->minus(*right);
//	delete left;
//	return *result;
//}

/* Loss Functions */

template<class T>
long double Transforms::meanSquareLoss(IMatrix<T>& y, IMatrix<T>& truth)
{
	long double mse;
	IMatrix<T>* result = &truth.minus(y);
	result->forEach([](long double v) -> long double { return v * v; }, true);
	mse = result->getSum() / result->getCount();
	delete result;
	return mse;
}

template<class T>
long double Transforms::meanAbsoluteLoss(IMatrix<T>& y, IMatrix<T>& truth)
{
	long double mse;
	IMatrix<T>* result = &truth.minus(y);
	result->forEach([](long double v) -> long double { return abs(v); }, true);
	mse = result->getSum() / result->getCount();
	delete result;
	return mse;
}

template<class T>
long double Transforms::smoothMeanAbsoluteLoss(IMatrix<T>& y, IMatrix<T>& truth)
{
	long double mse;
	const long double t = Transforms::SMAE_DELTA;
	IMatrix<T>* result = &truth.minus(y);
	result->forEach([&t](long double v) -> long double {
		long double a = abs(v);
		return (a <= t) ? 
			1 / 2 * v * v :
			t * a - 1 / 2 * t * t;
	}, true);
	mse = result->getSum() / result->getCount();
	delete result;
	return mse;
}

template<class T>
long double Transforms::logCoshLoss(IMatrix<T>& y, IMatrix<T>& truth)
{
	IMatrix<T>* result = &truth.minus(y);
	long double mse = result->forEach(logCosh, true).getSum() / result->getCount();
	delete result;
	return mse;
}

template<class T>
long double Transforms::crossEntropyLoss(IMatrix<T>& y, IMatrix<T>& truth)
{
	return -y.forEach(log2l).hadamardTimes(truth, true).getSum() / y.getCount();
}
