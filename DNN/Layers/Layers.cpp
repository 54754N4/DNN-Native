#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include "..\..\Models\Exceptions.h"
#include "..\..\Models\Vector.h"
#include "..\..\Models\Matrix.h"
#include "Transforms.h"
#include "Layers.h"

Layer::Layer(int inputs, int neurons, Matrix& weights, Vector& bias) 
	: inputs(inputs), neurons(neurons), weights(weights), bias(bias) {}

Layer::~Layer()
{
	delete previousActivation;
	delete error;
	delete delta;
}

/**
  * Calculates the dot product of this layer : X . W + B
  * Also saves the result for use in backprop later.
  * @param x The input.
  * @return The result.
  */
Matrix& Layer::activate(Matrix& x) 
{
	Matrix* temp1 = &x.times(weights), 
		* temp2 = &temp1->plusRow(bias);
	delete temp1;
	previousActivation = &applyActivation(*temp2);
	delete temp2;
	return *previousActivation;
}

/* NOP (e.g. Linear layer) */
NOP::NOP(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

NOP::~NOP() {}

Matrix& NOP::applyActivation(Matrix& x)
{
	return x;
}

Matrix& NOP::applyActivationDerivative(Matrix& x)
{
	return x.forEach(Transforms::identityDerivative);
}

/* Sigmoid */

Sigmoid::Sigmoid(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

Sigmoid::~Sigmoid() {}

Matrix& Sigmoid::applyActivation(Matrix& x)
{
	return x.forEach(Transforms::sigmoid);
}

Matrix& Sigmoid::applyActivationDerivative(Matrix& x)
{
	return x.forEach(Transforms::sigmoidDerivative);
}

/* ReLU */

Relu::Relu(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

Relu::~Relu() {}

Matrix& Relu::applyActivation(Matrix& x)
{
	return x.forEach(Transforms::relu);
}

Matrix& Relu::applyActivationDerivative(Matrix& x)
{
	return x.forEach(Transforms::reluDerivative);
}

/* LeakyReLU */

LeakyRelu::LeakyRelu(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

LeakyRelu::~LeakyRelu() {}

Matrix& LeakyRelu::applyActivation(Matrix& x)
{
	return x.forEach(Transforms::leakyRelu);
}

Matrix& LeakyRelu::applyActivationDerivative(Matrix& x)
{
	return x.forEach(Transforms::leakyReluDerivative);
}

/* ReLU6 */

Relu6::Relu6(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

Relu6::~Relu6() {}

Matrix& Relu6::applyActivation(Matrix& x)
{
	return x.forEach(Transforms::relu6);
}

Matrix& Relu6::applyActivationDerivative(Matrix& x)
{
	return x.forEach(Transforms::relu6Derivative);
}

/* ELU */

Elu::Elu(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

Elu::~Elu() {}

Matrix& Elu::applyActivation(Matrix& x)
{
	return x.forEach(Transforms::elu);
}

Matrix& Elu::applyActivationDerivative(Matrix& x)
{
	return x.forEach(Transforms::eluDerivative);
}

/* SELU */

Selu::Selu(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

Selu::~Selu() {}

Matrix& Selu::applyActivation(Matrix& x)
{
	return x.forEach(Transforms::selu);
}

Matrix& Selu::applyActivationDerivative(Matrix& x)
{
	return x.forEach(Transforms::seluDerivative);
}

/* GELU */

Gelu::Gelu(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

Gelu::~Gelu() {}

Matrix& Gelu::applyActivation(Matrix& x)
{
	return x.forEach(Transforms::gelu);
}

Matrix& Gelu::applyActivationDerivative(Matrix& x)
{
	return x.forEach(Transforms::geluDerivative);
}

/* Cube */

Cube::Cube(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

Cube::~Cube() {}

Matrix& Cube::applyActivation(Matrix& x)
{
	return x.forEach(Transforms::cube);
}

Matrix& Cube::applyActivationDerivative(Matrix& x)
{
	return x.forEach(Transforms::cubeDerivative);
}

/* Swish */

Swish::Swish(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

Swish::~Swish() {}

Matrix& Swish::applyActivation(Matrix& x)
{
	return x.forEach(Transforms::swish);
}

Matrix& Swish::applyActivationDerivative(Matrix& x)
{
	return x.forEach(Transforms::swishDerivative);
}

/* Softsign */

Softsign::Softsign(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

Softsign::~Softsign() {}

Matrix& Softsign::applyActivation(Matrix& x)
{
	return x.forEach(Transforms::softsign);
}

Matrix& Softsign::applyActivationDerivative(Matrix& x)
{
	return x.forEach(Transforms::softsignDerivative);
}

/* Softplus */

Softplus::Softplus(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

Softplus::~Softplus() {}

Matrix& Softplus::applyActivation(Matrix& x)
{
	return x.forEach(Transforms::softplus);
}

Matrix& Softplus::applyActivationDerivative(Matrix& x)
{
	return x.forEach(Transforms::softplusDerivative);
}

/* Softmax */

Softmax::Softmax(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

Softmax::~Softmax() {}

Matrix& Softmax::applyActivation(Matrix& x)
{
	return x.forEach(Transforms::identity);			// <======== FIX WHEN YOU KNOW HOW
}

Matrix& Softmax::applyActivationDerivative(Matrix& x)
{
	return Transforms::softmaxDerivative(x);
}
