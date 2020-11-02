/* References :
https://en.wikipedia.org/wiki/Hyperbolic_functions
https://mlfromscratch.com/activation-functions-explained/#/
*/

#ifndef TRANSFORMS_H
#define TRANSFORMS_H

namespace Transforms
{
	const long double LEAKY_RELU_ALPHA = 0.3,
		ELU_ALPHA = 0.3,								// alpha usually belongs to [0.1, 0.3]
		SELU_ALPHA = 1.6732632423543772848170429916717,
		SELU_LAMBDA = 1.0507009873554804934193349852946,
		SMAE_DELTA = 2;									// huber loss delta

	/* Utility + Trigonometry */
	long double max(long double* data, const int count);
	void sort(int& a, int& b);
	void swap(long double& a, long double& b);
	long double logCosh(long double x);
	long double coth(long double x);
	long double sech(long double x);
	long double csch(long double x);
	long double acoth(long double x);
	long double asech(long double x);
	long double acsch(long double x);
	long double sinhDerivative(long double x);
	long double coshDerivative(long double x);
	long double tanhDerivative(long double x);
	long double cothDerivative(long double x);
	long double sechDerivative(long double x);
	long double cschDerivative(long double x);
	long double asinhDerivative(long double x);
	long double acoshDerivative(long double x);
	long double atanhDerivative(long double x);
	long double acothDerivative(long double x);
	long double asechDerivative(long double x);
	long double acschDerivative(long double x);
	
	/*
		Activations
	*/
	
	/* NOP */
	long double identity(long double x);
	Matrix& identitym(Matrix& x);
	long double identityDerivative(long double x);
	Matrix& identityDerivativem(Matrix& x);
	/* Sigmoid */
	long double sigmoid(long double x);
	Matrix& sigmoidm(Matrix& x);
	long double sigmoidDerivative(long double x);
	Matrix& sigmoidDerivativem(Matrix& x);
	/* ReLU */
	long double relu(long double x);
	Matrix& relum(Matrix& x);
	long double reluDerivative(long double x);
	Matrix& reluDerivativem(Matrix& x);
	/* LeakyReLU */
	long double leakyRelu(long double x);
	Matrix& leakyRelum(Matrix& x);
	long double leakyReluDerivative(long double x);
	Matrix& leakyReluDerivativem(Matrix& x);
	/* Relu6 */
	long double relu6(long double x);
	Matrix& relu6m(Matrix& x);
	long double relu6Derivative(long double x);
	Matrix& relu6Derivativem(Matrix& x);
	/* ELU */
	long double elu(long double x);
	Matrix& elum(Matrix& x);
	long double eluDerivative(long double x);
	Matrix& eluDerivativem(Matrix& x);
	/* Scaled ELU */
	long double selu(long double x);
	Matrix& selum(Matrix& x);
	long double seluDerivative(long double x);
	Matrix& seluDerivativem(Matrix& x);
	/* Gaussian ELU */
	long double gelu(long double x);
	Matrix& gelum(Matrix& x);
	long double geluDerivative(long double x);
	Matrix& geluDerivativem(Matrix& x);
	/* Cube */
	long double cube(long double x);
	Matrix& cubem(Matrix& x);
	long double cubeDerivative(long double x);
	Matrix& cubeDerivativem(Matrix& x);
	/* Swish */
	long double swish(long double x);
	Matrix& swishm(Matrix& x);
	long double swishDerivative(long double x);
	Matrix& swishDerivativem(Matrix& x);
	/* Softsign */
	long double softsign(long double x);
	Matrix& softsignm(Matrix& x);
	long double softsignDerivative(long double x);
	Matrix& softsignDerivativem(Matrix& x);
	/* Softplus */
	long double softplus(long double x);
	Matrix& softplusm(Matrix& x);
	long double softplusDerivative(long double x);
	Matrix& softplusDerivativem(Matrix& x);
	/* Softmax*/
	long double* softmax(long double* data, const int count);
	Matrix& softmax(Matrix& x);
	Matrix& softmaxDerivative(Matrix& matrix);

	/* 
		Loss Functions
	*/

	long double meanSquareLoss(Matrix& y, Matrix& truth);		// l2 loss
	long double meanAbsoluteLoss(Matrix& y, Matrix& truth);		// l1 loss
	long double smoothMeanAbsoluteLoss(Matrix& y, Matrix& truth);	// huber loss
	long double logCoshLoss(Matrix& y, Matrix& truth);
	long double crossEntropyLoss(Matrix& y, Matrix& truth);
	/*long double kullbackLeiblerLoss(Matrix& y, Matrix& truth);*/
};
#endif