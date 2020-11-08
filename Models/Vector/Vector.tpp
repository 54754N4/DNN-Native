#ifndef VECTOR_TPP
#define VECTOR_TPP

#ifndef VECTOR_H
#error __FILE__ should only be included from Vector.h
#endif 

template<int c>
Vector::Vector(long double (&vector)[c]) : IVector(c) {
	data = new long double[c];
	for (int i = 0; i < c; i++)
		data[i] = vector[i];
}
#endif