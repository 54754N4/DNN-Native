#ifndef SIGMOID_H
#define SIGMOID_H

class Sigmoid : public Layer
{
public:
	Sigmoid(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Sigmoid();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

#endif
