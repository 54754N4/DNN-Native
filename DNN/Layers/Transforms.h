#ifndef TRANSFORMS_H
#define TRANSFORMS_H

long double max(long double* data, const int count);
long double* softmax(long double* data, const int count);
long double sigmoid(long double x);
long double sigmoidDerivative(long double x);

#endif