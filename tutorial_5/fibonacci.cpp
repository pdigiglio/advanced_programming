/**
 *
 *
 *           @name  fibonacci.cpp
 *
 *        @version  1.0
 *           @date  11/09/2014 (10:54:57 PM)
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


#include <cstring>
#include <cerrno>
#include "eta.h"

	long int
FibonacciRec ( long int n ) {
	if( n == 0 || n == 1 )
		return n;

	return FibonacciRec( n - 1 ) + FibonacciRec( n - 2 );
}		/* -----  end of function FibonacciRec  ----- */


/**
 * @brief The Fibonacci series with one recursive call.
 *
 * In the previous recursive cycle, I evaluate twice each `FibonacciRec( n - i )`
 * when `i` is greater than one.
 */
	long int
FibonacciRec2 ( long int n, long int *a, long int *b ) {
	if( n > 0 ) {
		long int sum = *a + *b;
		*a = *b;
		*b = sum;
		return FibonacciRec2( -- n, a, b );
	}

	return *b;
}		/* -----  end of function FibonacciRec2  ----- */

/**
 * @brief The Fibonacci series with one recursive call without pointers.
 *
 */
	long int
FibonacciRec3 ( long int n, long int tmp = 1, long int sum = 0 ) {
	if( n > 0 )
		return FibonacciRec3( -- n, sum, sum + tmp );

	return sum;
}		/* -----  end of function FibonacciRec2  ----- */

	int
main ( int argc, char *argv[] ) {

//	clock_t start;
//
//	char timesIter_file_name[] = "timesIter.dat"; /**< Output file name for `FibonacciIter()`. */
//	FILE *timesIter = fopen( timesIter_file_name, "w" ); /**< Output File pointer for `FibonacciIter()`. */
//
//	if ( timesIter == NULL ) {
//		fprintf ( stderr, "couldn't open file '%s'; %s\n",
//				timesIter_file_name, strerror(errno) );
//		exit (EXIT_FAILURE);
//	}
//
//	char timesRec_file_name[] = "timesRec.dat"; /**< Output file name for `FibonacciRec()`. */
//	FILE *timesRec = fopen( timesRec_file_name, "w" ); /**< Output File pointer for `FibonacciRec()`. */
//
//	if ( timesRec == NULL ) {
//		fprintf ( stderr, "couldn't open file '%s'; %s\n",
//				timesRec_file_name, strerror(errno) );
//		exit (EXIT_FAILURE);
//	}
//
//
//	for ( unsigned i = 0; i < 50; ++ i ) {
//		start = clock();
//		std::cout << "F(" << i << ") = " << FibonacciRec( i ) << std::endl;
//		printETA( start, timesRec );
//	}
//	
//	if( fclose(timesIter) == EOF ) { /* close output file */
//		fprintf ( stderr, "couldn't close file '%s'; %s\n",
//				timesIter_file_name, strerror(errno) );
//		exit (EXIT_FAILURE);
//	}
//
//	if( fclose(timesRec) == EOF ) {			/* close output file   */
//		fprintf ( stderr, "couldn't close file '%s'; %s\n",
//				timesRec_file_name, strerror(errno) );
//		exit (EXIT_FAILURE);
//	}

	clock_t start = clock();

	for ( unsigned i = 0; i < 40; ++i )
		std::cout << "F(" << i << ") = " << FibonacciRec( i ) << std::endl;

	printETA( start );

	start = clock();
	for ( unsigned i = 0; i < 40; ++i )
		std::cout << "F(" << i << ") = " << FibonacciRec3( i ) << std::endl;

	printETA( start );

	start = clock();
	for ( unsigned i = 0; i < 40; ++i )
		std::cout << "F(" << i << ") = " << FibonacciRec3( i ) << std::endl;

	printETA( start );
	
	return 0;
}				/* ----------  end of function main  ---------- */
