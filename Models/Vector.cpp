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

inline int Vector::getLength()
{
	return count;
}

std::string Vector::toString() 
{
	std::string result = "";
	for (int i = 0; i < count; ++i)
		result.append(std::to_string(*(data + i)))
			.append(row ? " " : "\n");
	return result;
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

bool Vector::equals(Vector& vector)
{
	for (int i = 0; i < count; ++i)
		if (*(data + i) != *(vector.data + i))
			return false;
	return true;
}

Vector& Vector::operator+(Vector& vector) 
{
	if (count != vector.count)
		throw VectorsDifferentDimensionError(count, vector.count);
	Vector* result = new Vector(count);
	for (int i = 0; i < count; ++i)
		(*result)[i] = *(data+i) + *(vector.data+i);
	return *result;
}

Vector& Vector::operator*(long double value) {
	Vector* result = new Vector(count);
	for (int i = 0; i < count; ++i)
		(*result)[i] = (*data+i) * value;
	return *result;
}

Vector& Vector::operator-(Vector& vector)
{
	return *this + (vector * (-1));
}

Vector& Vector::operator*(Vector& vector)
{
	return this->hadamardProduct(vector);
}