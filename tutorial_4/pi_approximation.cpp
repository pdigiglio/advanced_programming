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
	//!
	//! First set a _random seed_  for the random number generator.
	//!
	srand( time( NULL ) );
	
	// variable for timing
	clock_t start = clock();
	
	//!
	//! Then choose a number of throws.
	//!
	unsigned int throws = 100000000;

	// coordinates of the point
	double x, y;
	// counter for points inside the circle
	unsigned int inside = 0;
	for ( unsigned int j = 0; j < throws; ++ j ) {
		//!
		//! For each throw, randomly generate two numbers in \f$[0,1]\f$
		//! with uniform distribution.
		//! They live in the upper-right quarter of the plane.
		//!
		x = (double) rand() / RAND_MAX;
		y = (double) rand() / RAND_MAX;

		//! 
		//! Then check if the number is in the circle using the equation of
		//! the circumference \f$x^2 + y^2 = 1\f$ so that the point lies in 
		//! the circumference if \f$ y^2 < 1 - x^2 \f$.
		//!
		if( y * y < 1.0 - x * x )
			inside ++;
	}

	//!
	//! I take \f$0\textrm{ and }1\f$ as random variable---i.e. the values put into `inside`
	//! variable which counts the number of points inside the circle---so that
	//! \f$\langle x^2\rangle = \langle x\rangle\f$.
	//! You see that if the point is outside the circle `inside` is not changed, i.e. I am
	//! adding the instance \f$0\f$ of my random variable, otherwise I increment `inside`
	//! by one \f$1\f$.
	//! Lastly, the ratio between `inside` and `throws` is the ratio between the area of
	//! the upper-right section of the circle \f$\pi r^2/4\f$, where the radius is one,
	//! and the area of the square of late length one so that the radio is \f$\pi/4\f$.
	//!
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
