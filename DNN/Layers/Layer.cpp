#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include "..\..\Models\Exceptions.h"
#include "..\..\Models\Vector.h"
#include "..\..\Models\Matrix.h"
#include "Layer.h"

Layer::Layer(int inputs, int neurons, Matrix& weights, Vector& bias) 
	: inputs(inputs), neurons(neurons), weights(weights), bias(bias),
	previousActivation(nullptr), error(nullptr), delta(nullptr) {}

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