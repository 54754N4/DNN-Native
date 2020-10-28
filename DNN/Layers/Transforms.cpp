#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include "..\..\Models\Exceptions.h"
#include "..\..\Models\Vector.h"
#include "..\..\Models\Matrix.h"
#include "Transforms.h"

long double max(long double* data, const int count)
{
	long double max = 0;
	for (int i = 0; i < count; ++i)
		if (*(data + i) > max)
			max = *(data + i);
	return max;
}

long double* softmax(long double* data, const int count)
{
	long double sum = 0, 
		m = max(data, count),
		*result = new long double[count];
	for (int i = 0; i < count; ++i) {
		*(result + i) = exp(*(data + i) - m);
		sum += *(result + i);
	}
	for (int i = 0; i < count; ++i)
		*(result + i) /= sum;
	return result;
}

long double sigmoid(long double x)
{
	return x / (1 + abs(x));
}

long double sigmoidDerivative(long double x)
{
	return x * (1 - x);
}

