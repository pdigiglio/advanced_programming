/**
 *
 *
 *           @name  mem_all.cpp
 *          @brief  Out-of-bonds effects on arrays.
 *
 *          I will allocate four different arrays of length `N` (specified with a `#define`
 *          directive). Then I will read and write from them and see what happens when I am
 *          out of the bonds of allocated memory.
 *
 *          Example usage:
 *          @code
 *          $ ./mem_all
 *          @endcode
 *
 *        @version  1.0
 *           @date  11/20/2014 (09:02:55 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *
 */

#include <iostream>

#define N 100

/**
 * _Static_ and _global_ array are always initialized to zero whereas the
 * _heap_ and _stack_ ones are not.
 */


// global allocation
int globalArray[N];

/**
 * @brief Simple functions to read and write from/to arrays.
 *
 * The aim of the function is testing different kinds of memory allocations.
 *
 * @param ptr address of the array to access
 * @param start index from which access array
 * @param stop index until which access array
 */
	void
memory_access ( int *ptr, int start, int stop ) {
	std::cout << "Initial content of array: " << std::endl;
	
	/** First print the content of the allocated and not user-initialized array. */
	for ( int j = start; j < stop; ++ j )
		std::cout << "(" << j << ") " << ptr[j] << " ";

	std::cout << std::endl;

	std::cout << std::endl << "After filling it with ones: " << std::endl;
	
	/** Then tries to write the value 1 in the array and to print the new content. */
	for ( int j = start; j < stop; ++ j )
		ptr[j] = 1;

	for ( int j = start; j < stop; ++ j )
		std::cout << "(" << j << ") " << ptr[j] << " ";

	std::cout << std::endl << std::endl;

}		/* -----  end of function memory_access  ----- */

	int
main ( int argc, char *argv[] ) {
	// static allocation
	static int staticArray[N];

	/** The _stack_ memory is not inizialized: it contains random values! */

	// stack (normal) allocation
	int stackArray[N];
	// Heap allocation
	int *heapArray = new int[N];
	std::cout << "ADDR(first): " << reinterpret_cast<void*>(heapArray) << std::endl;
	
	/**
	 * The _heap_ memory complains when I am out of bounds.
	 * There is no problem for reading but I have troubles when I want to write on it.
	 */ 


	/**
	 * When my `start` parameter is negative, I have no problem as far its absolute value
	 * is small. Then the first problem is that I cannot write on the globally allocated
	 * array.
	 */
	int start = 0;
	int stop = 100;

	std::cout << " >> Global memory << " << std::endl;
	memory_access( globalArray, start, stop );

	std::cout << " >> Stack memory << " << std::endl;
	memory_access( stackArray, start, stop );

	/**
	 * @attention The _heap_ memory will be accessible even if I 'delete []` the array
	 * before I use it!
	 */
	delete [] heapArray;
	std::cout << "ADDR(after): " << reinterpret_cast<void*>(heapArray) << std::endl;

	std::cout << " >> Heap memory << " << std::endl;
	memory_access( heapArray, start, stop );

	std::cout << " >> Static memory << " << std::endl;
	memory_access( staticArray, start, stop );

//	delete [] heapArray;

	return 0;
}				/* ----------  end of function main  ---------- */
