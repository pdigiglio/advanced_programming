/**
 *
 *
 *           @name  templates.cpp
 *
 *        @version  1.0
 *           @date  01/15/2015 (09:49:09 PM)
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
#include <cstdlib>
#include <string>

// TODO: ASSIGNMENT 1
// a function template to compute the square for general numeric types (requrires existence of "operator*")

/**
 * @brief Generic template function to evaluate square.
 *
 * It will work for any numeric type.
 *
 * @attention This requires the existence of the multiplication operator `*`
 */
template<class T>
T square(T a) {
	std::cout << "using generic version to square " << a << std::endl;
	return a*a;
}

// "int" is so special -- provide a specialized function template

/**
 * @brief Specialized template function for `int` square.
 *
 * Since this function is specialized, I will not be able to call the generic template
 * function with an `int` as argument.
 */
template<>
int square( int a ) {
	std::cout << "using specialized generic version to square " << a << std::endl;
	return a*a;
}

// and there's one more: a non-template square function for int

/**
 * @brief Non-templatized version for the square of an `int`
 *
 * If I call `square(int)`, then this function will automatically be called! To force
 * the compiler using the template-specialized function, I have to specify
 * `square<int>(int)".
 */
int square(int a) {
	std::cout << "using explicit version to square " << a << std::endl;
	return a*a;
}

//#define SQUAREMACRO

#ifdef SQUAREMACRO

/**
 * You need to put brackets here, otherwise when calling `square(a+1)` you will have
 * `a + 1 * a + 1` replaced while the expected result would be `(a+1)*(a+1)`
 */
#define square(a) (a)*(a)

#endif


// TODO: ASSIGNMENT 2: implement TArray class
template<class T>
class TArray {
	public:

		/**
		 * @brief class ctor
		 *
		 * Allocate memory and check for allocation fault (if errors occur: exit).
		 */
		TArray( size_t size ): _size(size) {
			_arr = new T[size];
			if ( _arr == nullptr ) {
				std::cerr << "allocation failed" << std::endl;
				exit( EXIT_FAILURE ); 
			}
		}
		~TArray() {
			delete [] _arr;
		}

		/**
		 * @brief Get the size of `_arr`
		 *
		 * @return `size` of the array `_arr`
		 */
			inline size_t
		size ( void ) const {
			return _size;
		}

		/**
		 * @brief `[]` operator implementation
		 *
		 * Check if index is out of bounds and returns the array element `i`.
		 *
		 * @return non-constant `T&` reference
		 */
			T&
		operator [] ( size_t i ) {
			if ( i >= _size ) {
				std::cerr << "out of bound access failed" << std::endl;
				exit( EXIT_FAILURE );
			}

			return this->_arr[i];
		}

	private:
		size_t _size; ///! @brief Size of the array
		T *_arr; ///! @brief pointer to be allocated in ctor
};

#define ASSIGNMENT2_DONE

#if defined(ASSIGNMENT2_DONE)

// TODO: ASSIGNMENT 3: 
//  1. implement bubble sort for a double array

/**
 * @brief Template swap functions.
 *
 * Swaps two variables using a temporary buffer variable.
 * The parameters are _non-const_ in order to allow the swapping!
 *
 * @param a _non-const_ reference to the first variable
 * @param b _non-const_ reference to the second variable
 *
 * @attention The template _must_ have operator `=` implemented!
 */
template <class T>
	inline void
swap ( T &a, T &b ) {
	T tmp = a;
	a = b;
	b = tmp;
}
/**
 * @brief Specialization of swap for `double`s.
 */
template <>
	inline void
swap ( double &a, double &b ) {
	double tmp = a;
	a = b;
	b = tmp;
}

// 1. step

/**
 * @brief Bubble sort explicit implementation
 */
void mysort( TArray<double>& array ) {

	for ( size_t i = 1; i < array.size(); ++ i ) {

		for ( size_t j = 0; j < array.size() - i; ++ j ) {

			if( array[j] > array[j + 1] )
				swap<double>( array[j], array[j + 1 ] );
		}
	}

}

#define SORT_DONE

//  2. convert function to a templated function.
//     You may assume that the DataTypes have available compare operators

/**
 * @brief Template bubble sort function implementation.
 *
 * Apply bubble sorting to any data type.
 *
 * @attention
 *     * Comparison `>` _must_ be defined for the data type!
 *     * Assignment operator `=` _must_ be defined in order to call `swap()`
 */
template <class T>
void mysort( T & array ) {

	for ( size_t i = 1; i < array.size(); ++ i ) {

		for ( size_t j = 0; j < array.size() - i; ++ j ) {

			if( array[j] > array[j + 1] )
				swap( array[j], array[j + 1 ] );
		}
	}

}
#define ASSIGNMENT3_DONE

// TODO: ASSIGNMENT 4: sort array of pointers in a special way

/**
 * @brief Specialized template bubble sort function
 *
 * In this case one should want to compare the value of the variable it's pointed by 
 * the `double*`, not the pointer itself!
 *
 */
