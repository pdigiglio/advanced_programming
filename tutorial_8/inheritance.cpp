/**
 *
 *
 *           @name  inheritance.cpp
 *          @brief  
 *
 *          Example usage:
 *          @code
 *          @endcode
 *
 *        @version  1.0
 *           @date  11/29/2014 (12:58:47 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *
 *
 */

#include "colors.h"

#include <iostream>

const int N = 10; /*!< @brief Constant length of array(s). */

class AbstractVector {
    public:
        AbstractVector() {
            std::cout << ANSI_GREEN << "AbstractVector" << ANSI_RESET
				<< ": constructor called" << std::endl;
        }

		/// @brief Destructor.
		///
		/// This is declared to be `virtual` in such a way that the right destructor
		/// is called when inherited classes are deleted with `delete`.
        virtual ~AbstractVector() {
            std::cout << ANSI_RED << "AbstractVector" << ANSI_RESET
				<< ": destructor called" << std::endl;
        }

		/// @brief Dummy function
		///
		/// If it's declared to be `virtual` then it will be overwritten in FixedVector
		/// and SequenceVector::print() will show the content of FixedVector::data[].
		/// Otherwise, SequenceVector will inheritate this useless method.
        virtual void print() {
            std::cout << "--- PRINT: Abstract vector content is abstract" << std::endl;
        }
};

class FixedVector : public AbstractVector {
    public:
        FixedVector() {
            std::cout << ANSI_BLUE << "FixedVector" << ANSI_RESET
				<< ": constructor called" << std::endl;

            for ( int i = 0; i < N; ++ i ) {
                data[i] = 0;
            }
        }
 
		/// There is no need to `delete [] data` since the memory is allocated in
		/// the _stack_ and will be automatically freed at the end of the class (scope).
        ~FixedVector() {
            std::cout << ANSI_RED << "FixedVector" << ANSI_RESET
				<< ": destructor called" << std::endl;
        }

		/// @brief Copy the values of `data[]` into `target.data[]`.
		///
		/// @attention If I used the _call by value_ this would __not__ work! In fact, a
		/// new FixedVector would be constructed and the value of its data[] array initialized
		/// to `0`.
		///
		/// @param target reference to the class where values will be copied
        void copy( FixedVector &target ) {
            std::cout << "--- copy data around!" << std::endl;
            for ( int i = 0; i < N ; ++ i ) {
               target.data[i] = data[i];
            }
        }

		/// Prints the content of `data[]` in a raw.
        void print() {
            std::cout << "--- PRINT: Fixed Vector content:";
            for ( int i = 0; i < N; ++ i ) {
                std::cout << " " << data[i];
            }
            std::cout << std::endl;
        }

    protected:
        int data[N]; //!< Just a `protected` array to allow inheritated classes to access it.
};

class SequenceVector : public FixedVector {
    public:
        SequenceVector() {
            std::cout << ANSI_CYAN << "SequenceVector " << ANSI_RESET
				<< ": constructor called" << std::endl;
 
            // TODO: allow SequenceVector to directly access the data array in FixedVector
            // then fill the array with values from [0..N-1]
			for ( int i = 0; i < N; ++ i ) {
				data[i] = i;
			}
        }
 
        ~SequenceVector() {
            std::cout << ANSI_RED << "SequenceVector" << ANSI_RESET
				<< ": destructor called" << std::endl;
        }
};

class LastVector: public SequenceVector {
	public:
	LastVector() {
		std::cout << ANSI_YELLOW << "LastVector " << ANSI_RESET
			<< ": constructor called" << std::endl;
	};

	~LastVector() {
		std::cout << ANSI_RED << "LastVector" << ANSI_RESET
			<< ": destructor called" << std::endl;
	};
};

void heap_initialization() {
    std::cout << "heap initialization: " << std::endl;
    std::cout << "----" << std::endl;
    {
        AbstractVector *fixedVector = new FixedVector();
        delete fixedVector;
    }
    std::cout << "----" << std::endl;
    {
        AbstractVector *sequenceVector = new LastVector();// new SequenceVector();
        delete sequenceVector;
    }
    std::cout << "----" << std::endl;
}

void normal_initialization() {
    std::cout << "normal initialization: " << std::endl;
    std::cout << "----" << std::endl;
    {
        FixedVector fixedVector; // Is properly constructed and distructed at the end of the scope.
    }
    std::cout << "----" << std::endl;
    {
        SequenceVector seqVector; // Is properly constructed and destructed as well.
    }
    std::cout << "----" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    std::cout << "========== TASK 1 =============" << std::endl;
    // TODO 1: direct access for derived classes only
    SequenceVector seqVector;
    std::cout << "this should be a sequence: ";
    seqVector.print();
 
    /* ----------------------------------------------------------- */

    std::cout << std::endl << "========== TASK 2 =============" << std::endl;
    // TODO 1: destructors and inheritance: 
    // heap version looks different? Why? Fix it!
    normal_initialization();
    heap_initialization();
  
    /* ----------------------------------------------------------- */
 
    std::cout << std::endl << "========== TASK 3 =============" << std::endl;
    // TODO 2: virtual functions matter
	//
	// This works it AbstractVector::print() is declared to be virtual
    AbstractVector *absVector = &seqVector;
    absVector->print();

    /* ----------------------------------------------------------- */

    std::cout << std::endl << "========== TASK 4 =============" << std::endl;
    // TODO 3: call by something ?
    FixedVector newVector;
    seqVector.copy(newVector);
    
    std::cout << "expected values: ";
    seqVector.print();
    std::cout << "actual values: ";
    newVector.print();
 
    return 0;
}
