#ifndef INITIALISER_TPP
#define INITIALISER_TPP

#ifndef INITIALISER_H
#error __FILE__ should only be included from Initialiser.h
#endif

template<class I>
Initialiser<I>::Initialiser(int inputs, int outputs, bool uniform)
	: inputs(inputs), outputs(outputs), uniform(uniform) {}


template<class I>
IMatrix<I>* Initialiser<I>::createWeights()
{
	return create(inputs, outputs, uniform);
}

template<class I>
IMatrix<I>* Initialiser<I>::createBiases()
{
	return create(inputs, 1, uniform);
}

template<class I>
IMatrix<I>* Initialiser<I>::create(int inputs, int outputs, bool uniform)
{
	return new IMatrix<I>(inputs, outputs);		// zeros for now
}

#endif
