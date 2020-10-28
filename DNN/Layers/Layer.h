#ifdef LAYER_H
#define LAYER_H

class Layer
{
	const int inputs, neurons;
	Matrix *weights, *previousActivation, *error, *delta;
	Vector *bias;

public:
	Layer(int inputs, int neurons, Matrix* weights, Vector* bias);
	virtual ~Layer() = 0;

	Matrix* activate(Matrix* x);

	virtual Matrix* applyActivation(Matrix* matrix) = 0;
	virtual Matrix* applyActivationDerivative(Matrix* matrix) = 0;
};

#endif // !LAYER_H