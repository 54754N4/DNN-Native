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
	template<class T> IMatrix <T>& identitym(IMatrix<T>& x);
	long double identityDerivative(long double x);
	template<class T> IMatrix<T>& identityDerivativem(IMatrix<T>& x);
	///* Sigmoid */
	//long double sigmoid(long double x);
	//template<class T> IMatrix<T>& sigmoidm(IMatrix<T>& x);
	//long double sigmoidDerivative(long double x);
	//template<class T> IMatrix<T>& sigmoidDerivativem(IMatrix<T>& x);
	///* ReLU */
	//long double relu(long double x);
	//template<class T> IMatrix<T>& relum(IMatrix<T>& x);
	//long double reluDerivative(long double x);
	//template<class T> IMatrix<T>& reluDerivativem(IMatrix<T>& x);
	///* LeakyReLU */
	//long double leakyRelu(long double x);
	//template<class T> IMatrix<T>& leakyRelum(IMatrix<T>& x);
	//long double leakyReluDerivative(long double x);
	//template<class T> IMatrix<T>& leakyReluDerivativem(IMatrix<T>& x);
	///* Relu6 */
	//long double relu6(long double x);
	//template<class T> IMatrix<T>& relu6m(IMatrix<T>& x);
	//long double relu6Derivative(long double x);
	//template<class T> IMatrix<T>& relu6Derivativem(IMatrix<T>& x);
	///* ELU */
	//long double elu(long double x);
	//template<class T> IMatrix<T>& elum(IMatrix<T>& x);
	//long double eluDerivative(long double x);
	//template<class T> IMatrix<T>& eluDerivativem(IMatrix<T>& x);
	///* Scaled ELU */
	//long double selu(long double x);
	//template<class T> IMatrix<T>& selum(IMatrix<T>& x);
	//long double seluDerivative(long double x);
	//template<class T> IMatrix<T>& seluDerivativem(IMatrix<T>& x);
	///* Gaussian ELU */
	//long double gelu(long double x);
	//template<class T> IMatrix<T>& gelum(IMatrix<T>& x);
	//long double geluDerivative(long double x);
	//template<class T> IMatrix<T>& geluDerivativem(IMatrix<T>& x);
	///* Cube */
	//long double cube(long double x);
	//template<class T> IMatrix<T>& cubem(IMatrix<T>& x);
	//long double cubeDerivative(long double x);
	//template<class T> IMatrix<T>& cubeDerivativem(IMatrix<T>& x);
	///* Swish */
	//long double swish(long double x);
	//template<class T> IMatrix<T>& swishm(IMatrix<T>& x);
	//long double swishDerivative(long double x);
	//template<class T> IMatrix<T>& swishDerivativem(IMatrix<T>& x);
	///* Softsign */
	//long double softsign(long double x);
	//template<class T> IMatrix<T>& softsignm(IMatrix<T>& x);
	//long double softsignDerivative(long double x);
	//template<class T> IMatrix<T>& softsignDerivativem(IMatrix<T>& x);
	///* Softplus */
	//long double softplus(long double x);
	//template<class T> IMatrix<T>& softplusm(IMatrix<T>& x);
	//long double softplusDerivative(long double x);
	//template<class T> IMatrix<T>& softplusDerivativem(IMatrix<T>& x);
	///* Softmax*/
	//long double* softmax(long double* data, const int count);
	//template<class T> IMatrix<T>& softmax(IMatrix<T>& x);
	//template<class T> IMatrix<T>& softmaxDerivative(IMatrix<T>& matrix);

	/* 
		Loss Functions
	*/
	template<class T> long double meanSquareLoss(IMatrix<T>& y, IMatrix<T>& truth);		// l2 loss
	template<class T> long double meanAbsoluteLoss(IMatrix<T>& y, IMatrix<T>& truth);		// l1 loss
	template<class T> long double smoothMeanAbsoluteLoss(IMatrix<T>& y, IMatrix<T>& truth);	// huber loss
	template<class T> long double logCoshLoss(IMatrix<T>& y, IMatrix<T>& truth);
	template<class T> long double crossEntropyLoss(IMatrix<T>& y, IMatrix<T>& truth);
	/*template<class T> long double kullbackLeiblerLoss(IMatrix<T>& y, IMatrix<T>& truth);*/
};
#endif