/**
 *
 *
 *           @name  call_by_val_ref.cpp
 *          @brief  
 *
 *        @version  1.0
 *           @date  11/29/2014 (02:51:22 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *
 *
 */

#include <iostream>

class Base {
	public:
		void a ( void ) {
			std::cout << "a" << std::endl;
		};

		// this will be overwritten
		virtual void b ( void ) {
			std::cout << "b" << std::endl;
		};
};

class Derived: public Base {
	public:
		// until Base::a() is not virtual, this will not be called
		void a ( void ) {
			std::cout << "aD" << std::endl;
		};

		void b ( void ) {
			std::cout << "bD" << std::endl;
		};
};

// call by value
void func1 ( Base base ) {
	base.a();
	base.b();
}

// call by reference
void func2 ( Base &base ) {
	base.a();
	base.b();
}

// call by pointer
void func3 ( Derived *der ) {
	der->a();
	der->b();
}

int main ( void ) {
	Base b;
	Derived d;

	func1( b );
	// This is treated as a Base class since when the value is copied in the call,
	// a new Base class is constructed.
	func1( d );

	std::cout << std::endl << "---------" << std::endl << std::endl;
	
	func2( b );
	func2( d );

	std::cout << std::endl << "---------" << std::endl << std::endl;

	// This desn't work since Base is not a Derived so the compiler doesn't know how
	// to perform the conversion.
//	func3( &b );
	func3( &d );

	return 0;
}
