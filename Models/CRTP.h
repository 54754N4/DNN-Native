#ifndef CRTP_H
#define CRTP_H

template<typename Derived>
class CRTP
{
	typedef CRTP Base;
public:
	// casting "down" the inheritance hierarchy
	Derived const* self() const
	{
		return static_cast<Derived const*>(this);
	}

	// write the non-const version in terms of the const version
	// Effective C++ 3rd ed., Item 3 (p. 24-25)
	Derived* self()
	{
		return const_cast<Derived*>(static_cast<Base const*>(this)->self());
	}
protected:
	// disable deletion of Derived* through Base* 
	// enable deletion of Base* through Derived*
	~CRTP() {}		// nop
};

#endif //!CRTP_H