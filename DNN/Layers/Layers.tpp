#ifndef LAYERS_TPP
#define LAYERS_TPP

#ifndef LAYERS_TPP
#error __FILE__ should only be included from Layers.h
#endif 

template<ActivationFunction Forward, ActivationFunction Backward>
Layer<Forward, Backward>::Layer(int inputs, int neurons, Matrix& weights, Vector& bias)
	: inputs(inputs), neurons(neurons), weights(weights), bias(bias) {}

template<ActivationFunction Forward, ActivationFunction Backward>
Layer<Forward, Backward>::~Layer()
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
template<ActivationFunction Forward, ActivationFunction Backward>
Matrix& Layer<Forward, Backward>::activate(Matrix& x)
{
	Matrix* temp1 = &x.times(weights),
		* temp2 = &temp1->plusRow(bias);
	delete temp1;
	previousActivation = &applyActivation(*temp2);
	delete temp2;
	return *previousActivation;
}

#endif