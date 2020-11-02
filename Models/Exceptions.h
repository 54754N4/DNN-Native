#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class IndexOutOfBoundsError : std::exception {
	const long index;
	std::string* message;	// Lazy loading
public:
	IndexOutOfBoundsError(long index) : index(index) {}
	~IndexOutOfBoundsError() { delete message; }

	const char* what() {
		const int length = 50;
		char buffer[length];
		std::snprintf(buffer, length, "Vector index out of bound : %i", index);
		message = new std::string(buffer);
		return message->c_str();
	}
};

class InvalidExponentError : std::exception {
	const long e;
	std::string* message;	// Lazy loading
public:
	InvalidExponentError(long e) : e(e) {}
	~InvalidExponentError() { delete message; }

	const char* what() {
		const int length = 50;
		char buffer[length];
		std::snprintf(buffer, length, "Exponent has to be > 0 and not : %i", e);
		message = new std::string(buffer);
		return message->c_str();
	}
};

class DuplicateArgumentError : std::exception {
public:
	const char* what() {
		return "Duplicate arguments given";
	}
};

class NotSquareMatrixError : std::exception {
public:
	const char* what() {
		return "Invalid operation on a non-square matrix";
	}
};

class NotYetImplementedError : std::exception {
public:
	const char* what() {
		return "Method has not been implemented yet";
	}
};

class NullMatrixDeterminantError : std::exception {
public:
	const char* what() {
		return "Matrix determinant == 0";
	}
};

class VectorDimensionError : std::exception {
	const long wrong, right;
	std::string* message;	// Lazy loading
public:
	VectorDimensionError(long wrong, long right) : wrong(wrong), right(right) {}
	~VectorDimensionError() { delete message; }

	const char* what() {
		const int length = 50;
		char buffer[length];
		std::snprintf(buffer, length, "Vector size is %i but should be : %i", wrong, right);
		message = new std::string(buffer);
		return message->c_str();
	}
};

class VectorsDifferentDimensionError : std::exception {
	const long first, second;
	std::string* message;
public:
	VectorsDifferentDimensionError(long a, long b) : first(a), second(b) {}
	~VectorsDifferentDimensionError() { delete message; }

	const char* what() {
		const int length = 90;
		char buffer[length];
		std::snprintf(buffer, length, "Vectors don't have the same dimensions: %i != %i", first, second);
		message = new std::string(buffer);
		return message->c_str();
	}
};

class MatricesDifferentDimensionError : std::exception {
	const long r1, r2, c1, c2;
	std::string* message;
public:
	MatricesDifferentDimensionError(long r1, long c1, long r2, long c2) : r1(r1), r2(r2), c1(c1), c2(c2) {}
	~MatricesDifferentDimensionError() { delete message; }

	const char* what() {
		const int length = 100;
		char buffer[length];
		std::snprintf(buffer, length, "Matrices cannot be multiplied (%i,%i) in (%i,%i), %i != %i", r1, c1, r2, c2, c1, r2);
		message = new std::string(buffer);
		return message->c_str();
	}
};

#endif // !EXCEPTIONS_H
