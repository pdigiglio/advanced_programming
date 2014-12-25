/**
 *
 *
 *           @name  memory.cpp
 *
 *          @brief  Creates a recursive function and analyzes the memory usage.
 *
 *          Compile with specifying the `PAYLOAD_SIZE` macro, e.g.
 *          @code
 *          	g++ -DPAYLOAD_SIZE=10 memory.c -o memory
 *          @endcode
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *
 *        @version  1.0
 *           @date  11/10/2014 (10:54:14 PM)
 *
 *
 */


#include <iostream>

#include <cstdio>

#ifndef  PAYLOAD_SIZE
/** @def length of the string in the `recursiveSumMemory()` memory */
#define  PAYLOAD_SIZE 100 
#endif   /* ----- #ifndef PAYLOAD_SIZE  ----- */

/**
 * @brief The recursive function to be analized.
 *
 * For each function call a string `char a[PAYLOAD_SIZE]` is allocated.
 * The formal parameter `unsigned int n` is used as a counter to control the
 * recursion depth.
 *
 * @param n recursion depth
 * @return used memory on the recursive stack 
 */
	size_t
recursiveSumMemory( unsigned int n ) {

	// allocate a `char` array
	char a[PAYLOAD_SIZE];

//	std::cout << n << std::endl;
	if( n == 0 )
		return sizeof( a ) + sizeof( n );

	return sizeof( a ) + sizeof( n ) + recursiveSumMemory( -- n );
}


	int
main ( int argc, char *argv[] ) {

	// recursion depth
	unsigned int depth = 1000;

	std::cout << "Memory occupied (depth = " << depth << "): "
		<< recursiveSumMemory( depth ) << " Byte" << std::endl;

	return 0;
}				/* ----------  end of function main  ---------- */
