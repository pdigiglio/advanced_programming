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


	/// I expect the memory compsumption to have a linear dependence on the `depth`
	/// parameter, as shown in figure
	/// @image latex mem_vs_depth.jpeg "Memory vs. Depth (`-O3` flag, `PAYLOAD_SIZE=100`)" width=10cm
//	for ( unsigned int depth = 0; depth < 1000; ++ depth ) {

	//	std::cout << "Memory occupied (depth = ";
//		std::cout << depth;
//		std::cout << "\t";
	//	std::cout << "): ";
		std::cout << recursiveSumMemory( depth );
	//	std::cout << " Byte"
		std::cout << std::endl;

	//	}
	
	/// Also, the memory compsumption as a function of `PAYLOAD_SIZE` should be linear, as
	/// shown in figure 
	/// @image latex mem_vs_payload.jpeg "Memory vs. `PAYLOAD_SIZE` (`-O3` flag, `depth=1000`)" width=10cm

	return 0;
}				/* ----------  end of function main  ---------- */
