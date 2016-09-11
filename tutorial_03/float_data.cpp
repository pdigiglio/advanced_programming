/**
 *
 *
 *           @name  float_data.cpp
 *
 *        @version  1.0
 *           @date  12/25/2014 (12:32:02 PM)
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

	int
main ( void ) {
	const unsigned int operations = 1;

	const float base = 1.;
	const float delta = 1e-20;

	float newValueMult = base;
	float newValueSum = base;

	for ( unsigned int j = 0; j < operations; ++ j ) {
		newValueSum  += delta;
		newValueMult *= delta;
	}

	for ( unsigned int j = 0; j < operations; ++ j ) {
		newValueSum  -= delta;
		newValueMult /= delta;
	}

	cout << "[prod] Old value: " << base << " ==> New value: " << newValueMult << endl; 
	cout << "[sum]  Old value: " << base << " ==> New value: " << newValueSum << endl; 

	return 0;
}
