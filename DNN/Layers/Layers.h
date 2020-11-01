#ifndef LAYER_H
#define LAYER_H

using ActivationFunction = Matrix& (*)(Matrix&);

/* Interface */
template<ActivationFunction Forward, ActivationFunction Backward>
class Layer
{
protected:
	Matrix* previousActivation{ nullptr }, * error{ nullptr }, * delta{ nullptr };
	Matrix& weights;
	Vector& bias;
public:
	const int inputs, neurons;

	Layer(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Layer();

	Matrix& activate(Matrix& x);
	Matrix& applyActivation(Matrix& x) { return Forward(x); };
	Matrix& applyActivationDerivative(Matrix& x) { return Backward(x); };
};

namespace Layers
{
	struct NOP : public Layer<Transforms::identitym, Transforms::identityDerivativem>
	{
		NOP(int inputs, int neurons, Matrix& weights, Vector& bias) 
			: Layer(inputs, neurons, weights, bias) {}
	};
	struct Sigmoid : public Layer<Transforms::sigmoidm, Transforms::sigmoidDerivativem>
	{
		Sigmoid(int inputs, int neurons, Matrix& weights, Vector & bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
	struct Relu : public Layer<Transforms::relum, Transforms::reluDerivativem>
	{
		Relu(int inputs, int neurons, Matrix& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
	struct LeakyRelu : public Layer<Transforms::leakyRelum, Transforms::leakyReluDerivativem>
	{
		LeakyRelu(int inputs, int neurons, Matrix& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
	struct Relu6 : public Layer<Transforms::relu6m, Transforms::relu6Derivativem>
	{
		Relu6(int inputs, int neurons, Matrix& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
	struct Elu : public Layer<Transforms::elum, Transforms::eluDerivativem>
	{
		Elu(int inputs, int neurons, Matrix& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
	struct Selu : public Layer<Transforms::selum, Transforms::seluDerivativem>
	{
		Selu(int inputs, int neurons, Matrix& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
	struct Gelu : public Layer<Transforms::gelum, Transforms::geluDerivativem>
	{
		Gelu(int inputs, int neurons, Matrix& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
	struct Cube : public Layer<Transforms::cubem, Transforms::cubeDerivativem>
	{
		Cube(int inputs, int neurons, Matrix& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
	struct Swish : public Layer<Transforms::swishm, Transforms::swishDerivativem>
	{
		Swish(int inputs, int neurons, Matrix& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
	struct Softsign : public Layer<Transforms::softsignm, Transforms::softsignDerivativem>
	{
		Softsign(int inputs, int neurons, Matrix& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
	struct Softplus : public Layer<Transforms::softplusm, Transforms::softplusDerivativem>
	{
		Softplus(int inputs, int neurons, Matrix& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
	struct Softmax : public Layer<Transforms::softmax, Transforms::softmaxDerivative>
	{
		Softmax(int inputs, int neurons, Matrix& weights, Vector& bias)
			: Layer(inputs, neurons, weights, bias) {}
	};
};
#include "Layers.tpp"

#endif // !LAYER_H