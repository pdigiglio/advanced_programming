/*
 * =====================================================================================
 *
 *       Filename:  polynomial.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/07/2014 09:21:45 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  P. Di Giglio (github.com/pdigiglio), p.digiglio91@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */


#include <iostream>

#define N 30

// evaluate polynomial with a normal summation
	float
normalPol ( double x, const double *a, unsigned int l = 1 ) {
	// assign a[ 0 ]
	double pol = *( a ++ );
	
	// XXX each step: 2 multiplication, 1 addition
	for ( unsigned int i = 1; i < l; i ++ ) {
		// add nex term
		pol += x * *( a ++ );
		// evaluate a new power of x
		x *= x;
	}

	return pol;
}		/* -----  end of function normalPol  ----- */

// evaluate polynomial with the Horner's factorization (faster, more accurate)
	float
hornerPol ( double x, const double *a, unsigned int l = 1 ) {
	// assign last operation
	// the first --l is because index are from 0 to l - 1
	// the second is to decrement the index
	double pol = *( a + ( -- l ) ) * x +  *( a + ( -- l ) );
	
	// XXX each step: 1 multiplication, 1 addition
	while( l ) {
		pol *= x;
		pol += *( a + ( -- l ) );

	}

	return pol;
}		/* -----  end of function hornerPol  ----- */

	int
main ( int argc, char *argv[] ) {
//	double a[] = {0., 1.};
//	// take length of vector
//	unsigned int length = sizeof( a ) / sizeof( double );

	// coefficient arrays
	double a[N], b[N];
	for ( unsigned short int i = 0; i < N; ++ i ) {
		// 1 / ( 1 + i )
		*( a + i ) = (double) 1 / ( 1 + i );
		// i / ( 1 + i )
		*( b + i ) = (double) i / ( N + 1 ) ;
	}

	double x = 2.5;
	std::cout << hornerPol( x, a, N ) << std::endl;
	std::cout << normalPol( x, a, N ) << std::endl;
	std::cout << hornerPol( x, b, N ) << std::endl;
	std::cout << normalPol( x, b, N ) << std::endl;

	return 0;
}				/* ----------  end of function main  ---------- */
