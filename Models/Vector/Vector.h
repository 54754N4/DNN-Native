#ifndef VECTOR_H
#define VECTOR_H

class Vector : public IVector
{
	/* Attributes */
	long double* data{ nullptr };
public:
	/* Constructors and destructor */
	inline Vector();
	explicit Vector(int size);
	Vector(int size, const double initial);
	Vector(long double* data, int count);
	template<int c>
	Vector(long double (&vector)[c]);
	~Vector();
	/* Move semantics */
	Vector(const Vector& vector);							// copy ctor
	Vector(Vector&& vector) noexcept;						// move ctor
	Vector& operator=(const Vector& vector);				// copy op
	Vector& operator=(Vector&& vector) noexcept;			// move op
	/* Accessors */
	bool isZero() override;
	long double getNorm() override;
	std::string toString() override;
	/* Operations */
	const bool equals(IVector& vector) override;
	long double dotProduct(IVector& vector) override;
	IVector& normalize() override;
	IVector& hadamardProduct(IVector& vector, bool inPlace = false) override;
	IVector& transpose(bool inPlace = false) override;
	inline IVector& plus(IVector& vector, bool inPlace = false) override;
	inline IVector& times(long double scalar, bool inPlace = false) override;
	inline IVector& minus(IVector& vector, bool inPlace = false) override;
	inline IVector& times(IVector& vector, bool inPlace = false) override;
	IVector& operator+(IVector& vector) override;
	IVector& operator*(long double value) override;
	IVector& operator-(IVector& vector) override;
	IVector& operator*(IVector& vector) override;	// dot product
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