template <>
void mysort( TArray<double*>& array ) {

	std::cerr << "Specialized double* sorting called" << std::endl;

	for ( size_t i = 1; i < array.size(); ++ i ) {

		for ( size_t j = 0; j < array.size() - i; ++ j ) {

			if( *(array[j]) > *(array[j + 1]) )
				swap<double>( *(array[j]), *(array[j + 1 ]) );
		}
	}

}
#endif

// test stub implementation
int main(int argc, char **argv) {
    std::cout << "ASSIGNMENT 1:" << std::endl;

	int aInt     = 4;
	float aFloat = 4.2f;

	int aIntSquared = square(aInt + 1);
	std::cout << "int:   " << (aInt + 1) << "^2=" << aIntSquared << std::endl;

    float aFloatSquared = square(aFloat);
	std::cout << "float: " << aFloat << "^2=" << aFloatSquared << std::endl;

    // TODO: How can you call the specialized version of square for integers?    

	/** One can call the specialized function by specifying `int` in angular brackets */
	aIntSquared = square<int>(aInt + 1);
	std::cout << "int:   " << (aInt + 1) << "^2=" << aIntSquared << std::endl;

    // ------------------------------------------------------------ //

#if defined(ASSIGNMENT2_DONE)
    std::cout << std::endl << "ASSIGNMENT 2:" << std::endl;

    // allocate TArray object
    TArray<double> array_a(10);

    // check implementation of size()
    if (array_a.size() != 10) {
        std::cout << "size of array_a: " << array_a.size()
                  << " but actual size should be 10"
                  << std::endl;
    } else {
        std::cout << "size() works as expected" << std::endl;
    }

    // check implementation of array operator[]
    for (size_t i=0; i < array_a.size(); ++i) {
        array_a[i] = static_cast<double>(i+10);
    }

    bool all_correct = true;
    for ( size_t i = 0; i < array_a.size(); ++ i ) {

        if ( array_a[i] != static_cast<double>( i + 10 ) ) {
            all_correct = false;
            std::cout << "value at position " << i << " is wrong: "
                      << " it should be " << static_cast<double>(i+10)
                      << std::endl;
        }
    }
    
    if ( !all_correct ) {
        std::cout << "operator[] returns the wrong values" << std::endl;
    } else {
        std::cout << "operator[] works as expected" << std::endl;
    }
    
    std::cout << "tests completed" << std::endl;
    std::cout << std::endl;
#endif

    // ------------------------------------------------------------ //

#if defined(SORT_DONE)
    std::cout << "ASSIGNMENT 3:" << std::endl;
    
    // seed some random values
    for ( size_t i = 0; i < array_a.size(); ++ i ) {
        array_a[i] = static_cast<double>( rand() ) / RAND_MAX;
    }

    // print unsorted array
    std::cout << "unsorted:" << std::endl;
    for ( size_t i = 0; i < array_a.size(); ++ i ) {
        std::cout << " " << array_a[i];
    }
    std::cout << std::endl;

    mysort(array_a);

    // print sorted array
    std::cout << "sorted:" << std::endl;
    for ( size_t i = 0; i < array_a.size(); ++ i ) {
        std::cout << " " << array_a[i];
    }
    std::cout << std::endl;

    std::cout << std::endl;
#endif

    // ------------------------------------------------------------ //

#if defined(ASSIGNMENT3_DONE)

    std::cout << "ASSIGNMENT 4:" << std::endl;

    // now we allocate an array of double pointers ....
    TArray<double*> array_ptrs(10);
    for ( size_t i = 0; i < array_ptrs.size(); ++ i ) {
		/**
		 * The doubles will be allocated in a consecutive way so the
		 * array is already sorted
		 */
        array_ptrs[i] = new double();
        *(array_ptrs[i]) = static_cast<double>( rand() ) / RAND_MAX;
    }

    // ... and try to sort them
    std::cout << "unsorted:" << std::endl;
    for (size_t i=0; i < array_ptrs.size(); ++i) {
        std::cout << " " << *(array_ptrs[i]);
    }
    std::cout << std::endl;
  
	/**
	 * In this case the correct (i.e. best matching) specialized template function will 
	 * be called since no explicit function has been implemented
	 */
    mysort(array_ptrs);

	/**
	 * When you try to sort the addresses of an array, as we are doing now, nothing
	 * will change: allocated doubles occupy consecutive places in memory (i.e. have
	 * incremental addresses).
	 */
    std::cout << "sorted:" << std::endl;
    for (size_t i=0; i < array_ptrs.size(); ++i) {
        std::cout << " " << *(array_ptrs[i]);
    }
    std::cout << std::endl;

    // finally, we cleanup some pointers
    for (size_t i=0; i < array_ptrs.size(); ++i) {
        delete (array_ptrs[i]);
    }

    std::cout << std::endl;

#endif

    // ------------------------------------------------------------ //

    return 0;
}
