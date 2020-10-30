#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
	/* Attributes */
	bool row = 1;	// by default create row vectors
	long double* data;
public:
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
	Vector& hadamardProduct(Vector& vector, bool inPlace = false);
	Vector& transpose(bool inPlace = false);
	inline Vector& plus(Vector& vector, bool inPlace = false);
	inline Vector& times(long double scalar, bool inPlace = false);
	inline Vector& minus(Vector& vector, bool inPlace = false);
	inline Vector& times(Vector& vector, bool inPlace = false);
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
	void initialize(const long double value);
	void slice(long double* elements);
};

#include "Vector.tpp"

#endif	// !VECTOR_H