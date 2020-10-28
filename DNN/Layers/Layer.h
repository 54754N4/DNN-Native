#ifndef LAYER_H
#define LAYER_H

class Layer
{
public:
	const int inputs;
	const int neurons;
	Layer(int inputs, int neurons, Matrix* weights, Vector* bias);
	virtual ~Layer() = 0;

	Matrix* activate(Matrix* x);

	virtual Matrix* applyActivation(Matrix* matrix) = 0;
	virtual Matrix* applyActivationDerivative(Matrix* matrix) = 0;
protected:
	Matrix* weights, * previousActivation, * error, * delta;
	Vector* bias;
};

#endif // !LAYER_H