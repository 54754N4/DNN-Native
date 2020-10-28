#ifndef INITIALISER_H
#define INITIALISER_H
#endif // !INITIALISER_H
class Initialiser
{
	const int inputs, outputs;
	const bool uniform;

public:
	Initialiser(int inputs, int outputs, bool uniform);
	virtual long double getScaling() = 0;

	Matrix* createWeights();
	Matrix* createBiases();
	static Matrix* create(int inputs, int outputs, bool uniform);
};

//#endif // !INITIALISER_H