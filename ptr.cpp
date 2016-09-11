/**
 *
 *
 *           @name  ptr.cpp
 *
 *        @version  1.0
 *           @date  12/28/2014 (09:15:37 PM)
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

int main ( ) {
	int *a = new int(3);
	std::cout << a << " = " << *a << std::endl;

	delete a;
	
	// why can I still use the pointer?
	std::cout << a << " = " << *a << std::endl;

	*a = 1;
	std::cout << a << " = " << *a << std::endl;

	a = nullptr;
	// why can I delete it _again_ (even if it's an invalid address)?
	delete a;

	// segmentation fault
	std::cout << a << " = " << *a << std::endl;

	return 0;
}
