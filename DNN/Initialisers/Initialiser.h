#ifndef INITIALISER_H
#define INITIALISER_H

template<class I>
class Initialiser
{
	const int inputs, outputs;
	const bool uniform;

public:
	Initialiser(int inputs, int outputs, bool uniform);
	virtual long double getScaling() = 0;

	IMatrix<I>* createWeights();
	IMatrix<I>* createBiases();
	static IMatrix<I>* create(int inputs, int outputs, bool uniform);
};

#include "Initialiser.tpp"

#endif // !INITIALISER_H