/**
 *
 *
 *           @name  static_experiment.cpp
 *
 *        @version  1.0
 *           @date  01/22/2015 (01:53:46 PM)
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
using namespace std;

/** XXX The value for a is the first assigned for each function */
int& foo( int b ) {
	static int a = b;
	cout << "foo: " << b << " " << a << endl;
	return a;
}

int* bar( int b ) {
	static int a = b;
	cout << "bar: " << b << " " << a << endl;
	return &a;
}

int main () {

	for ( unsigned int c = 1; c < 10; ++ c ) {
		cout << foo( c ) << " " << &foo(c)  << endl;
	}

	for ( unsigned int a = 3; a < 10; ++ a ) {
		cout << *bar( a ) << " " << bar(a) << endl;
	}

	return 0;
}
