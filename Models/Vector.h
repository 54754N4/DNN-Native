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
	Vector(const Vector& vector);
	template<int c>
	Vector(long double (&vector)[c]);
	~Vector();
	/* Accessors */
	bool isZero();
	inline bool isRow();
	inline bool isColumn();
	int getLength();
	long double getNorm();
	std::string toString();
	/* Operations */
	const bool equals(Vector& vector);
	long double dotProduct(Vector& vector);
	Vector& normalize();
	Vector& hadamardProduct(Vector& vector);
	Vector& transpose();
	inline Vector& plus(Vector& vector);
	inline Vector& times(long double scalar);
	inline Vector& minus(Vector& vector);
	inline Vector& times(Vector& vector);
	Vector& operator+(Vector& vector);
	Vector& operator*(long double value);
	Vector& operator-(Vector& vector);
	Vector& operator*(Vector& vector);	// dot product
	/* Operator overloads (inline = have to be defined in header file) */
	inline const bool operator==(Vector& vector) { return equals(vector); };
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