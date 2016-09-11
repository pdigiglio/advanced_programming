/**
 *
 *
 *           @name  auto_vector.cpp
 *
 *        @version  1.0
 *           @date  01/22/2015 (11:45:36 PM)
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

#include <cstdio>
#include <cstdlib>

const unsigned int SIZE = 400;
const short int VECTORSIZE = 4;

void vector_init( double *a, size_t N ) {
	for ( unsigned int s = 0; s < SIZE; ++ s ) {
		a[s] = static_cast<double>( rand() ) / RAND_MAX;
	}
}

void vector_add_reference ( double *a, double *b, double *c, size_t N ) {
	for ( unsigned int s = 0; s < SIZE; ++ s ) {
		a[s] = b[s] + c[s];
	}
}

template<unsigned int VS>
void vector_add ( double *a, double *b, double *c, size_t N ) {
	for ( unsigned int s = 0; s < N / VS; ++ s ) {
		for ( unsigned short int v = 0; v < VS; ++ v ) {
			a[s * VS + v ] = b[s * VS + v] + c[s * VS + v];
		}
	}

}
	int
main () {

	double a[SIZE], b[SIZE], c[SIZE];

	vector_add_reference( a, b, c, SIZE );
	vector_add<VECTORSIZE>(a, b, c, SIZE);

	return 0;
}
