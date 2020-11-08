#ifndef IVECTOR_H
#define IVECTOR_H

class IVector
{
protected:
	/* Attributes */
	bool row{ 1 };	// by default create row vectors
public:
	int count{ 0 };
protected:
	/* Constructors and destructor */
	IVector();
	explicit IVector(int size);
	IVector(const IVector& vector);							// copy constructor
public:
	/* Accessors */
	bool isRow();
	bool isColumn();
	int getLength();
	virtual bool isZero() = 0;
	virtual long double getNorm() = 0;
	virtual std::string toString() = 0;
	/* Operations */
	virtual const bool equals(IVector& vector) = 0;
	virtual long double dotProduct(IVector& vector) = 0;
	virtual IVector& normalize() = 0;
	virtual IVector& hadamardProduct(IVector& vector, bool inPlace = false) = 0;
	virtual IVector& transpose(bool inPlace = false) = 0;
	virtual inline IVector& plus(IVector& vector, bool inPlace = false) = 0;
	virtual inline IVector& times(long double scalar, bool inPlace = false) = 0;
	virtual inline IVector& minus(IVector& vector, bool inPlace = false) = 0;
	virtual inline IVector& times(IVector& vector, bool inPlace = false) = 0;
	virtual IVector& operator+(IVector& vector) = 0;
	virtual IVector& operator*(long double value) = 0;
	virtual IVector& operator-(IVector& vector) = 0;
	virtual IVector& operator*(IVector& vector) = 0;	// dot product
	/* Operator overloads (inline = have to be defined in header file) */
	inline const bool operator==(IVector& vector) { return equals(vector); };
	virtual inline long double& operator()(int index) = 0;
	virtual inline long double operator()(int index) const = 0;
	virtual inline long double& operator[](int index) = 0;
	virtual inline long double operator[](int index) const = 0;
};


#endif	// !IVECTOR_H