#include <stdexcept>
#include <string>
#include <iostream>
#include <math.h>
#include "IVector.h"
#include "Vector.h"
#include "../Exceptions.h"

/* Constructors and destructor */
inline Vector::Vector() 
	: IVector() {}

Vector::Vector(int size) 
	: IVector(size), data(new long double[size])
{
	initialize(0);
}

Vector::Vector(int size, const double initial) 
	: IVector(size), data(new long double[size])
{
	initialize(initial);
}

Vector::Vector(long double* data, int count) 
	: IVector(count), data(new long double[count])
{
	slice(data);
}

Vector::~Vector() 
{
	if (data != nullptr)
		delete[] data;
}

/* Move semantics */

Vector::Vector(const Vector& vector)					// copy ctor
	: IVector(vector.count), data(new long double[vector.count])
{
	std::copy(vector.data, vector.data + vector.count, data);
}

Vector::Vector(Vector&& vector) noexcept				// move ctor
{ 
	*this = std::move(vector);
}

Vector& Vector::operator=(const Vector& vector)			// copy op
{
	if (this != &vector)
	{
		if (count != vector.count)
		{
			if (data != nullptr)
				delete[] data;
			data = new long double[vector.count];
		}
		count = vector.count;
		std::copy(vector.data, vector.data + count, data);
	}
	return *this;
}

Vector& Vector::operator=(Vector&& vector) noexcept		// move op
{	
	if (this != &vector)
	{
		if (data != nullptr)
			delete[] data;
		count = vector.count;
		data = vector.data;
		vector.count = 0;
		vector.data = nullptr;
	}
	return *this;
} 


/* Utility methods */

void Vector::initialize(const long double value)
{
	for (int i = 0; i < count; ++i)
		data[i] = value;
}

void Vector::slice(long double* elements)
{
	for (int i = 0; i < count; ++i)
		data[i] = elements[i];
}

/* Accessors */

bool Vector::isZero()
{
	for (int i = 0; i < count; ++i)
		if (data[i] != 0)
			return false;
	return true;
}

std::string Vector::toString() 
{
	std::string result = "";
	for (int i = 0; i < count; ++i)
		result.append(std::to_string(data[i]))
			.append(row ? " " : "\n");
	return result;
}

long double Vector::getNorm()
{
	long double norm = 0;
	for (int i = 0; i < count; ++i)
		norm += data[i] * data[i];
	return sqrt(norm);
}

IVector& Vector::normalize()
{
	return *this * (1 / getNorm());
}

long double Vector::dotProduct(IVector& vector)
{
	if (count != vector.count)
		throw VectorsDifferentDimensionError(count, vector.count);
	long double dotProduct = 0;
	for (int i = 0; i < count; ++i)
		dotProduct += data[i] * vector[i];
	return dotProduct;
}

IVector& Vector::hadamardProduct(IVector& vector, bool inPlace)
{
	if (count != vector.count)
		throw VectorsDifferentDimensionError(count, vector.count);
	Vector* ptr = inPlace ? this : new Vector(count);
	for (int i = 0; i < count; ++i)
		(*ptr)[i] = data[i] * vector[i];
	return *ptr;
}

IVector& Vector::transpose(bool inPlace)
{
	Vector* ptr = inPlace ? this : new Vector(count);
	ptr->row = !row;
	return *ptr;
}

const bool Vector::equals(IVector& vector)
{
	for (int i = 0; i < count; ++i)
		if (data[i] != vector[i])
			return false;
	return true;
}

inline IVector& Vector::plus(IVector& vector, bool inPlace)
{
	if (count != vector.count)
		throw VectorsDifferentDimensionError(count, vector.count);
	Vector* ptr = inPlace ? this : new Vector(count);
	for (int i = 0; i < count; ++i)
		(*ptr)[i] = data[i] + vector[i];
	return *ptr;
}

inline IVector& Vector::times(long double scalar, bool inPlace)
{
	Vector* ptr = inPlace ? this : new Vector(count);
	for (int i = 0; i < count; ++i)
		(*ptr)[i] = data[i] * scalar;
	return *ptr;
}

inline IVector& Vector::minus(IVector& vector, bool inPlace)
{
	return this->plus(vector.times(-1, inPlace), inPlace);
}

inline IVector& Vector::times(IVector& vector, bool inPlace)
{
	return hadamardProduct(vector, inPlace);
}

IVector& Vector::operator+(IVector& vector) 
{
	return plus(vector);
}

IVector& Vector::operator*(long double scalar) 
{
	return times(scalar);
}

IVector& Vector::operator-(IVector& vector)
{
	return minus(vector);
}

IVector& Vector::operator*(IVector& vector)
{
	return hadamardProduct(vector);
}