#ifndef RELU_H
#define RELU_H

class Relu : public Layer
{
public:
	Relu(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Relu();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

#endif  //!RELU_H