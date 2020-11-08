#ifndef LAYERS_H
#define LAYERS_H

template<class I>
using ActivationFunction = I& (*)(I&);

template<class I, ActivationFunction<I> F, ActivationFunction<I> B>
class Layer
{
protected:
	I& weights, * previousActivation{ nullptr }, * error{ nullptr }, * delta{ nullptr };
	Vector& bias;
public:
	const int inputs, neurons;

	Layer(int inputs, int neurons, I& weights, Vector& bias);
	~Layer();

	I& activate(I& x);
	I& applyActivation(I& x) { return F(x); };
	I& applyActivationDerivative(I& x) { return B(x); };
};

namespace Layers
{
	template<class I>
	struct NOP : public Layer<I, Transforms::identitym, Transforms::identityDerivativem>
	{
		NOP(int inputs, int neurons, I& weights, Vector& bias) 
			: Layer(inputs, neurons, weights, bias) {}
	};

	/*
	template<class I>
	struct Sigmoid : public Layer<I, Transforms::sigmoidm, Transforms::sigmoidDerivativem>
	{
		Sigmoid(int inputs, int neurons, IMatrix<I>& weights, Vector & bias)
			: Layer(inputs, neurons, weights, bias) {}
	};

	
	template<class I>
	struct Relu : public Layer<I, Transforms::relum, Transforms::reluDerivativem>
	{
		Relu(int inputs, int neurons, IMatrix<I>& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};

	template<class I>
	struct LeakyRelu : public Layer<I, Transforms::leakyRelum, Transforms::leakyReluDerivativem>
	{
		LeakyRelu(int inputs, int neurons, IMatrix<I>& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
	
	template<class I>
	struct Relu6 : public Layer<I, Transforms::relu6m, Transforms::relu6Derivativem>
	{
		Relu6(int inputs, int neurons, IMatrix<I>& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};

	template<class I>
	struct Elu : public Layer<I, Transforms::elum, Transforms::eluDerivativem>
	{
		Elu(int inputs, int neurons, IMatrix<I>& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};

	template<class I>
	struct Selu : public Layer<I, Transforms::selum, Transforms::seluDerivativem>
	{
		Selu(int inputs, int neurons, IMatrix<I>& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};

	template<class I>
	struct Gelu : public Layer<I, Transforms::gelum, Transforms::geluDerivativem>
	{
		Gelu(int inputs, int neurons, IMatrix<I>& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};

	template<class I>
	struct Cube : public Layer<I, Transforms::cubem, Transforms::cubeDerivativem>
	{
		Cube(int inputs, int neurons, IMatrix<I>& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};

	template<class I>
	struct Swish : public Layer<I, Transforms::swishm, Transforms::swishDerivativem>
	{
		Swish(int inputs, int neurons, IMatrix<I>& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};

	template<class I>
	struct Softsign : public Layer<I, Transforms::softsignm, Transforms::softsignDerivativem>
	{
		Softsign(int inputs, int neurons, IMatrix<I>& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};

	template<class I>
	struct Softplus : public Layer<I, Transforms::softplusm, Transforms::softplusDerivativem>
	{
		Softplus(int inputs, int neurons, IMatrix<I>& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};

	template<class I>
	struct Softmax : public Layer<I, Transforms::softmax, Transforms::softmaxDerivative>
	{
		Softmax(int inputs, int neurons, IMatrix<I>& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};*/

};
#include "Layers.tpp"

#endif // !LAYERS_H