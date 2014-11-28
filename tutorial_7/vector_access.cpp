/**
 *
 *
 *           @name  vector_access.cpp
 *
 *          @brief  Simple program to implement a class handling heap memory.
 *
 *          Compile and run without argumenst:
 *          @code
 *           $ ./vector_access
 *          @endcode
 *
 *        @version  1.0
 *           @date  11/27/2014 (09:46:02 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *
 *
 */
#include <iostream>

#include <cstdio>
#include <cmath>

#include <typeinfo>

using namespace std;

class VectorOperations;

//TODO: implement OurVector
class OurVector {
	friend class VectorOperations;

	public:

		/// @brief Constructor.
		///
		/// Checks the given `size` and allocates the memory in heap using `new`.
		/// 
		/// @param size number of double do allocate
		/// @param value the initial value to assign to my allocated memory
		OurVector ( int size = 1, double value = 0 ): _size( size ) {

			/// If the `size` is invalid, prints a messagge to the `stderr` and exits
			/// the program with the `EXIT_FAILURE` value.
			if ( _size <= 0 ) {
				cerr << "Invalid size" << endl;
				exit( EXIT_FAILURE );
			}

			// print a message
			cerr << " >> " << __func__ << ": Allocating an array of " << _size
				<< " double(s) in heap memory" << endl;

			/// Allocates heap memory. If the allocation fails, it prints a messagge to
			/// the `stderr` and exits with `EXIT_FAILURE`.
			_p = new double[_size];
			if( _p == NULL ) {
				cerr << "Allocation failed" << endl;
				exit( EXIT_FAILURE );
			}

		/// Initialize the heap memory.
//			#pragma omp parallel for
			for ( int j = 0; j < _size; ++ j ) {
				_p[j] = value;
			}
		};

		/// @brief The copy constructor.
		///
		/// This overrides the default copy constructor and avoids memory problems.
		/// The copying operation is performed "physically": values are copied one by
		/// one into the new class so that even if `first` is destroyed for some reason,
		/// values are stored.
		///
		/// @param first constant rference to a class to copy from
		OurVector ( const OurVector &first ): _size(first._size) {
			// print a message
			cerr << " >> " << __func__ << ": Allocating an array of " << _size
				<< " double(s) in heap memory" << endl;

			/// Allocates heap memory. If the allocation fails, it prints a messagge to
			/// the `stderr` and exits with `EXIT_FAILURE`.
			_p = new double[_size];
			if( _p == NULL ) {
				cerr << "Allocation failed" << endl;
				exit( EXIT_FAILURE );
			}

			// copy the variables
			cerr << " >> " << __func__ << ": Coping values into heap array" << endl;
			for ( int j = 0; j < _size; ++ j ) {
				_p[j] = first._p[j];
			}
		}
		
		/// @brief Assignment operator
		///
		/// Since I have a `const _size` variable, the defalut assignment operator
		/// cannot work.
		OurVector& operator = ( const OurVector &first ) {
			/// In this case, I cannot assign `_size` since it already has got some
			/// value. So I just can check if `_size` values are compatibile.
			if( _size != first._size ) {
				cerr << " >> " << __func__ << " : Sizes not matching. Exiting." << endl; 
				exit( EXIT_FAILURE );
			}

			/// If the `_size` test is passed then the valued are copied one by one.
			for ( int j = 0; j < _size; ++ j )
				_p[j] = first._p[j];

			return *this;
		}

		/// @brief Deallocates memory for my double pointer.
		~OurVector () {
			// print a message
			cerr << " >> " << __func__ << ": Deleting an array of " << _size
				<< " double(s) in heap memory" << endl;
			delete [] _p;
		};


		/// @brief Get the value in the \f$i\f$-th index of the array.
		///
		/// Specifying `const` after the function means that I cannot change anything
		/// in my function.
		const double& GetValue( int i ) const {
			/// Check if the index is out of bonds and if so returns `NaN` and print
			/// a message to the `stderr`.
			if ( i < 0 || _size < i ) {
				cerr << "Error accessing array! NaN returned!" << endl;
				return _accessError;
			}

			/// If the index is ok, it returns a `const` reference to the value.
			return _p[i];
		};

		/// @brief returns a `const` reference to the array size.
		const int& GetSize() const {
			return _size;
		};

	protected:
		/// The `_size` of my array is hidden to any other class.
		const int _size;

	private:
		double *_p;
		const double _accessError = NAN;

}; /* -----  end of class OurVector  ----- */

//TODO: implement VectorOperations
class VectorOperations {
	public:
		VectorOperations () {
			cerr << "[" << __func__ << "]" << endl;
 		};

		~VectorOperations () { 
			cerr << "[" << __func__ << "]" << endl;
		};


		static void add ( const OurVector &a, const OurVector &b, OurVector &res );

		static void print ( const OurVector &a );
}; /* -----  end of class VectorOperations  ----- */

/// @brief Function to add two `OurVector`s into a third one
///
/// This is declared to be `static` so that one can access it even 
/// without initializing an instance of `VectorOperations`.
///
/// @param a the first operand
/// @param b the second operand
/// @param res the class in which will be stored the result
	void
VectorOperations::add ( const OurVector &a, const OurVector &b, OurVector &res ) {
	// check if all sizes are compatible
	if( a.GetSize() != b.GetSize() ) {
		cerr << "Operands have different sizes" << endl;
		exit( EXIT_FAILURE );
	} else if ( a.GetSize() != res.GetSize() ) {
		cerr << "Size for operands and result don't correspond" << endl;
		exit( EXIT_FAILURE );
	}

//			#pragma omp parallel for
	for ( int j = 0; j < a.GetSize(); ++ j ) {
		res._p[j] = a._p[j] + b._p[j];
	}
}

/// @brief Prints the values of the vector `_p` in a column.
	void
VectorOperations::print ( const OurVector &a ) {
	for ( int j = 0; j < a.GetSize(); ++ j )
		cout << a._p[j] << endl;
}



// our stub implementation for testing
int main(int argc, char **argv) {
    // TODO: task 1: define class OurVector and create an instance of it
    OurVector first(5,2.0);

    // TODO: task 2: define class VectorOperations
    {
        OurVector result(5,0.0);
        VectorOperations::add(first,first,result);

        std::cout << "vector content of result: " << std::endl;
        VectorOperations::print(result);
    }

    //TODO: task 3: copy operator and explicit operators
    {
        OurVector b(5,3.0);
        /// The `b` class will be deleted at the end of the scoper so I may have
        /// a reference to an invalid memory spot in my `first` opject.
        /// With the implicit _copy ctor_ only the reference is passed.
        /// The solution is writing my own copy constructor and copy one by one the
        /// values.
        first = b; 
    }
    std::cout << "vector content after assignment: " << std::endl;
    VectorOperations::print(first);

    {
        OurVector copy(first);
        std::cout << "vector content after copy:" << std::endl;
        VectorOperations::print(copy);
    }

    return 0;
}
