#include <stdexcept>
#include <string>
#include <iostream>
#include <math.h>
#include "Vector.h"
#include "Exceptions.h"

/* Constructors and destructor */
inline Vector::Vector() : count(0)
{
	data = nullptr;
}

Vector::Vector(int size) :  count(size)
{
	initialize(0);
}

Vector::Vector(int size, const double initial) : count(size)
{
	initialize(initial);
}

Vector::Vector(long double* data, int count) : count(count)
{
	slice(data);
}

Vector::~Vector() 
{
	delete[] data;
}

/* Utility methods */
void Vector::initialize(const long double value)
{
	data = new long double[count];
	for (int i = 0; i < count; i++)
		*(data + i) = value;
}

void Vector::slice(long double* elements)
{
	data = new long double[count];
	for (int i = 0; i < count; ++i)
		*(data + i) = *(elements + i);
}

/* Accessors */
inline bool Vector::isRow()
{
	return row;
}

inline bool Vector::isColumn()
{
	return !row;
}

int Vector::getLength()
{
	return count;
}

bool Vector::isZero()
{
	for (int i = 0; i < count; ++i)
		if (*(data + i) != 0)
			return false;
	return true;
}

std::string Vector::toString() 
{
	std::string result = "";
	for (int i = 0; i < count; ++i)
		result.append(std::to_string(*(data + i)))
			.append(row ? " " : "\n");
	return result;
}

long double Vector::getNorm()
{
	long double norm = 0;
	for (int i = 0; i < count; ++i)
		norm += *(data + i) * *(data + i);
	return sqrt(norm);
}

Vector& Vector::normalize()
{
	return *this * (1 / getNorm());
}

long double Vector::dotProduct(Vector& vector)
{
	if (count != vector.count)
		throw VectorsDifferentDimensionError(count, vector.count);
	long double dotProduct = 0;
	for (int i = 0; i < count; ++i)
		dotProduct += *(data+i) * *(vector.data+i);
	return dotProduct;
}

Vector& Vector::hadamardProduct(Vector& vector)
{
	if (count != vector.count)
		throw VectorsDifferentDimensionError(count, vector.count);
	Vector* result = new Vector(count);
	for (int i = 0; i < count; ++i)
		(*result)[i] = *(data+i) * *(vector.data+i);
	return *result;
}

Vector& Vector::transpose()
{
	row = !row;
	return *this;
}

const bool Vector::equals(Vector& vector)
{
	for (int i = 0; i < count; ++i)
		if (*(data + i) != *(vector.data + i))
			return false;
	return true;
}

inline Vector& Vector::plus(Vector& vector)
{
	if (count != vector.count)
		throw VectorsDifferentDimensionError(count, vector.count);
	Vector* result = new Vector(count);
	for (int i = 0; i < count; ++i)
		(*result)[i] = *(data + i) + *(vector.data + i);
	return *result;
}

inline Vector& Vector::times(long double scalar)
{
	Vector* result = new Vector(count);
	for (int i = 0; i < count; ++i)
		(*result)[i] = (*data + i) * scalar;
	return *result;
}

inline Vector& Vector::minus(Vector& vector)
{
	return *this + (vector * (-1));
}

inline Vector& Vector::times(Vector& vector)
{
	return hadamardProduct(vector);
}

Vector& Vector::operator+(Vector& vector) 
{
	return plus(vector);
}

Vector& Vector::operator*(long double scalar) 
{
	return times(scalar);
}

Vector& Vector::operator-(Vector& vector)
{
	return minus(vector);
}

Vector& Vector::operator*(Vector& vector)
{
	return hadamardProduct(vector);
}