/**
 *
 *
 *           @name  allignment.cpp
 *
 *        @version  1.0
 *           @date  12/25/2014 (01:04:01 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *          @brief  
 *
 *          Example usage:
 *          @code
 *          @endcode
 *
 *
 */

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

/**
 * @brief A macro for avoiding some copy-paste work in `dummy()`
 */

#define PVD( var )  cout << "Arg. name is: " << #var << endl; \
	cout << "___addr: " << &var << endl; \
	cout << "___addr: " << reinterpret_cast<size_t>(&var) << endl; \
	cout << "____val: " << var << endl; \
	cout << "____all: " << byteAllignment( &var ) << endl;	\
	cout << "___type: " << abi::__cxa_demangle(typeid(var).name(),0,0,nullptr) << endl;\
	cout << "___size: " << sizeof( var ) << " byte"<< endl << endl;

using namespace std;

/// @return the largest power of two which divides the address without a remaindern
	unsigned short int
byteAllignment( void *addr ) {

	/// Cast the address into a `size_t` to perform arithmetic calculations.
	size_t a = reinterpret_cast<size_t>( addr );

	// print addresses
//	cout << "Addr: " << addr << " => " << a << endl;

	/// Find the largest power of 2 which fits into the address:
	unsigned short int n = 0;
	/// Till a is a multiple of 2 (= last bit is 0)
	while( !( a & 1 ) ) {
		// Divide a by 2 (= cut off one zero in the decimal representation).
		a >>= 1;
//		cout << a << endl;
		++ n;
	}

	// return the power of two
	return n;
}

	void
info ( void *var ) {}

/**
 * @brief Just a dummy function without any return value (and agument) to allocate one
 * `int`, `char` and `double` in it.
 */
	void
dummy( void ) {
	int i = 0;
	PVD( i );
//	cout << "i:: addr: " << &i << endl;
//	cout << "i:: addr: " << reinterpret_cast<size_t>(&i) << endl;
//	cout << "i::  val: " << i << endl;
//	cout << "i::  all: " << byteAllignment( &i ) << endl;
//	cout << "i:: size: " << sizeof( i ) << " byte"<< endl;

//	cout << endl;

	double d;
	PVD( d );
//	cout << "d:: addr: " << &d << endl;
//	cout << "d:: addr: " << reinterpret_cast<size_t>(&d) << endl;
//	cout << "d::  val: " << d << endl;
//	cout << "d::  all: " << byteAllignment( &d ) << endl;
//	cout << "d:: size: " << sizeof( d ) << " byte" << endl;
//
//	cout << endl;

	long double ld;
	PVD( ld );
//	cout << "ld:: addr: " << &ld << endl;
//	cout << "ld:: addr: " << reinterpret_cast<size_t>( &ld ) << endl;
//	cout << "ld::  val: " << ld << endl;
//	cout << "ld::  all: " << byteAllignment( &ld ) << endl;
//	cout << "ld:: size: " << sizeof( ld ) << " byte" << endl;
//
//	cout << endl;

	char c[10];

	/// The `for` scope _is_ needed since in replacing text only the first line would
	/// be executed otherwise!
	for ( i = 0; i < 10; ++ i  ) {
		PVD( c[i] );
	}
//	cout << "c:: addr: " << (void*) &c << endl;
//	cout << "c:: addr: " << reinterpret_cast<size_t>(&c) << endl;
//	cout << "c::  val: " << (int) c << endl;
//	cout << "c::  all: " << byteAllignment( &c ) << endl;
//	cout << "c:: size: " << sizeof( c ) << " byte" << endl;
}

	int
main ( void ) {
//	int a;
//	cout << byteAllignment( &a ) << endl;
	dummy();
	return 0;
}
