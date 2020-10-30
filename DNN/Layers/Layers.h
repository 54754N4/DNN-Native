#ifndef LAYER_H
#define LAYER_H

/* Interface */
class Layer
{
protected:
	Matrix* previousActivation{ nullptr }, * error{ nullptr }, * delta{ nullptr };
	Matrix& weights;
	Vector& bias;
public:
	const int inputs, neurons;

	Layer(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Layer();

	Matrix& activate(Matrix& x);

	virtual Matrix& applyActivation(Matrix& x) = 0;
	virtual Matrix& applyActivationDerivative(Matrix& x) = 0;
};

/* NOP */
class NOP : public Layer
{
public:
	NOP(int inputs, int neurons, Matrix& weights, Vector& bias);
	~NOP();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

/* Sigmoid */
class Sigmoid : public Layer
{
public:
	Sigmoid(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Sigmoid();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

/* ReLU */
class Relu : public Layer
{
public:
	Relu(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Relu();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

/* LeakyRelu */
class LeakyRelu : public Layer
{
public:
	LeakyRelu(int inputs, int neurons, Matrix& weights, Vector& bias);
	~LeakyRelu();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

/* Relu6 */
class Relu6 : public Layer
{
public:
	Relu6(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Relu6();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

/* ELU */
class Elu : public Layer
{
public:
	Elu(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Elu();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

/* SeLU */
class Selu : public Layer
{
public:
	Selu(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Selu();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

/* GeLU */
class Gelu : public Layer
{
public:
	Gelu(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Gelu();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

/* Cube */
class Cube : public Layer
{
public:
	Cube(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Cube();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

/* Swish */
class Swish : public Layer
{
public:
	Swish(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Swish();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

/* Softsign */
class Softsign : public Layer
{
public:
	Softsign(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Softsign();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

/* Softplus */
class Softplus : public Layer
{
public:
	Softplus(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Softplus();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

/* Softmax */
class Softmax : public Layer
{
public:
	Softmax(int inputs, int neurons, Matrix& weights, Vector& bias);
	~Softmax();
	Matrix& applyActivation(Matrix& matrix);
	Matrix& applyActivationDerivative(Matrix& matrix);
};

#endif // !LAYER_H