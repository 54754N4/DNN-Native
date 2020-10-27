#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
	/* Attributes */
	const int count;
	/* Constructors and destructor */
	inline Vector();
	Vector(int size);
	Vector(int size, const double initial);
	Vector(long double* data, int count);
	template<int c>
	Vector(long double (&vector)[c]);
	~Vector();
	/* Accessors */
	inline bool isRow();
	inline bool isColumn();
	inline int getLength();
	std::string toString();
	/* Operations */
	bool equals(Vector& vector);
	long double dotProduct(Vector& vector);
	Vector& hadamardProduct(Vector& vector);
	Vector& transpose();
	Vector& operator+(Vector& vector);
	Vector& operator*(long double value);
	Vector& operator-(Vector& vector);
	Vector& operator*(Vector& vector);	// dot product
	/* Operator overloads (inline = have to be defined in header file) */
	inline long double& operator()(int index) { return *(data + index); }
	inline long double operator()(int index) const { return *(data + index); };
	inline long double& operator[](int index) { return *(data + index); }
	inline long double operator[](int index) const { return *(data + index); };
private:
	bool row = 1;	// by default create row vectors
	long double* data;

	void initialize(const long double value);
	void slice(long double* elements);
};

#include "Vector.tpp"

#endif	// !VECTOR_H