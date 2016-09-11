/**
 *
 *
 *           @name  valgrind_memcheck_example.cpp
 *
 *        @version  1.0
 *           @date  01/09/2015 (08:27:45 AM)
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

#include <stdlib.h>

	void
f ( void ) {
	int *x = (int *) malloc( 10 * sizeof( int ) );

	// XXX invalid memory access
	x[10] = 0;

	// XXX also: memory leak -- I don't free memory!
}

	int
main ( void ) {

	f();

	return 0;
}
