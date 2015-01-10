#include <iostream>

// in this way one can just specify a namespace for certain functions
using std::cout;
using std::endl;

// ---------------------------------------------------

	static double
constant_function( double x ) {
    return 2.0;
}

	static double
linear_function( double x ) {
    return x;
}

	static double
quadratic_function( double x ) {
    return - 8 * x * x + 24 * x - 15;
}
 
// ---------------------------------------------------

// specifies different functions for different intervals 
//      [start:end[
      
// TODO: This is kind of an on-the-fly declaration and initialization.
//       Can you split it up into the two respective parts? 
//       (structure definition and example array)

//!
//! I define a `struct` such that the first and second fields are the interval limits.
//! The third field is just a pointer to a function.
//! In this way I can associata a function to an interval: this is just a __mapping__ 
//! between functions and intervals.
//!
struct LookupTable_entry {
    double start; // inclusive
    double end; // exclusive
    double ( *func ) ( double x );
};

struct LookupTable_entry example_table[] = { 
     { 0.0, 1.0, &linear_function },
     { 1.0, 2.0, &quadratic_function },
     { 2.0, 3.0, &constant_function }
}; //! @brief Actual user-specified functions-interval mapping.

// ---------------------------------------------------

/*!
 * @brief Mapping rule from intervals to functions.
 *
 *       1. Loop through all entries in the given lookup table
 *       2. Check for every entry if our query point is part 
 *          of the respective interval
 *       3. If so, call the corresponding function with the 
 *          query point as argument and stop the loop.
 *          If not, try the other entries.
 *
 * @param table is the mapping between intervals and functions
 * @param numberOfElementsInTable is the number of elements of the `table` array
 * @param querypoint is the point in which I want to evaluate the function
 * @return the value of the function in `querypoint`
 */

double query_lookuptable(
    struct LookupTable_entry *table,
    int numberOfElementsInTable,
    double querypoint
) {
    double result = 0.0;
	
	/// Cycle over all elements of the `*table`.
	for ( unsigned int e = 0; e < numberOfElementsInTable; ++ e ) {
		/// Check if my `querypoint` (the point in which I want my function to be
		/// evaluated) is part of the interval of any element of the `LookupTable_entry
		/// *table`.
		///
		/// First check if the `querypoint` is smaller than the first (i.e. lowest)
		/// `table[0].start` point. In this case, I can already break the cycle since
		/// the result is set to `0.0`.
		///
		/// @attention Be aware that:
		/// 	* `*table` intervals are assumed to be _sorted_;
		///		* if there are overlaps between intervals, this method will return the
		///		  value of the function (whose interval contains `querypoint`) wich
		/// 	  corresponds to the lowest index in the `*table`.
		if ( table[e].start > querypoint)
			break;
		else if( table[e].end > querypoint ) {
			/// If querypoint lies in the interval, assign the value to `result` and
			/// break the cycle.
			result = table[e].func( querypoint );
			break;
		}
//		cout << "element " << e << endl;
	}
    
    return result;
}

// ---------------------------------------------------

int main(int argc, char **argv) {

    // TODO: What does this magic line do? Why does it work in this case?
    // Does this method work for arrays which are stored in the heap as well?

	/// This magic line takes evaluates the sizes of the _whole_ array `example_table` and
	/// divides it by the size of one of its elements to get the lenght of the array.
	///
	/// @attention Such a method __would not work__ for a heap-stored variables because
	/// in that case `sizeof(example_table)` would return the size of the pointer!
    size_t numberOfElementsInTable = sizeof(example_table) / sizeof(example_table[0]);

    std::cout << "# x_pos y_value" << std::endl;
    for ( double x = -1.0; x < 4.0; x += 0.1 ) {
        double result_value = query_lookuptable( example_table, numberOfElementsInTable, x );

        std::cout << x  << " "  
                  << result_value
                  << std::endl;
    }

    return 0;
}
