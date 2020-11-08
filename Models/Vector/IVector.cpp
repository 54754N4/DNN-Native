#include <stdexcept>
#include <string>
#include <iostream>
#include <math.h>
#include "IVector.h"

/* Constructors */
IVector::IVector() {}
IVector::IVector(int size) : count(size) {}
IVector::IVector(const IVector& vector) : count(vector.count) {}

/* Accessors */
bool IVector::isRow()
{
	return row;
}

bool IVector::isColumn()
{
	return !row;
}

int IVector::getLength()
{
	return count;
}