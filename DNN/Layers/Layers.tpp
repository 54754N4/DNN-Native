#ifndef LAYERS_TPP
#define LAYERS_TPP

#ifndef LAYERS_H
#error __FILE__ should only be included from Layers.h
#endif 


template<class I, ActivationFunction<I> F, ActivationFunction<I> B>
Layer<I, F, B>::Layer(int inputs, int neurons, I& weights, Vector& bias)
	: inputs(inputs), neurons(neurons), weights(weights), bias(bias) {}

template<class I, ActivationFunction<I> F, ActivationFunction<I> B>
Layer<I, F, B>::~Layer()
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
template<class I, ActivationFunction<I> F, ActivationFunction<I> B>
I& Layer<I, F, B>::activate(I& x)
{
	I* a = &x.times(weights).plusRow(bias, true);
	previousActivation = &applyActivation(*a);
	delete a;
	return *previousActivation;
}

//template<class I, ActivationFunction<I> Forward, ActivationFunction<I> Backward>
//Layer<I, Forward, Backward>::Layer(int inputs, int neurons, I& weights, Vector& bias)
//	: inputs(inputs), neurons(neurons), weights(weights), bias(bias) {}
//
//template<class I, ActivationFunction<I> Forward, ActivationFunction<I> Backward>
//Layer<I, Forward, Backward>::~Layer()
//{
//	delete previousActivation;
//	delete error;
//	delete delta;
//}
//
///**
//  * Calculates the dot product of this layer : X . W + B
//  * Also saves the result for use in backprop later.
//  * @param x The input.
//  * @return The result.
//  */
//template<class I, ActivationFunction<I> Forward, ActivationFunction<I> Backward>
//I& Layer<I, Forward, Backward>::activate(I& x)
//{
//	IMatrix<I>* a = &x.times(weights).plusRow(bias, true);
//	previousActivation = &applyActivation(*a);
//	delete a;
//	return *previousActivation;
//}

#endif