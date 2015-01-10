/**
 *
 *
 *           @file  gcd.cpp
 *
 *          @brief  Great Common Divider.
 *
 *          This simple program evaluates the greatest common divider between two
 *          integers using tre algorithms. The first one is recursive and the remaining
 *          two ones are iterative.
 *
 *        @version  1.0
 *           @date  11/09/2014 07:59:24 PM
 *         @author  P. Di Giglio (github.com/pdigiglio), p.digiglio91@gmail.com
 *
 *
 */


#include <iostream>
#include "eta.h"

/**
	\brief Evaluate \f$\gcd(a,b)\f$ recursively.

	Evaluates the greatest common divider between two numbers using the recursive 
	formula
	\f[ \gcd(a,b) = 
	\begin{cases}
		a &\text{if }a=0 \\
		\gcd(b, a \bmod b) &\text{otherwise}
		\end{cases}
	\f]

*/
	long int
gcdRecursive ( long int a, const long int b ) {
	/*!
	 * Using a constant as parameter prevents errors like the assignment `b = 0`
	 * in the first `if` statement.
	 */
	if( b == 0 )
		return a;

//	std::cout << "a " << a << " b " << b << std::endl; 

	/**
	 * If `b` is greater than `a`, then \f$\gcd(b, a \bmod b)\f$ will interchange
	 * the variables: e.g. if \f$a = 3\f$ and \f$b=12\f$, then \f$a \bmod b = 3 = a\f$.
	 */
	return gcdRecursive( b, a % b );
}		/* -----  end of function gcdRecursive  ----- */


/**
 * \brief  Evaluate \f$\gcd(a,b)\f$ iteratively using a `tmp` temporary variable.
 */
	long int
gcdIterative ( long int a, long int b ) {
	long int tmp; ///!< temporary variable to store the old value of `a`. 

	while( b != 0 ) {
		tmp = b;
//		std::cout << "a " << a << " b " << b << std::endl; 

		b = a % b;
		a = tmp;
	}

	return a;
}		/* -----  end of function gcdIterative  ----- */

	long int
gcdIterative2 ( long int a, long int b ) {
	long int min = ( ( a > b ) ? b : a );
	for ( int i = min; i > 0; -- i ) {
		// if they have a common divider
		if( a % i == 0 && b % i == 0 )
			return i
	}

	// If it doesn't find any common divider, returns 1.
	return 1;
}		/* -----  end of function gcdIterative2  ----- */

/**
 * \brief Evaluate \f$\gcd(a,b)\f$ iteratively without using a `tmp` temporary variable.
 *
 * To swap variables without using a temporary variable, the following code is used
 * 	\code{.cpp}
 * 		a = a + b;
 * 		b = a - b; // ( a + b ) - b = a
 * 		a -= b;	// ( a + b ) - a = b
 * 	\endcode
 */

	long int
gcdIterativeSwap ( long int a, long int b ) {
	while( b != 0 ) {
//		std::cout << "a " << a << " b " << b << std::endl; 

		// swap variables
		a = a + b;
		b = a - b; // ( a + b ) - b = a
		a -= b;	// ( a + b ) - a = b

		// b = a % b
		// now b = a_old and a = b_old
		b %= a;
	}

	return a;
}		/* -----  end of function gcdIterativeSwap  ----- */


	int
main ( int argc, char *argv[] ) {

	/** First create a little prompt. */
	unsigned long int a, b;
	std::cout << "Insert two integers >> ";
	std::cin >> a >> b;

	/**
	 * Then evaluates gcd with three algorithms and print them to the
	 * `stdout` with the respective esecution times.
	 */
	clock_t start = clock();
	std::cout << "gcdRecursive( " << a << ", " << b <<
		" ) = " << gcdRecursive( a, b ) << std::endl;
	ETA( start );

	start = clock();
	std::cout << "gcdIterative( " << a << ", " << b <<
		" ) = " << gcdIterative( a, b ) << std::endl;
	ETA( start );

	start = clock();
	std::cout << "gcdIterativeSwap( " << a << ", " << b <<
		" ) = " << gcdIterativeSwap( a, b ) << std::endl;
	ETA( start );

	return 0;
}				/* ----------  end of function main  ---------- */
