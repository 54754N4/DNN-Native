#ifndef VECTOR_TPP
#define VECTOR_TPP

#ifndef VECTOR_H
#error __FILE__ should only be included from Vector.h
#endif 

template<int c>
Vector::Vector(double (&vector)[c]) : row(1), count(c) {
	data = new double[c];
	for (int i = 0; i < c; i++)
		data[i] = vector[i];
}
#endif