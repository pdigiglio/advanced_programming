/*
 * =====================================================================================
 *
 *       Filename:  pi_approximation.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/07/2014 01:29:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  P. Di Giglio (github.com/pdigiglio), p.digiglio91@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <iomanip>

#include <cmath>
#include <ctime>
#include <cstdlib>

	int
main ( int argc, char *argv[] ) {
	// random seed
	srand( time( NULL ) );
	
	// variable for timing
	clock_t start = clock();
	
	// number of throws
	unsigned int throws = 100000000;

	// coordinates of the point
	double x, y;
	// counter for points inside the circle
	unsigned int inside = 0;
	for ( unsigned int j = 0; j < throws; ++ j ) {
		// choose two random numbers with uniform distribution
		x = (double) rand() / RAND_MAX;
		y = (double) rand() / RAND_MAX;

		// checks if the point is in the circle
		if( y * y < 1.0 - x * x )
			inside ++;
	}

	// I take 0,1 as random variable so that <x^2> = <x>
	double piFour = ( (double) inside / throws ); 
	double err = sqrt( piFour * ( 1 - piFour ) / ( throws - 1 ) );
	std::cout << piFour * 4 << " +/- " << 
		4 * err;
	std::cout << std::setprecision(2);
	std::cout << " (" << 100 * err / piFour << "%)"  << std::endl;

	// to see the difference in time with optimization options
	std::cout << "Time: " << (double) ( clock() - start ) / CLOCKS_PER_SEC << std::endl;
	return 0;
}				/* ----------  end of function main  ---------- */
