#ifndef TRANSFORMS_H
#define TRANSFORMS_H

/* References : 
https://en.wikipedia.org/wiki/Hyperbolic_functions
https://mlfromscratch.com/activation-functions-explained/#/  
*/

/* Utility */
long double max(long double* data, const int count);
long double coth(long double x);
long double sech(long double x);
long double csch(long double x);
long double acoth(long double x);
long double asech(long double x);
long double acsch(long double x);
long double sinhDerivative(long double x);
long double coshDerivative(long double x);
long double tanhDerivative(long double x);
long double cothDerivative(long double x);
long double sechDerivative(long double x);
long double cschDerivative(long double x);
long double asinhDerivative(long double x);
long double acoshDerivative(long double x);
long double atanhDerivative(long double x);
long double acothDerivative(long double x);
long double asechDerivative(long double x);
long double acschDerivative(long double x);
/* Sigmoid */
long double sigmoid(long double x);
long double sigmoidDerivative(long double x);
/* ReLU */
long double relu(long double x);
long double reluDerivative(long double x);
/* LeakyReLU */
long double leakyRelu(long double x, long double ratio = 0.3);
long double leakyReluDerivative(long double x, long double ratio = 0.3);
/* Relu6 */
long double relu6(long double x);
long double relu6Derivative(long double x);
/* ELU */
long double elu(long double x, long double alpha = 0.3);					// alpha usually belongs to [0.1, 0.3]
long double eluDerivative(long double x, long double alpha = 0.3);
/* Scaled ELU */
long double selu(long double x, long double alpha = 1.6732632423543772848170429916717, long double lambda = 1.0507009873554804934193349852946);
long double seluDerivative(long double x, long double alpha = 1.6732632423543772848170429916717, long double lambda = 1.0507009873554804934193349852946);
/* Gaussian ELU */
long double gelu(long double x);
long double geluDerivative(long double x);
/* Cube */
long double cube(long double x);
long double cubeDerivative(long double x);
/* Swish */
long double swish(long double x);
long double swishDerivative(long double x);
/* Softsign */
long double softsign(long double x);
long double softsignDerivative(long double x);
/* Softplus */
long double softplus(long double x);
long double softplusDerivative(long double x);
/* Softmax*/
long double* softmax(long double* data, const int count);
Matrix& softmaxDerivative(Matrix& matrix);


/* Matrix iterator consumers */
const auto SIGMOID_CONSUMER = [](long double x) -> long double { return sigmoid(x); };
const auto SIGMOID_DERIVATIVE_CONSUMER = [](long double x) -> long double { return sigmoidDerivative(x); };
const auto RELU_CONSUMER = [](long double x) -> long double { return relu(x); };
const auto RELU_DERIVATIVE_CONSUMER = [](long double x) -> long double { return reluDerivative(x); };
const auto LEAKY_RELU_CONSUMER = [](long double x) -> long double { return leakyRelu(x); };
const auto LEAKY_RELU_DERIVATIVE_CONSUMER = [](long double x) -> long double { return leakyReluDerivative(x); };
const auto RELU6_CONSUMER = [](long double x) -> long double { return relu6(x); };
const auto RELU6_DERIVATIVE_CONSUMER = [](long double x) -> long double { return relu6Derivative(x); };
const auto ELU_CONSUMER = [](long double x) -> long double { return elu(x); };
const auto ELU_DERIVATIVE_CONSUMER = [](long double x) -> long double { return eluDerivative(x); };
const auto SELU_CONSUMER = [](long double x) -> long double { return selu(x); };
const auto SELU_DERIVATIVE_CONSUMER = [](long double x) -> long double { return seluDerivative(x); };
const auto GELU_CONSUMER = [](long double x) -> long double { return gelu(x); };
const auto GELU_DERIVATIVE_CONSUMER = [](long double x) -> long double { return geluDerivative(x); };
const auto CUBE_CONSUMER = [](long double x) -> long double { return cube(x); };
const auto CUBE_DERIVATIVE_CONSUMER = [](long double x) -> long double { return cubeDerivative(x); };
const auto SWISH_CONSUMER = [](long double x) -> long double { return swish(x); };
const auto SWISH_DERIVATIVE_CONSUMER = [](long double x) -> long double { return swishDerivative(x); };
const auto SOFTSIGN_CONSUMER = [](long double x) -> long double { return softsign(x); };
const auto SOFTSIGN_DERIVATIVE_CONSUMER = [](long double x) -> long double { return softsignDerivative(x); };
const auto SOFTPLUS_CONSUMER = [](long double x) -> long double { return softplus(x); };
const auto SOFTPLUS_DERIVATIVE_CONSUMER = [](long double x) -> long double { return softplusDerivative(x); };
#endif