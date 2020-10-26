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
	Vector(double* data, int count);
	template<int c>
	Vector(double (&vector)[c]);
	~Vector();
	/* Accessors */
	inline bool isRow();
	inline bool isColumn();
	inline int getLength();
	std::string toString();
	/* Operations */
	double dotProduct(Vector& vector);
	Vector& hadamardProduct(Vector& vector);
	Vector& transpose();
	Vector& operator+(Vector& vector);
	Vector& operator*(double value);
	Vector& operator-(Vector& vector);
	Vector& operator*(Vector& vector);	// dot product
	/* Operator overloads (inline = have to be defined in header file) */
	inline double& operator()(int index) { return *(data + index); }
	inline double operator()(int index) const { return *(data + index); };
	inline double& operator[](int index) { return *(data + index); }
	inline double operator[](int index) const { return *(data + index); };
private:
	bool row = 1;	// by default create row vectors
	double* data;

	void initialize(const double value);
	void slice(double* elements);
};

#include "Vector.tpp"

#endif	// !VECTOR_H