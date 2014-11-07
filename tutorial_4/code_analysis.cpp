/*
 * =====================================================================================
 *
 *       Filename:  code_analysis.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/07/2014 08:57:09 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  P. Di Giglio (github.com/pdigiglio), p.digiglio91@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */


#include <iostream>


	int
main ( int argc, char *argv[] ) {
	int xvalues[10];

	// XXX problem with space allocation of your array

	// XXX (signed) char are from -128 to 127 so I have an infinite loop
	for( char i = 0 i < 128; i ++ ) {
		// you cannot use a char into an array index 
		// in C++ (maybe an unsigned char works)
		std::cin >> xvalues[ static_cast<int>( i ) ];
	}

	// this value is 0 because you firs perform the operation as integer
	double a = static_cast<double>( 1 / 3 );
	double b = 5;
	double c = 10;

	for ( int i = 0; i < 128; i ++ ) {
		int x = xvalues[ i ];
		// XXX ^ is a XOR binary operator
		// XXX 1 / a is an error because of 1 / 0
		double result = ( 1 / a ) * ( ( x + 1 ) ^ 2 ) + b * x + c;
		std::cout << "x = " << xvalues[ i ]
			<< ", result = " << result << std::endl;
	}

	return 0;
}				/* ----------  end of function main  ---------- */
