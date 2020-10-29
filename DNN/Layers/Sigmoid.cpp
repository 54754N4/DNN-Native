#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include "..\..\Models\Exceptions.h"
#include "..\..\Models\Vector.h"
#include "..\..\Models\Matrix.h"
#include "Transforms.h"
#include "Layer.h"
#include "Sigmoid.h"

Sigmoid::Sigmoid(int inputs, int neurons, Matrix& weights, Vector& bias)
	: Layer(inputs, neurons, weights, bias) {}

Sigmoid::~Sigmoid() {}

Matrix& Sigmoid::applyActivation(Matrix& x)
{
	return x.forEach(SIGMOID_CONSUMER);
}

Matrix& Sigmoid::applyActivationDerivative(Matrix& x)
{
	return x.forEach(SIGMOID_DERIVATIVE_CONSUMER);
}
